#include <iostream>
#include <cassert>

#include "lirs_algorythm.hpp"

int main() {
    int hits = 0, buf_len;
    size_t buf_size;

    std::cin >> buf_size >> buf_len;
    assert(std::cin.good());
    
    for (int i=0; i<buf_len; i++) {
        int page;
        std::cin >> page;
        assert(std::cin.good());

        int hit_or_miss = algorythm_step(page);
        if ((hit_or_miss = 0) || (hit_or_miss = 1))
            hits += hit_or_miss;
        else {
            std::cout << "Something weird happened during algorythm step" << std::endl;
            std::abort();
        }
    }

    std::cout << "Total number of hits: " << hits << std::endl;
    return 0;
}