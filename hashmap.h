/* Andrew Wilder */

struct hashmap_metadata;

typedef struct hashmap {
	int size;
	double loadfactor;
	struct hashmap_metadata meta;
} hashmap_t;

typedef int (*hash_func_t)(const void*);
typedef int (*equal_func_t)(const void*, const void*);
typedef void (*free_func_t)(void*);

struct hashmap *create_hashmap(hash_func_t, equal_func_t, free_func_t);
void hashmap_put(struct hashmap*, void *key, void *value);
void *hashmap_get(struct hashmap*, void *key);

