#include <iostream>
#include <fstream>
#include <ctime>
#include "LIRS_Cache/lirs_file_read.hpp"
#include "LIRS_Cache/lirs_algorithm.hpp"
#include "LIRS_Cache/stack_implementation.hpp"
#include "Ideal_Cache/ideal_cache.hpp"

int main() { 
    int cache_hit = 0;
    int lirs_start_time = 0, lirs_end_time = 0, ideal_start_time = 0, ideal_end_time = 0;
    std::ifstream test1;
    test1.open("comparator_test.txt");

    lirs_start_time = clock();
    cache_hit = lirs_file_read(test1);
    lirs_end_time = clock();
    std::cout << "LIRS amount of cache hits: " << cache_hit << std::endl << "LIRS execution time: " << lirs_end_time - lirs_start_time << " millisec" << std::endl;

    test1.close();
    std::ifstream test2;
    test2.open("comparator_test.txt");
    
    ideal_start_time = clock();
    int cache_size = 0, pages_amount = 0;
    test2 >> cache_size >> pages_amount;
    std::vector<int> pages(pages_amount);
    for (int i = 0; i < pages_amount; i++) 
        test2 >> pages[i];
    cache_hit = icache_hits(cache_size, pages_amount, pages);
    ideal_end_time = clock();
    std::cout << "Ideal amount of cache hits: " << cache_hit << std::endl << "Ideal execution time: " << ideal_end_time - ideal_start_time << " millisec" << std::endl;

    test2.close();
    return 0;
}