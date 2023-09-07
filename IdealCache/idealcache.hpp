#pragma once

#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>

typedef unsigned int uint;

unsigned int icache_hits(size_t cache_size, uint buf_len, std::vector<uint> requests);