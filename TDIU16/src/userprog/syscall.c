#include <stdio.h>
#include <syscall-nr.h>
#include "userprog/syscall.h"
#include "threads/interrupt.h"
#include "threads/thread.h"

/* header files you probably need, they are not used yet */
#include <string.h>
#include "filesys/filesys.h"
#include "filesys/file.h"
#include "threads/vaddr.h"
#include "threads/init.h"
#include "userprog/pagedir.h"
#include "userprog/process.h"
#include "devices/input.h"
#include "userprog/flist.h"
#include "userprog/plist.h"
#include "devices/timer.h"
static void syscall_handler (struct intr_frame *);

static bool verify_fix_length(void* start, unsigned length)
{
  char *ptr = (char *) start; 
  char *end = ptr + length; 
  char *page_addr = pg_round_down(ptr); 

  if (ptr == NULL || !is_user_vaddr(ptr) || !is_user_vaddr(end - 1))
    return false;
  
  for(;page_addr < end; page_addr +=PGSIZE){
    if(pagedir_get_page(thread_current()->pagedir, page_addr) == NULL){
      return false;  
    } 
  }
  return true; 
}

static bool verify_variable_length(const char *start)
{
  if (start == NULL || !is_user_vaddr(start) || pagedir_get_page(thread_current()->pagedir, start) == NULL)
    return false;

  unsigned last_page = pg_no(start);

  while (true) {
    if (pg_no(start) != last_page){     
      if (!is_user_vaddr(start) || pagedir_get_page(thread_current()->pagedir, start) == NULL)
        return false;
      last_page = pg_no(start); 
    }

    if (*start == '\0')
      return true;   

    ++start;    
  }
}


void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

bool is_valid_fd(int fd) {
  return fd >= 2 && fd < MAP_SIZE && map_get(&thread_current()->fd_table, fd) != NULL;
}

int read(int fd, void *buffer, unsigned length){
  if (fd == STDIN_FILENO) {
    char *buf = (char *) buffer;
    for (unsigned i = 0; i < length; i++) {
      buf[i] = input_getc();
      if (buf[i] == '\r') {
        buf[i] = '\n';
      }
      putbuf(&buf[i], 1); 
    }
    return length;
  }

  if (is_valid_fd(fd)) {
    struct file *f = map_get(&thread_current()->fd_table, fd);
    return file_read(f, buffer, length);
  }

  return -1;
}

int write(int fd, const void *buffer, unsigned length) {
  if (fd == STDOUT_FILENO) {
    const char *buf = (const char *) buffer;
    putbuf(buf, length);
    return length;
  }

  if (is_valid_fd(fd)) {
    struct file *f = map_get(&thread_current()->fd_table, fd);
    return file_write(f, buffer, length);
  }

  return -1;
}

int open(const char *name){
  if (name == NULL) return -1;

  struct file *f = filesys_open(name);
  if (f == NULL) return -1;

  int fd = map_put(&thread_current()->fd_table, f);
  if (fd == -1) {
    file_close(f);
    return -1;
  }

  return fd;
}

void close(int fd){
  if (is_valid_fd(fd)) {
    struct file *f = map_get(&thread_current()->fd_table, fd);
    map_remove(&thread_current()->fd_table, fd);
    file_close(f);
  }
}

void seek(int fd, unsigned position){
  if (is_valid_fd(fd)) {
    struct file *f = map_get(&thread_current()->fd_table, fd);
    unsigned limit = file_length(f);
    if (position <= limit) {
      file_seek(f, position);
    }
  }
}

int filesize(int fd){
  if (is_valid_fd(fd)) {
    struct file *f = map_get(&thread_current()->fd_table, fd);
    return file_length(f);
  }
  return -1;
}

unsigned tell(int fd){
  if (is_valid_fd(fd)) {
    struct file *f = map_get(&thread_current()->fd_table, fd);
    return file_tell(f);
  }
  return (unsigned)-1;
}

bool create(const char *name, unsigned size){
  if (name == NULL) return false;
  return filesys_create(name, size);
}

bool remove(const char *name){
  if (name == NULL) return false;
  return filesys_remove(name);
}

void plist (void){
  plist_print();
}

void sleep (int milliseconds){
  timer_msleep(milliseconds); 
}

pid_t exec(const char *file){
  return process_execute(file); 
}

int wait(pid_t child){
  return process_wait(child); 
} 
/* This array defined the number of arguments each syscall expects.
   For example, if you want to find out the number of arguments for
   the read system call you shall write:

   int sys_read_arg_count = argc[ SYS_READ ];

   All system calls have a name such as SYS_READ defined as an enum
   type, see `lib/syscall-nr.h'. Use them instead of numbers.
 */
const int argc[] = {
  /* basic calls */
  0, 1, 1, 1, 2, 1, 1, 1, 3, 3, 2, 1, 1,
  /* not implemented */
  2, 1,    1, 1, 2, 1, 1,
  /* extended, you may need to change the order of these two (plist, sleep) */
  0, 1
};

static void
syscall_handler (struct intr_frame *f)
{
  // tolka user stack som en array av 32-bitars heltal 
  int32_t* esp = (int32_t*)f->esp;

  // tests/userprog/wait-killed
  // esp pekar på systemanropnummer i farligt område
  if(!verify_fix_length(esp, sizeof(*esp)))
    thread_exit(); 

  // tests/filst/sc-bad-nr-1
  // tests/filst/sc-bad-nr-2
  // tests/filst/sc-bad-nr-3
  if(esp[0] < 0 || esp[0] >= SYS_NUMBER_OF_CALLS)
    thread_exit(); 
  
  // tests/userprog/sc-bad-arg
  // systemanrop placerad i slutet på user-space och argument palcerade i kernel-space eller utanför trådens pagedir
  int syscall_nr = esp[0]; 
  int num_args = argc[syscall_nr];
  if (!verify_fix_length(esp, (num_args +1) * sizeof(*esp)))
    thread_exit();

  switch (esp[0])
  {
    case SYS_HALT:
      power_off(); 
      break;
    
    case SYS_EXIT:  
    {
      int status = esp[1];
      //printf("exit status: %d\n", status); 
      process_exit(status);
      thread_exit();
      break;
    }

    case SYS_READ: 
    {
      int fd = esp[1];
      void *buffer = (void *) esp[2]; 
      unsigned length = (unsigned) esp[3]; 

      if(!verify_fix_length(buffer, length))
        thread_exit(); 

      f->eax = read(fd, buffer, length);
      break; 
    }

    case SYS_WRITE: 
    {
      int fd = esp[1]; 
      void *buffer = (void *) esp[2];
      unsigned length = (unsigned) esp[3]; 

      if(!verify_fix_length(buffer, length))
        thread_exit(); 

      f->eax = write(fd, buffer, length); 
      break; 
    }

    case SYS_OPEN:
    {
      const char *name = (char*) esp[1];

      if(!verify_variable_length(name))
        thread_exit();  

      f->eax = open(name);
      break; 
    }
    
    case SYS_CLOSE:
    {
      int fd = esp[1]; 
      close(fd);
      break; 
    }

    case SYS_REMOVE: 
    {
      const char *name = (char *) esp[1];

      if(!verify_variable_length(name))
        thread_exit(); 

      f->eax = remove(name); 
      break;  
    }

    case SYS_FILESIZE:
    {
      int fd = esp[1];
      f->eax = filesize(fd);
      break;
    }

    case SYS_SEEK:
    {
      int fd = esp[1];
      unsigned position = (unsigned) esp[2]; 
      seek(fd, position);
      break; 
    }

    case SYS_TELL:
    {
      int fd = esp[1]; 
      f->eax = tell(fd);
      break; 
    }

    case SYS_CREATE: 
    {
      const char *name = (char *) esp[1];
      unsigned size = (unsigned) esp[2]; 

      if(!verify_variable_length(name))
        thread_exit();  

      f->eax = create(name, size); 
      break;
    }

    case SYS_PLIST:
    {
      plist();
      f->eax = 0;
      break;
    }

    case SYS_SLEEP:
    {
      sleep(esp[1]);  
      f->eax = 0;
      break;
    }

    case SYS_EXEC: 
    {
      const char *file = (char *) esp[1];

      if(!verify_variable_length(file))
        thread_exit(); 

      f->eax = exec(file); 
      break; 
    }

    case SYS_WAIT:
    {
      int child = esp[1];
      f->eax = wait(child); 
      break; 
    }

    default:
      printf ("Executed an unknown system call!\n");
      thread_exit ();
      break; 
  }
}
