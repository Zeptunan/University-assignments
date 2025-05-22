#include <stddef.h>

#include "flist.h"

void map_init(struct map* m) {
    for(int i = 0; i < MAP_SIZE; i++){
        m->content[i] = NULL;
    }
}

fd_t map_put(struct map* m, file_t v){
    for(int i = 2; i < MAP_SIZE; i++){
        if(m->content[i] == NULL) {
            m->content[i] = v; 
            return i; //fd_t
        }
    }
    return -1; 
}

file_t map_get(struct map* m, fd_t k) {
    if(k < 0 || k >= MAP_SIZE)
        return NULL;

    if(m->content[k] != NULL)
        return m->content[k];
    
    return NULL; 
}

file_t map_remove(struct map* m, fd_t k){
    if(k < 0 || k >= MAP_SIZE)
        return NULL;

    file_t removed = NULL;
    if(m->content[k] != NULL){
        removed = m->content[k];
        m->content[k] = NULL;
        return removed; 
    }

    return NULL; 
}

void map_for_each(struct map* m, void (*exec)(fd_t k, file_t v, int aux), int aux){
   for(int i = 0; i < MAP_SIZE; i++){
        if(m->content[i] != NULL){
            exec(i, m->content[i], aux);
        }
   }
}

void map_remove_if(struct map* m, bool (*cond)(fd_t k, file_t v, int aux), int aux){
    for(int i = 0; i < MAP_SIZE; i++){
        if(m->content[i] != NULL){
            if(cond(i, m->content[i], aux) == true){
                m->content[i] = NULL; 
            }
        }
    }
}
