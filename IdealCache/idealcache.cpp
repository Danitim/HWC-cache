#include "idealcache.hpp"

int icache_hits(size_t cache_size, int buf_len, std::vector<int> requests) {
    int hits = 0;

    /*Create unordered_map filled with iterators to the first appearances of requests vector,
    if the element does not have future appearances, iterator is equal to vector.end()*/
    std::unordered_map<int, std::vector<int>::iterator> next_appearance;
    for (int i = buf_len-1; i >= 0; i--) {
        next_appearance[requests[i]] = std::find(requests.begin()+i+1, requests.end(), requests[i]);
    }

    std::list<int> cache;
    for (int i=0; i<buf_len; i++) {
        int cur = requests[i];

        next_appearance[cur] = std::find(requests.begin()+i+1, requests.end(), cur);

        //If it is a hit, we count it and continue
        if (std::find(cache.begin(), cache.end(), cur) != cache.end()) { hits ++; continue; }

        //If the cache is not full, we add current element to the cache and continue
        if (cache.size() < cache_size) { cache.push_back(cur); continue; }

        //We must choose the element to delete
        int max_dist = 0;
        int value_to_delete = -1;
        std::list<int>::iterator it;
        for (it=cache.begin(); it!=cache.end(); ++it) {
            std::vector<int>::iterator next = next_appearance[*it];

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

    return hits;
}