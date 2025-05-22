#ifndef _PLIST_H_
#define _PLIST_H_

#include <stdbool.h>
#include <stddef.h>
#include "threads/synch.h"

typedef struct p_info p_info;
typedef struct p_list p_list;

#define TABLE_SIZE 512

struct p_info { 
  int parent_pid; 
  int child_pid; 
  int exit_status; // vad processen returnerar vid exit
  struct semaphore p_sema; 
  bool alive; // lever processen? 
  bool parent_alive; 
  bool waited_on; // förhindrar dubbel wait om en wait redan finns på barn
  bool in_use; // om ett index i listan används eller inte 
  struct lock plist_lock;
};

struct p_list {
  p_info table[TABLE_SIZE];  
};

void plist_init(void); 
int plist_insert(int child_pid, int parent_pid); 
struct p_info* plist_get(int pid);
bool plist_remove(int pid);
void plist_print(void);
struct p_info* plist_wait(int child_pid, int parent_pid); 
void plist_mark_orphans(int parent_pid);
void plist_remove_dead_orphans(void);
#endif
