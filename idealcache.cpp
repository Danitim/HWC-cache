#include <iostream>
#include <cassert>
#include <algorithm>
#include <list>
#include <unordered_map>
#include <vector>

typedef unsigned int uint;

int main(int argc, char *argv[]) {

    uint hits = 0, buf_len;
    size_t cache_size;

    std::cin >> cache_size >> buf_len;
    assert(std::cin.good());

    std::vector<uint> requests(buf_len);
    for (int i = 0; i < buf_len; i++) {
        std::cin >> requests[i];
    }

    /*Returns unordered_map filled with iterators to the first appearances of requests vector,
    if the element does not have future appearances, iterator is equal to vector.end()*/
    std::unordered_map<int, std::vector<uint>::iterator> next_appearance;
    for (int i = buf_len; i >= 0; i--) 
        next_appearance[requests[i]] = std::find(requests.begin()+i, requests.end(), requests[i]);

    std::list<uint> cache;
    for (int i=0; i<buf_len; i++) {
        uint cur = requests[i];

        //If it is a hit, we count it and continue
        if (std::find(cache.begin(), cache.end(), cur) != cache.end()) { hits ++; continue; }

        //If the cache is not full, we add current element to the cache and continue
        if (cache.size() < cache_size) { cache.push_back(cur); continue; }

        //We must choose the element to delete
        uint max_dist = -1, value_to_delete;
        std::list<uint>::iterator it;
        for (it=cache.begin(); it!=cache.end(); it++) {
            std::vector<uint>::iterator next = next_appearance[*it];

            //If we find a value that won't occur again, we delete it.
            if (next == requests.end()) { value_to_delete = *it; break; }

            //Otherwise, we look for the element that occurs most recently.
            if ((next - requests.begin()) > max_dist) {
                max_dist = next - requests.begin();
                value_to_delete = *it;
            }
        }

        //Delete the unwanted element and add the desired one to the cache
        cache.remove(value_to_delete);
        cache.push_back(cur);
    }

    std::cout << "Total number of hits: " << hits << std::endl;
    return 0;
}