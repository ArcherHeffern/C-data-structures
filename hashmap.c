#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hashmap.h"

#define MAX_BALANCE_FACTOR (0.7)
#define DEFAULT_CAPACITY 1

void __hashmap_insert(struct HashMap *hashmap, struct HashMapNode* node);
struct HashMapNode** hashmap_get_target_node(struct HashMap *hashmap, int key, bool stop_on_deleted);
void hashmap_resize(struct HashMap *hashmap, int new_capacity);

struct HashMapNode {
	int key;
	int value;
	bool deleted;
};

struct HashMap {
	struct HashMapNode **hashmap;
	int capacity;
	int size;
};

float hashmap_balance_factor(struct HashMap *hashmap) {
	return hashmap->size / hashmap->capacity;
}

bool hashmap_should_resize(struct HashMap *hashmap) {
	return hashmap_balance_factor(hashmap) >= MAX_BALANCE_FACTOR || hashmap->size >= hashmap->capacity;
}

struct HashMap* hashmap_create() {
	struct HashMap *hashmap = malloc(sizeof(struct HashMap));
	hashmap->hashmap = malloc(sizeof(struct HashMapNode*) * DEFAULT_CAPACITY);
	memset(hashmap->hashmap, 0, sizeof(struct HashMapNode) * DEFAULT_CAPACITY);
	hashmap->capacity = DEFAULT_CAPACITY;
	hashmap->size = 0; 
	return hashmap;
}

void hashmap_destroy(struct HashMap *hashmap) {
	free(hashmap->hashmap);
	free(hashmap);
}

int hash(int num) {
	return num;
}

void hashmap_insert(struct HashMap *hashmap, int key, int value) {
	struct HashMapNode *node = malloc(sizeof(struct HashMapNode));
	node->key = key;
	node->value = value;
	node->deleted = false;
	if (hashmap_should_resize(hashmap)) {
		printf("Hashmap resize\n");
		hashmap_resize(hashmap, hashmap->capacity*2);
	}
	__hashmap_insert(hashmap, node);
	hashmap->size++;
}

void hashmap_resize(struct HashMap *hashmap, int new_capacity) {
	int old_capacity = hashmap->capacity;
	struct HashMapNode** old_hashmap = hashmap->hashmap;
	hashmap->capacity *= 2;
	size_t new_hashmap_bytes = sizeof(struct HashMapNode*)*hashmap->capacity;
	hashmap->hashmap = malloc(new_hashmap_bytes);
	memset(hashmap->hashmap, 0, new_hashmap_bytes);

	for (int i = 0; i < old_capacity; i++) {
		if (old_hashmap[i] != NULL) {
			__hashmap_insert(hashmap, old_hashmap[i]);
		}
	}
	free(old_hashmap);
}

void __hashmap_insert(struct HashMap *hashmap, struct HashMapNode* node) {
	/// May free node
	/// Assumes there is enough space in the hashmap
	struct HashMapNode **node_p = hashmap_get_target_node(hashmap, node->key, true);
	if (*node_p == NULL) {
		*node_p = node;
		return;
	}
	(*node_p)->value = node->value;
	(*node_p)->deleted = false;
	free(node);
}

bool hashmap_remove(struct HashMap *hashmap, int key) {
	/// Returns true if item was removed. False if no such key exists
	struct HashMapNode** node = hashmap_get_target_node(hashmap, key, false);
	if (node == NULL || *node == NULL) {
		return false;
	}
	(*node)->deleted = true;
	return true;
}

struct HashMapNode** hashmap_get_target_node(struct HashMap *hashmap, int key, bool stop_on_deleted) {
	/// Returns 
	/// * NULL if hashmap is full
	/// * pointer to first free slot
	/// * pointer to node with same key
	int start_index = hash(key) % hashmap->capacity;
	int index = start_index;
	while (hashmap->hashmap[index] != NULL && 
			(hashmap->hashmap[index]->key != key
			|| hashmap->hashmap[index]->deleted)
			) {
		if (hashmap->hashmap[index]->deleted && stop_on_deleted) {
			break;
		}
		index = (index+1) % hashmap->capacity;
		if (index == start_index) {
			return NULL;
		}
	}
	return &hashmap->hashmap[index];
}
bool hashmap_get(struct HashMap *hashmap, int key, int *value) {
	struct HashMapNode** node = hashmap_get_target_node(hashmap, key, false);
	if (node == NULL || *node == NULL)
		return false;
	*value = (*node)->value;
	return true;
}

void assert_get(struct HashMap *hashmap, int key, int *expected_value) {
	int value;
	bool ok = hashmap_get(hashmap, key, &value);
	if (ok && expected_value == NULL) {
		printf("Expected get(%d)=NULL but found get(%d)=%d\n", key, key, value);
	} else if (!ok && expected_value != NULL) {
		printf("Expected get(%d)=%d but found get(%d)=NULL\n", key, *expected_value, key);
	}
}

int main() {
	struct HashMap *hashmap = hashmap_create();
	for (int i = 0; i < 100; i++) {
		int value = i+1;
		printf("set(%d)=%d\n", i, value);
		hashmap_insert(hashmap, i, value);
		assert_get(hashmap, i, &value);
	}
	assert_get(hashmap, -1, NULL);
	assert_get(hashmap, 101, NULL);
	for (int i = 0; i < 100; i++) {
		printf("delete(%d)\n", i);
		hashmap_remove(hashmap, i);
		assert_get(hashmap, i, NULL);
	}
	for (int i = 0; i < 100; i++) {
		int value = i+1;
		printf("set(%d)=%d\n", i, value);
		hashmap_insert(hashmap, i, value);
		assert_get(hashmap, i, &value);
	}
}
