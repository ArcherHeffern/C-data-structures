#include <stdio.h>
#include <stdlib.h>

struct ArrayList {
	int *list;
	int size; 
	int capacity;
};

struct ArrayList* list_create(int capacity) {
	struct ArrayList* list = malloc(sizeof(struct ArrayList));
	list->list = malloc(capacity * sizeof(int));
	list->size = 0;
	list->capacity = capacity;
	return list;
}

void list_destroy(struct ArrayList *list) {
	free(list->list);
	free(list);
}

void list_add(struct ArrayList *list, int value) {
	if (list->size == list->capacity) {
		list->capacity *= 2;
		int *new_list = malloc(sizeof(int)*list->capacity);
		for (int i = 0; i < list->size; i++) {
			new_list[i] = list->list[i];
		}
		list->list = new_list;
	}
	list->list[list->size] = value;
	list->size++;
}

int list_get(struct ArrayList *list, int index) {
	return list->list[index];
}

void list_set(struct ArrayList *list, int index, int value) {
	list->list[index] = value;
}

int list_size(struct ArrayList *list) {
	return list->size;
}

int list_remove(struct ArrayList *list, int index) {
	int removed = list->list[index];
	for (int i = index+1; i < list->size; i++) {
		list->list[i-1] = list->list[i];
	}
	list->size--;
	return removed;
}

void list_swap(struct ArrayList *list, int index1, int index2) {
	int tmp = list_get(list, index1);
	list_set(list, index1, list_get(list, index2));
	list_set(list, index2, tmp);
}

void list_print(struct ArrayList *list) {
	if (list->size == 0) {
		printf("(empty)");
	}
	for (int i = 0; i < list->size; i++) {
		printf("%d, ", list->list[i]);
	}
	printf("\n");
}

// int main() {
// 	struct ArrayList *list = list_create(2);
// 	list_print(list);
// 	for (int i = 0; i < 10; i++) {
// 		list_add(list, i);
// 	}
// 	list_print(list);
// 	list_remove(list, 0);
// 	list_remove(list, list->size-1);
// 	list_print(list);
// 	list_destroy(list);
// }
