
#ifndef __ARRAYLIST_H
#define __ARRAYLIST_H

struct ArrayList;

struct ArrayList* 	list_create(int capacity);
void 				list_destroy(struct ArrayList *list);
void 				list_add(struct ArrayList *list, int value);
int 				list_get(struct ArrayList *list, int index);
void 				list_set(struct ArrayList *list, int index, int value);
int 				list_size(struct ArrayList *list);
int 				list_remove(struct ArrayList *list, int index);
void 				list_swap(struct ArrayList *list, int index1, int index2);
void 				list_print(struct ArrayList *list);

#endif // __ARRAYLIST_H
