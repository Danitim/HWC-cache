#pragma once

#include <algorithm>
#include <vector>
#include <list>
#include <unordered_map>

int icache_hits(size_t cache_size, int buf_len, std::vector<int> requests);