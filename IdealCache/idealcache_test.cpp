#include <iostream>
#include <fstream>

#include "idealcache.hpp"

int main(int argc, char *argv[]) {

    uint hits = 0, buf_len, answer, counter = 0;
    size_t cache_size;
    std::ifstream infile;
    infile.open("test_data.txt");

    while (!infile.eof()) {
        ++counter;
        infile >> cache_size >> buf_len;
        std::vector<uint> requests(buf_len);
         for (int i = 0; i < buf_len; i++)
            infile >> requests[i];
        infile >> answer;

        hits = icache_hits(cache_size, buf_len, requests);

        std::cout << "Test number #" << counter <<
            (hits == answer ? " passed" : " failed") << std::endl;
    }

    return 0;
}