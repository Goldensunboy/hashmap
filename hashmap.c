/* Andrew Wilder */

#include <stdlib.h>
#include "hashmap.h"

#define INITIAL_SIZE 10
#define MAX_LOAD_SIZE 0.75

struct hashmap_bucket {
	void *key;
	void *value;
	struct hashmap_bucket *next;
};

struct hashmap_metadata {
	struct hashmap_bucket *bucket_arr;
	int bucket_count;
	hash_func_t hash_func;
	equal_func_t equal_func;
	free_func_t key_free_func;
	free_func_t value_free_func;
};

struct hashmap *create_hashmap(hash_func_t hfunc, equal_func_t efunc, free_func_t kffunc, free_func_t vffunc) {
	struct hashmap *hmap = calloc(1, sizeof(struct hashmap));
	hmap->meta = malloc(sizeof(struct hashmap_metadata));
	hmap->meta->bucket_arr = calloc(INITIAL_SIZE, sizeof(struct hashmap_bucket));
	hmap->meta->bucket_count = INITIAL_SIZE;
	hmap->meta->hash_func = hfunc;
	hmap->meta->equal_func = efunc;
	hmap->meta->key_free_func = kffunc;
	hmap->meta->value_free_func = vffunc;
	return hmap;
}

int hashmap_put(struct hashmap *hmap, void *key, void *value) {
	return 0;
}

void *hashmap_get(struct hashmap *hmap, void *key) {
	return NULL;
}

