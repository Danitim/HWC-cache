#include "ideal_cache.hpp"


// Record the next page access time if it is requested in the future
static void next_appearance(int index, int request, 
                             const std::vector<int> &requests, 
                             std::unordered_map<int, std::set<std::pair<int, int>>::iterator> &iterators, 
                             std::set<std::pair<int, int>> &next_appear);

int icache_hits(size_t cache_size, int buf_len, std::vector<int> requests) {
    int hits = 0;

    // A set for quickly determining whether a page is in the cache.
    std::unordered_set<int> cache; 
    // A dictionary to store iterators to 'next_appear' elements for each page.
    std::unordered_map<int, std::set<std::pair<int, int>>::iterator> iterators;
    // A set to store the next access time for each page. It is automatically sorted by access time.
    std::set<std::pair<int, int>> next_appear; 
    
    for(int i = 0; i < buf_len; i++) {
        // If the page is already in cache.
        if(cache.find(requests[i]) != cache.end()) {
            hits++;
            next_appear.erase(iterators[requests[i]]);
            next_appearance(i, requests[i], requests, iterators, next_appear);
        } else {
            // If there is space in the cache, add the page.
            if(cache.size() < cache_size) {
                cache.insert(requests[i]);
                next_appearance(i, requests[i], requests, iterators, next_appear);
            } else {
                // If the cache is full, find the page with the furthest next appearance and delete it.
                auto farthest = next_appear.rbegin();
                cache.erase(farthest->second);
                iterators.erase(farthest->second);
                next_appear.erase(std::next(farthest).base());
                cache.insert(requests[i]);
                next_appearance(i, requests[i], requests, iterators, next_appear);
            }
        }
    }
    return hits;
}

static void next_appearance(int index, int request, 
                             const std::vector<int> &requests, 
                             std::unordered_map<int, std::set<std::pair<int, int>>::iterator> &iterators, 
                             std::set<std::pair<int, int>> &next_access) {
    int next = index + 1;
    while(next < requests.size() && requests[next] != request) next++;
    
    if (next != requests.size()) {
        iterators[request] = next_access.insert({next, request}).first;
    }
}