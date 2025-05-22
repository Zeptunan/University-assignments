#include <stddef.h>
#include <stdio.h>
#include "plist.h"

static struct p_list plist;

void plist_init(void)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        plist.table[i].in_use = false;
        sema_init(&plist.table[i].p_sema, 0);
        lock_init(&plist.table[i].plist_lock);
    }
}

int plist_insert(int child_pid, int parent_pid)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        lock_acquire(&plist.table[i].plist_lock);
        if (!plist.table[i].in_use) {
            plist.table[i].in_use = true;
            plist.table[i].child_pid = child_pid;
            plist.table[i].parent_pid = parent_pid;
            plist.table[i].alive = true;
            plist.table[i].parent_alive = true; 
            plist.table[i].waited_on = false;
            plist.table[i].exit_status = -1;
            lock_release(&plist.table[i].plist_lock);
            return i;
        }
        lock_release(&plist.table[i].plist_lock);
    }
    return -1;
}

struct p_info* plist_get(int pid)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        lock_acquire(&plist.table[i].plist_lock);
        if (plist.table[i].in_use &&
            plist.table[i].child_pid == pid) {
            lock_release(&plist.table[i].plist_lock);
            return &plist.table[i];
        }
        lock_release(&plist.table[i].plist_lock);
    }
    return NULL;
}

bool plist_remove(int pid)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        lock_acquire(&plist.table[i].plist_lock);
        if (plist.table[i].in_use &&
            plist.table[i].child_pid == pid) {
            plist.table[i].in_use = false;
            lock_release(&plist.table[i].plist_lock);
            return true;
        }
        lock_release(&plist.table[i].plist_lock);
    }
    return false;
}

struct p_info* plist_wait(int child_pid, int parent_pid){
    struct p_info *info = plist_get(child_pid);
    if (!info || info->parent_pid != parent_pid || info->waited_on)
        return NULL;

    sema_down(&info->p_sema);
    info->waited_on = true;
    return info;
}

void plist_mark_orphans(int parent_pid)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        lock_acquire(&plist.table[i].plist_lock);
        if (plist.table[i].in_use && plist.table[i].parent_pid == parent_pid){
            plist.table[i].parent_alive = false;
        }   
        lock_release(&plist.table[i].plist_lock);
    } 
}

void plist_remove_dead_orphans(void)
{
    for (int i = 0; i < TABLE_SIZE; i++) {
        lock_acquire(&plist.table[i].plist_lock);
        if (plist.table[i].in_use &&
            !plist.table[i].alive &&
            !plist.table[i].parent_alive){
            plist.table[i].in_use = false;
        }
        lock_release(&plist.table[i].plist_lock);  
    }  
}


void plist_print(void)
{
    printf("Index | Child | Parent | Exit | Alive | Waited\n");
    printf("----------------------------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (plist.table[i].in_use) {
            printf("%5d | %5d | %6d | %4d | %5s | %6s\n",
                   i,
                   plist.table[i].child_pid,
                   plist.table[i].parent_pid,
                   plist.table[i].exit_status,
                   plist.table[i].alive     ? "yes" : "no",
                   plist.table[i].waited_on ? "yes" : "no");
        }
    }
}
