#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

typedef int pid_t; 

void syscall_init (void);
int read(int fd, void *buffer, unsigned length);
int write(int fd, const void *buffer, unsigned length);
bool create(const char *name, unsigned size);
bool remove(const char *name);
int open(const char *name);
void close(int fd);
int filesize(int fd);
void seek(int fd, unsigned position);
unsigned tell(int fd);
bool is_valid_fd(int fd);
void plist (void);
void sleep (int milliseconds);
pid_t exec(const char *file);
int wait(pid_t child);

#endif /* userprog/syscall.h */
