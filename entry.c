//
// Created by 洪旭 on 2017/11/2.
//

#include "entry.h"
#include <stdio.h>

void removeFromList(LRUCacheS *cache, cacheEntryS *entry) {
    if (cache->lruListSize <= 0) {
        return;
    }

    if (entry == cache->lruListHead && entry == cache->lruListTail) {
        cache->lruListHead = cache->lruListTail = NULL;
    } else if (entry == cache->lruListHead) {
        cache->lruListHead = entry->lruListNext;
        entry->lruListNext->lruListPrev = NULL;
    } else if (entry == cache->lruListTail) {
        cache->lruListTail = entry->lruListPrev;
        entry->lruListPrev->lruListNext = NULL;
    } else {
        entry->lruListPrev->lruListNext = entry->lruListNext;
        entry->lruListNext->lruListPrev = entry->lruListPrev;
    }
    cache->lruListSize--;
}

cacheEntryS *insertToListHead(LRUCacheS *cache, cacheEntryS *entry) {
    cacheEntryS *removedEntry = NULL;

    if (++cache->lruListSize > cache->cacheCapacity) {
        /* 缓存满了，LRU置换 */
        removedEntry = cache->lruListTail;
        removeFromList(cache, removedEntry);
    }

    if (cache->lruListHead == NULL && cache->lruListTail == NULL) {
        cache->lruListHead = cache->lruListTail = entry;
    } else {
        entry->lruListNext = cache->lruListHead;
        entry->lruListPrev = NULL;
        cache->lruListHead->lruListPrev = entry;
        cache->lruListHead = entry;
    }

    return removedEntry;
}

void freeList(LRUCacheS *cache) {
    if (0 != cache->lruListSize) {
        cacheEntryS *entry = cache->lruListHead;
        while (NULL != entry) {
            cacheEntryS *next = entry->lruListNext;
            free(entry);
            entry = next;
        }
        cache->lruListSize = 0;
    }
}

void updateLRUList(LRUCacheS *cache, cacheEntryS *entry) {
    removeFromList(cache, entry);
    insertToListHead(cache, entry);
}
