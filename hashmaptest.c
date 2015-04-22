/* Andrew Wilder */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

struct car_t {
	char *model;
	int year;
};

struct person_t {
	char *first_name;
	char *last_name;
	int age;
};

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

void *person_create(int rand_val) {
	const char *fname = ((const char*[]) {
		"Andrew",
		"John",
		"Mark",
		"Elliot",
		"Thomas",
		"Chris",
		"Debra",
		"Nick",
		"Samantha",
		"Pratik",
		"Lopez"
	}) [rand_val % 11];
	int reverse = 0;
	for(int i = 32; i; --i) {
		reverse <<= 1;
		reverse |= rand_val & 1;
		rand_val >>= 1;
	}
	const char *lname = ((const char*[]) {
		"Brown",
		"Washington",
		"Smith",
		"Braswell",
		"Wilder",
		"Hwang",
		"Rosenblume",
		"Golden",
		"Graham",
		"Rogers",
		"Popescu"
	}) [reverse % 11];
	struct person_t *person = malloc(sizeof(struct person_t));
	person->first_name = (char*) fname;
	person->last_name = (char*) lname;
	person->age = 18 + (reverse >> 15) % 17;
	return person;
}

int person_hash(const void *data) {
	struct person_t *person = (struct person_t*) data;
	int ret = person->age << 8;
	char *ptr = person->first_name;
	while(ptr) {
		ret ^= *ptr++;
		for(int i = 7; i; --i) {
			int bit = (ret >> 31) & 1;
			ret <<= 1;
			ret |= bit;
		}
	}
	ptr = person->last_name;
	while(ptr) {
		ret ^= *ptr++;
		for(int i = 5; i; --i) {
			int bit = ret & 1;
			ret >>= 1;
			ret = (ret & 0x7FFFFFFF) | (bit << 31);
		}
	}
	return ret;
}

void person_free(void *data) {
	struct person_t *person = (struct person_t*) data;
	free(person->first_name);
	free(person->last_name);
	free(person);
}

int person_equal(const void *data1, const void *data2) {
	struct person_t *p1 = (struct person_t*) data1;
	struct person_t *p2 = (struct person_t*) data2;
	return p1->age == p2->age && !strcmp(p1->first_name, p2->first_name) && !strcmp(p1->last_name, p2->last_name);
}

void *car_create(int rand_val) {
	const char *model = ((const char*[]) {
		"Nissan",
		"Honda",
		"Toyota",
		"Tesla",
		"Roadster",
		"BMW",
		"Mercedes",
		"Jaguar",
		"Audi",
		"Chysler",
		"F150"
	}) [rand_val % 11];
	struct car_t *car = malloc(sizeof(struct car_t));
	car->model = strdup(model);
	car->year = 1915 + rand_val % 100;
	return car;
}

int car_hash(const void *data) {
	struct car_t *car = (struct car_t*) data;
	int ret = car->year << 8;
	char *ptr = car->model;
	while(ptr) {
		ret ^= *ptr++;
		for(int i = 7; i; --i) {
			int bit = (ret >> 31) & 1;
			ret <<= 1;
			ret |= bit;
		}
	}
	return ret;
}

int car_equal(const void *data1, const void *data2) {
	struct car_t *car1 = (struct car_t*) data1;
	struct car_t *car2 = (struct car_t*) data2;
	return car1->year == car2->year && !strcmp(car1->model, car2->model);
}

void car_free(void *data) {
	struct car_t *car = (struct car_t*) data;
	free(car->model);
	free(car);
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

	// Add 1000 elements to a hashmap
	srand(0x4F810C7B);
	struct person_t **key_arr = malloc(1000 * sizeof(void*));
	struct car_t **value_arr = malloc(1000 * sizeof(void*));
	hashmap_t *hmap3 = hashmap_create(person_hash, person_equal, person_free, car_free, CP_FREE_OLD_ENTRY);
	for(int i = 0; i < 1000; ++i) {
		key_arr[i] = person_create(rand());
		value_arr[i] = car_create(rand());
		hashmap_put(hmap3, key_arr[i], value_arr[i]);
	}
	for(int i = 0; i < 1000; ++i) {
		assert(car_equal(hashmap_get(hmap3, key_arr[i]), value_arr[i]));
	}
	void *something = malloc(4);
	assert(hashmap_get(hmap3, something) == NULL);
	free(something);
	assert(hmap3->size == 1000);
	assert(hmap3->load_factor == 1000 / 2560.0);
	hashmap_destroy(hmap3);
	free(key_arr);
	free(value_arr);

	return 0;
}
