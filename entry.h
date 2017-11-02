//
// Created by 洪旭 on 2017/11/2.
//

#ifndef ALGORITHM_ENTRY_H
#define ALGORITHM_ENTRY_H

typedef struct cacheEntryS cacheEntryS;
typedef struct LRUCacheS LRUCacheS;

struct LRUCacheS {
    int cacheCapacity;
    cacheEntryS **hashMap;
    cacheEntryS *lruListHead;
    cacheEntryS *lruListTail;
    unsigned lruListSize;
};

struct cacheEntryS {
    char key;
    char data;
    cacheEntryS *hashListPrev;
    cacheEntryS *hashListNext;
    cacheEntryS *lruListPrev;
    cacheEntryS *lruListNext;
};

void removeFromList(LRUCacheS *cache, cacheEntryS *entry);

cacheEntryS *insertToListHead(LRUCacheS *cache, cacheEntryS *entry);

void freeList(LRUCacheS *cache);

void updateLRUList(LRUCacheS *cache, cacheEntryS *entry);

#endif //ALGORITHM_ENTRY_H
