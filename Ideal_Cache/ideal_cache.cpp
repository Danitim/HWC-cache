#include "ideal_cache.hpp"


int icache_hits(size_t cache_size, int buf_len, std::vector<int> requests) {
    std::unordered_set<int> cache;
    std::unordered_map<int, std::set<std::pair<int, int>>::iterator> iterators;
    std::set<std::pair<int, int>> next_appear;

    int hits = 0;

    for (int i=0; i < buf_len; ++i) {
        int cur = requests[i];

        if (cache.find(cur) != cache.end()) {
            hits++;
            next_appear.erase(iterators[cur]);

            int next = i + 1;
            while(next < buf_len && requests[next] != cur) next++;
            iterators[cur] = next_appear.insert({next, cur}).first;
            continue;
        }

        if (cache.size() < cache_size) {
            cache.insert(cur);

            int next = i + 1;
            while(next < buf_len && requests[next] != cur) next++;
            iterators[cur] = next_appear.insert({next, cur}).first;
            continue;
        }

        if(!next_appear.empty()) {
            int next = i + 1;
            while(next < buf_len && requests[next] != cur) next++;
            if (next == buf_len) continue;

            iterators[cur] = next_appear.insert({next, cur}).first;

            auto farthest = --next_appear.end();
            int page_to_remove = farthest->second;

            if (page_to_remove == cur) continue;

            cache.erase(page_to_remove);
            iterators.erase(page_to_remove);
            next_appear.erase(farthest);

            cache.insert(requests[i]);

            while(next < buf_len && requests[next] != cur) next++;
            iterators[cur] = next_appear.insert({next, cur}).first;
        }
    }

    return hits;
}