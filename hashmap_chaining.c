#include <stdio.h>
#include <stdlib.h>

#define HASHMAP_CAPACITY 10

struct HashNode {
	int key;
	char* value;
	struct HashNode *next;
};

struct HashMap {
	struct HashNode* hashmap[HASHMAP_CAPACITY];
};

struct HashMap* hashmap_create() {
	struct HashMap* hashmap = malloc(sizeof(struct HashMap));
	for (int i = 0; i < HASHMAP_CAPACITY; i++) {
		hashmap->hashmap[i] = NULL;
	}
	return hashmap;
}

void hashmap_destroy(struct HashMap* hashmap) {
	for (int i = 0; i < HASHMAP_CAPACITY; i++) {
		if (hashmap->hashmap[i] != NULL) {
			free(hashmap->hashmap[i]);
		}
	}
	free(hashmap);
}

int hash(int h) {
	return h;
}

void hashmap_insert(struct HashMap* hashmap, int key, char* value) {
	int index = hash(key) % HASHMAP_CAPACITY;
	struct HashNode **cur_node = &hashmap->hashmap[index];
	while (*cur_node != NULL) {
		if ((*cur_node)->key == key) {
			(*cur_node)->value = value;
			return;
		}
		cur_node = &(*cur_node)->next;
	}
	*cur_node = malloc(sizeof(struct HashNode));
	(*cur_node)->key = key;
	(*cur_node)->value = value;
	(*cur_node)->next = NULL;
}

char* hashmap_get(struct HashMap* hashmap, int key) {
	int index = hash(key) % HASHMAP_CAPACITY;
	struct HashNode *node = hashmap->hashmap[index];
	while (node != NULL) {
		if (node->key == key) {
			return node->value;
		}
		node = node->next;
	}
	return NULL;
}



int main() {
	struct HashMap *hm = hashmap_create();
	char* letters = "abcdefghijklmnopqrstuvwxyz";
	for (int i = 0; i < 26; i++) {
		hashmap_insert(hm, i, letters+i);
		printf("%s\n", hashmap_get(hm, i));
	}
	hashmap_destroy(hm);
}
