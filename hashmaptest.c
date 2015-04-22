/* Andrew Wilder */

#include <assert.h>
#include <stdlib.h>
#include "hashmap.h"

void *int_create(int val) {
	int *ptr = (int*) malloc(sizeof(int));
	*ptr = val;
	return ptr;
}

int int_hash(const void *data) {
	return *(int*) data;
}

int int_equal(const void *data1, const void *data2) {
	return *(int*) data1 == *(int*) data2;
}

void int_free(void *data) {
	free(data);
}

int main() {

	// Add 5 elements to a hashmap
	hashmap_t *hmap1 = hashmap_create(int_hash, int_equal, int_free, int_free, CP_FREE_OLD_ENTRY);

	int i;
	for(i = 1; i <= 5; ++i) {
		hashmap_put(hmap1, int_create(i), int_create(6 - i));
	}
	for(i = 1; i <= 5; ++i) {
		int *ptr = hashmap_get(hmap1, &i);
		assert(*ptr == 6 - i);
	}
	assert(hashmap_get(hmap1, &i) == NULL);
	assert(hmap1->size == 5);
	assert(hmap1->load_factor == 0.5);
	hashmap_destroy(hmap1);

	// Add 10 elements to a hashmap
	hashmap_t *hmap2 = hashmap_create(int_hash, int_equal, int_free, int_free, CP_FREE_OLD_ENTRY);

	for(i = 1; i <= 10; ++i) {
		hashmap_put(hmap2, int_create(i), int_create(11 - i));
	}
	for(i = 1; i <= 10; ++i) {
		int *ptr = hashmap_get(hmap2, &i);
		assert(*ptr == 11 - i);
	}
	assert(hashmap_get(hmap2, &i) == NULL);
	assert(hmap2->size == 10);
	assert(hmap2->load_factor == 0.5);
	hashmap_destroy(hmap2);

	return 0;
}
