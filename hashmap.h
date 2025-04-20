
#ifndef __HASHMAP_H_
#define __HASHMAP_H_

struct HashMap;

struct HashMap* 	hashmap_create();
void 				hashmap_destroy(struct HashMap *hashmap);
bool 				hashmap_get(struct HashMap *hashmap, int key, int *value);
void 				hashmap_insert(struct HashMap *hashmap, int key, int value);
bool 				hashmap_remove(struct HashMap *hashmap, int key);

#endif // __HASHMAP_H_

