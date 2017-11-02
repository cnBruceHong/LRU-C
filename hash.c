//
// Created by 洪旭 on 2017/11/2.
//

#include "hash.h"
#include <stdio.h>

int hashKey(LRUCacheS *cache, char key) {
    unsigned capacity = (unsigned) cache->cacheCapacity;
    return key & (capacity);
}

cacheEntryS *getValueFromHashMap(LRUCacheS *cache, int key) {
    cacheEntryS *entry = cache->hashMap[hashKey(cache, key)];

    // 如果Hash冲突，这里会退化成链表
    while (entry) {
        if (entry->key == key) {
            break;
        }
        entry = entry->hashListNext;
    }

    return entry;
}

void insertEntryToHashMap(LRUCacheS *cache, cacheEntryS *entry) {
    cacheEntryS *n = cache->hashMap[hashKey(cache, entry->key)];

    if (n != NULL) {
        entry->hashListNext = n;
        n->hashListPrev = entry;
    }

    cache->hashMap[hashKey(cache, entry->key)] = entry;
}

void removeEntryFromHashMap(LRUCacheS *cache, cacheEntryS *entry) {
    if (NULL == entry || NULL == cache || NULL == cache->hashMap) return;
    cacheEntryS *n = cache->hashMap[hashKey(cache, entry->key)];

    while (n) {
        if (n->key == entry->key) {
            if (n->hashListPrev) {
                n->hashListPrev->hashListNext = n->hashListNext;
            } else {
                cache->hashMap[hashKey(cache, entry->key)] = n->hashListNext;
            }

            if (n->hashListNext) {
                n->hashListNext->hashListPrev = n->hashListPrev;
            }
        };
        n = n->hashListNext;
    }
}
