#include "lru.h"
#include "entry.h"
#include <stdio.h>
#include <stdlib.h>

/*测试用例1*/
void testcase1(void) {
    fprintf(stdout, "=========================\n");
    fprintf(stdout, "In testcase1....\n");
    fprintf(stdout, "=========================\n");
    LRUCacheS *lruCache = NULL;
    LRUCacheCreate(5, &lruCache);
    /*ABC!*/
    LRUCACHE_PUTDATA(lruCache, 'A');
//    LRUCACHE_GETDATA(lruCache, 'A');
    LRUCACHE_PUTDATA(lruCache, 'B');
//    LRUCACHE_GETDATA(lruCache, 'B');
    LRUCACHE_PUTDATA(lruCache, 'C');
    LRUCACHE_PUTDATA(lruCache, 'A');
//    LRUCACHE_GETDATA(lruCache, 'C');
//    LRUCachePrint(lruCache);/*CBA*/

    /*DEAF!*/
    LRUCACHE_PUTDATA(lruCache, 'D');
//    LRUCACHE_GETDATA(lruCache, 'D');
    LRUCACHE_PUTDATA(lruCache, 'E');
//    LRUCACHE_GETDATA(lruCache, 'E');
    LRUCACHE_PUTDATA(lruCache, 'A');
//    LRUCACHE_GETDATA(lruCache, 'A');
    LRUCACHE_PUTDATA(lruCache, 'F');
//    LRUCACHE_GETDATA(lruCache, 'F');
    LRUCachePrint(lruCache); /*FAEDC*/
//
//    /*B!*/
    LRUCACHE_PUTDATA(lruCache, 'F');
//    LRUCACHE_GETDATA(lruCache, 'F');
//    LRUCachePrint(lruCache); /*BFAED*/

    if (TRUE != LRUCacheDestroy(lruCache))
        HANDLE_ERROR("释放内存失败");
    fprintf(stdout, "finished\n");
    fprintf(stdout, "=========================\n\n");
}

int main() {
    testcase1();
    return 0;
}