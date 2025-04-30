#include "hashmap.h"

void insert(int key, stat_agg_t value, HashItem* hashmap) {
    HashItem *item = malloc(sizeof(HashItem));
    item->key = key;
    item->value = value;
    HASH_ADD_INT(hashmap, key, item);
}

HashItem* find(int key, HashItem* hashmap) {
    HashItem *item = NULL;
    HASH_FIND_INT(hashmap, &key, item);
    return item;
}

void delete(int key, HashItem* hashmap) {
    HashItem *item = find(key, hashmap);
    if (item) {
        HASH_DEL(hashmap, item);
        free(item);
    }
}

void cleanup(HashItem* hashmap) {
    HashItem *current_item, *tmp;
    HASH_ITER(hh, hashmap, current_item, tmp) {
        HASH_DEL(hashmap, current_item);
        free(current_item);
    }
}
