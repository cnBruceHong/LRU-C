//
// Created by 洪旭 on 2017/11/2.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lru.h"
#include "entry.h"
#include "hash.h"


cacheEntryS *newCacheEntry(char key, char data) {
    cacheEntryS *entry = (cacheEntryS *) malloc(sizeof(cacheEntryS));

    if (NULL == entry) {
        HANDLE_ERROR("申请内存失败\n");
    }

    memset(entry, 0, sizeof(*entry));
    entry->key = key;
    entry->data = data;

    return entry;
}

void freeCacheEntry(cacheEntryS *entry) {
    if (NULL != entry) {
        free(entry);
    }
}

// 创建LRU接口
bool LRUCacheCreate(unsigned capacity, void **lruCache) {
    LRUCacheS *cache = malloc(sizeof(LRUCacheS));

    if (NULL == cache) {
        HANDLE_ERROR("申请内存失败\n");
    }

    memset(cache, 0, sizeof(*cache));
    cache->cacheCapacity = capacity;
    cache->lruListHead = NULL;
    cache->lruListTail = NULL;
    cache->cacheCapacity = capacity;
    cache->hashMap = (cacheEntryS **) calloc(capacity, sizeof(cacheEntryS));

    if (NULL == cache->hashMap) {
        HANDLE_ERROR("申请内存失败\n");
    }

    memset(cache->hashMap, 0, sizeof(cache->hashMap) * capacity);
    *lruCache = cache;

    return TRUE;
}

// 销毁LRU接口
bool LRUCacheDestroy(void *lruCache) {
    LRUCacheS *cache = (LRUCacheS *) lruCache;
    if (NULL == cache) {
        return TRUE;
    }
    free(cache->hashMap);
    // TODO: free the link list
    free(cache);
    return TRUE;
}

// 添加缓存
bool LRUCacheSet(void *lruCache, char key, char data) {
    LRUCacheS *cache = (LRUCacheS *) lruCache;
    /*从哈希表查找数据是否已经在缓存中*/
    cacheEntryS *entry = getValueFromHashMap(cache, key);

    if (entry != NULL) {
        /*数据已经在缓存中,更新数据，将该数据项更新至链表表头*/
        entry->data = data;
        updateLRUList(cache, entry);
    } else {
        /*数据没在缓存中,新建缓存单元*/
        entry = newCacheEntry(key, data);

        /*将新建缓存单元插入链表表头*/
        cacheEntryS *removedEntry = insertToListHead(cache, entry);
        if (NULL != removedEntry) {
            /*新建缓存单元过程中，发生缓存满了的情况，需要淘汰最久没有被访问到的缓存数据单元*/
            removeEntryFromHashMap(cache, removedEntry);
            freeCacheEntry(removedEntry);
        }
        /*将新建缓存单元插入哈希表*/
        insertEntryToHashMap(cache, entry);
    }

    return TRUE;
}

// 获取缓存

char LRUCacheGet(void *lruCache, char key) {
    LRUCacheS *cache = (LRUCacheS *) lruCache;
    /*从哈希表查找数据是否已经在缓存中*/
    cacheEntryS *entry = getValueFromHashMap(cache, key);
    if (NULL != entry) {
        /*缓存中存在该数据，更新至链表表头*/
        updateLRUList(cache, entry);
        /*返回数据*/
        return entry->data;
    } else {
        /*缓存中不存在相关数据*/
        return '\0';
    }
}

// 输出调试
void LRUCachePrint(void *lruCache) {
    LRUCacheS *cache = (LRUCacheS *) lruCache;
    if (NULL == cache || 0 == cache->lruListSize) return;
    fprintf(stdout, "\n>>>>>>>>>>\n");
    fprintf(stdout, "cache  (key  data):\n");
    cacheEntryS *entry = cache->lruListHead;
    while (entry) {
        fprintf(stdout, "(%c, %c) ", entry->key, entry->data);
        entry = entry->lruListNext;
    }
    fprintf(stdout, "\n<<<<<<<<<<\n\n");
}