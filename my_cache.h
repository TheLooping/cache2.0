#include <stdio.h>
#include "memory_pool.h"
#include "forward.h"
#include "cache_strategy.h"
#ifndef _CACHE_H_
#define _CACHE_H_

#define REQUEST_SIZE 0 * GB + 0 * MB + 1 * KB + 0 * 1

void cache_module(memory_pool_t *mp, char *payload_start, uint32_t len);
// 缓存模块

#endif