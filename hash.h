//
// Created by 洪旭 on 2017/11/2.
//

#ifndef ALGORITHM_HASH_H
#define ALGORITHM_HASH_H

#include "entry.h"

int hashKey(LRUCacheS *cache, char key);

cacheEntryS *getValueFromHashMap(LRUCacheS *cache, int key);

void insertEntryToHashMap(LRUCacheS *cache, cacheEntryS *entry);

void removeEntryFromHashMap(LRUCacheS *cache, cacheEntryS *entry);

#endif //ALGORITHM_HASH_H
