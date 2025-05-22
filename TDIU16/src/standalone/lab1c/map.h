#ifndef MAP_H
#define MAP_H

#include <stdbool.h>
#include <stddef.h>

typedef int key_t;
typedef char* value_t;

/* symbolisk konstant för att enkelt kunna ändra storleken senare vid behov */
#define MAP_SIZE 32  

struct map {
    value_t content[MAP_SIZE];  
};

void map_init(struct map* m); 
key_t map_insert(struct map* m, value_t v); 
value_t map_find(struct map* m, key_t k);
value_t map_remove(struct map* m, key_t k);
void map_for_each(struct map* m, void (*exec)(key_t k, value_t v, int aux), int aux);
void map_remove_if(struct map* m, bool (*cond)(key_t k, value_t v, int aux), int aux);

#endif // MAP_H