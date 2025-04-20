
#ifndef __HEAP_H
#define __HEAP_H

void heap_heapify(struct ArrayList *list);
void heap_insert(struct ArrayList *heap, int value);
int heap_pop(struct ArrayList *heap);
int heap_peek(struct ArrayList *heap);
void heapify_up(struct ArrayList *heap, int index);
void heapify_down(struct ArrayList *list, int index);

#endif // __HEAP_H
