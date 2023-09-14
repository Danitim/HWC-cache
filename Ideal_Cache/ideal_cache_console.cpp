#include <iostream>

#include "ideal_cache.hpp"

int main(int argc, char *argv[]) {

    int hits = 0, buf_len;
    size_t cache_size;

    std::cin >> cache_size >> buf_len;
    std::vector<int> requests(buf_len);
    for (int i = 0; i < buf_len; i++)
        std::cin >> requests[i];

    hits = icache_hits(cache_size, buf_len, requests);

    std::cout /*<< "Total number of hits: " */<< hits << std::endl;
    return 0;
}