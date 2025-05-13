#include "hashmap.h"
/**
 * Inserts an item into a hashmap
 *
 * @param key an int corresponding to the player_id to insert on the hashmap
 * @param value a pointer to a stat agg object which is the value
 * @param hashmap double pointer to the hashmap
 */
void insert(int key, stat_agg_t *value, HashItem **hashmap) {
  HashItem *item = malloc(sizeof(HashItem));
  item->key = key;
  item->value = value;
  HASH_ADD_INT(*hashmap, key, item);
}

/**
 * Attempt to find an item in the hashmap
 *
 * @param key an int corresponding to the player_id to find in the hashmap
 * @param hashmap double pointer to the hashmap
 * @return a hashitem if the player is found in the map
 */
HashItem *find(int key, HashItem **hashmap) {
  HashItem *item = NULL;
  HASH_FIND_INT(*hashmap, &key, item);
  return item;
}

/**
 * Deletes an item from the map based on key
 *
 * @param key an int corresponding to the player_id to delete from the hashmap
 * @param hashmap double pointer to the hashmap
 */
void delete(int key, HashItem **hashmap) {
  HashItem *item = find(key, hashmap);
  if (item) {
    HASH_DEL(*hashmap, item);
    free(item);
  }
}

/**
 * Deletes and frees the map
 *
 * @param hashmap double pointer to the hashmap
 */
void cleanup(HashItem **hashmap) {
  HashItem *current_item, *tmp;
  HASH_ITER(hh, *hashmap, current_item, tmp) {
    HASH_DEL(*hashmap, current_item);
    free(current_item);
  }
}
