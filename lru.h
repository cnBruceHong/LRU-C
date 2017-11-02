//
// Created by 洪旭 on 2017/11/2.
//

#ifndef ALGORITHM_LRU_H
#define ALGORITHM_LRU_H

typedef int bool;
#define TRUE 1
#define FALSE 0
typedef char *string;

#ifndef HANDLE_ERROR
#define HANDLE_ERROR(msg) \
    do {fprintf(stderr, msg);exit(-1);} while (0)
#endif

#define LRUCACHE_PUTDATA(cache, data) \
    do {\
        if (TRUE != LRUCacheSet(cache, data, data)) \
            fprintf(stderr, "put (%c, %c) to cache fail.\n", data, data);\
        else \
            fprintf(stdout, "put (%c,%c) to cache success.\n", data, data); \
    } while (0)

#define LRUCACHE_GETDATA(cache, key) \
    do {\
        char data = LRUCacheGet(cache, key);\
        if ('\0' == data) \
            fprintf(stderr, "get data (Key:%c) from cache fail.\n", key);\
        else if (key == data) \
            fprintf(stdout, "got (%c,%c) from cache\n", key, data);\
    } while (0)

// 创建LRU接口
bool LRUCacheCreate(unsigned capacity, void **lruCache);

// 销毁LRU接口
bool LRUCacheDestroy(void *lruCache);

// 添加缓存
bool LRUCacheSet(void *lruCache, char key, char data);

// 获取缓存
char LRUCacheGet(void *lruCache, char key);

// 输出调试
void LRUCachePrint(void *lruCache);

#endif //ALGORITHM_LRU_H