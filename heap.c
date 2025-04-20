#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"
#include "heap.h"

void heap_heapify(struct ArrayList *list) {
	for (int i = 1; i < list_size(list); i++) {
		heapify_up(list, i);
	}
}

void heap_insert(struct ArrayList *heap, int value) {
	list_add(heap, value);
	heapify_up(heap, list_size(heap)-1);
}

int heap_pop(struct ArrayList *heap) {
	list_swap(heap, 0, list_size(heap)-1);
	int removed = list_remove(heap, list_size(heap)-1);
	heapify_down(heap, 0);
	return removed;
}

int heap_peek(struct ArrayList *heap) {
	return list_get(heap, 0);
}

void heapify_up(struct ArrayList *heap, int index) {
	/// Assumes index is the only value not abiding by heap invariant
	while (index != 0) {
		int parent = (index-1)/2;
		if (list_get(heap, index) <= list_get(heap, parent)) {
			return;
		}
		list_swap(heap, index, parent);
		index = parent;
	}
}

void heapify_down(struct ArrayList *heap, int index) {
	/// Assumes index is the only value not abiding by heap invariant
	int left_index = index*2+1;
	int right_index = left_index+1;
	while (left_index < list_size(heap)) {
		int greater_value_index = left_index;
		if (right_index < list_size(heap) && list_get(heap, right_index) > list_get(heap, left_index)) {
			greater_value_index = right_index;
		} 
		if (list_get(heap, index) >= list_get(heap, greater_value_index)) {
			return;
		}
		list_swap(heap, index, greater_value_index);
		index = greater_value_index;
		left_index = index*2+1;
		right_index = left_index+1;
	}
}

int main() {
	struct ArrayList *list = list_create(2);
	for (int i = 0; i < 10; i++) {
		list_add(list, i);
	}
	list_print(list);
	heap_heapify(list);
	for (int i = 10; i < 20; i++) {
		heap_insert(list, i);
	}
	list_print(list);
	 while (list_size(list) > 0) {
		printf("%d\n", heap_pop(list));
	}
}
