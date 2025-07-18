#include "wrap/thread.h"
#include "wrap/synch.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Denna struktur representerar innehållet i vår (stora) datafil.
 */
struct data_file {
  // Hur många gånger har filen blivit öppnad?
  int open_count;

  // Filens ID.
  int id;

  // Data i filen.
  char *data;

  struct lock file_lock; 
};

// Håll koll på den fil vi har öppnat. Om ingen fil är öppen är denna variabel NULL.
// Tänk er att detta är en array av två pekare, dvs. struct data_file *open_files[2];
struct data_file **open_files;
struct lock open_file_lock; 
// Initiera de datastrukturer vi behöver. Anropas en gång i början.
void data_init(void) NO_STEP {
  open_files = malloc(sizeof(struct data_file *)*2);
  lock_init(&open_file_lock); 
}

// Öppna datafilen med nummer "file" och se till att den finns i RAM. Om den
// redan råkar vara öppnad ger funktionen tillbaka en pekare till instansen som
// redan var öppen. Annars laddas filen in i RAM.
struct data_file *data_open(int file) {
  lock_acquire(&open_file_lock); 
  struct data_file *result = open_files[file];
  if (result == NULL) {
    // Skapa en ny data_file.
    result = malloc(sizeof(struct data_file));
    lock_init(&result->file_lock); 
    result->open_count = 1;
    result->id = file;

    // Simulera att vi läser in data...
    timer_msleep(100);
    if (file == 0)
      result->data = strdup("File 0");
    else
      result->data = strdup("File 1");

    // Spara data i "open_files".
    open_files[file] = result;
  } else {
    // Se till att datafilen behöver öppnas igen.
    data_reopen(result);
  }
  lock_release(&open_file_lock); 
  return result;
}

// Öppna en datafil som redan är öppen, så att den kan ges vidare till en annan
// del av systemet som kör close senare.
void data_reopen(struct data_file *file) {
  lock_acquire(&file->file_lock); 
  file->open_count++;
  lock_release(&file->file_lock); 
}

// Stäng en datafil. Om ingen annan har filen öppen ska filen avallokeras för
// att spara minne.
void data_close(struct data_file *file) {
  lock_acquire(&open_file_lock);
  lock_acquire(&file->file_lock);
  int open_count = --file->open_count;
  if (open_count <= 0) {
    // Ingen har filen öppen längre. Då kan vi ta bort den!
    open_files[file->id] = NULL;
    free(file->data);
    lock_release(&file->file_lock); 
    free(file);
  }else {
    lock_release(&file->file_lock); 
  }
  lock_release(&open_file_lock); 
}


/**
 * Testprogram.
 *
 * Med en korrekt implementation av funktionerna ovan ska du inte behöva ändra i
 * dessa funktioner. Det kan dock vara intressant att modifiera koden nedan för
 * att kunna testa bättre.
 */

// Semaphore to ensure that the integers are not used after they are freed.
struct semaphore data_sema;

void thread_main(int *file_id) {
  struct data_file *f = data_open(*file_id);
  data_reopen(f);
  printf("Data: %s\n", f->data);
  data_close(f);
  printf("Data: %s\n", f->data);
  data_close(f);
  sema_up(&data_sema);
}

int main(void) {
  sema_init(&data_sema, 0);
  data_init();

  int zero = 0;
  int one = 1;
  thread_new(&thread_main, &zero);
  thread_new(&thread_main, &one);

  thread_main(&zero);

  // Wait for other threads to be done.
  for (int i = 0; i < 3; i++)
    sema_down(&data_sema);

  return 0;
}
