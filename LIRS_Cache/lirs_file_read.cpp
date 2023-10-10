#include <iostream>
#include <list>
#include <unordered_map>
#include <cstdlib>
#include "lirs_algorithm.hpp"
#include "stack_implementation.hpp"
#include "lirs_file_read.hpp"

extern std::unordered_map<int, struct block*> hash_table;
extern std::list<struct block*> list_Q;

int lirs_file_read(std::ifstream &file) {
    long long cache_size = 0, HIR_section_size = 0, page_number = 0, cache_hit = 0, page_amount = 0;
    struct block *accessed_block;
    struct block *first_pseudo_block = (struct block *)calloc(1, sizeof(struct block));
    Stack S;                                               //creation of stack

//    std::cout << "Print cache size: ";
    file >> cache_size;
    if (cache_size <= 0) {
        std::cout << "Can't be negative number " << std::endl;
        return 0;
    }
    HIR_section_size = cache_size/100;
    if (HIR_section_size == 0)
        HIR_section_size = 1;

//    std::cout << "Print amount of pages: ";
    file >> page_amount;
    if (page_amount <= 0) {
        std::cout << "Must be a positive number." << std::endl;
        return 0;
    }

//    std::cout << "Cache: " << cache_size << "; HIR section: " << HIR_section_size << std::endl;
    for (int j = 0; j < cache_size - HIR_section_size; j++)                       //filling cache with LIR blocks
    {
        file >> page_number;
        if (std::cin.good() == 0)
            break;

        if (hash_table.count(page_number) == 1) {
            cache_hit++;
            j--;
            cache_size++;
        }
        else
            hash_table[page_number] = (struct block *)calloc(1, sizeof(struct block));

        hash_table[page_number]->number = page_number;
        hash_table[page_number]->HIR = 0;
        hash_table[page_number]->stack_residency = 0;
        hash_table[page_number]->cache_residency = 1;
        S.stack_push(hash_table[page_number]);

//        std::cout << hash_table[page_number]->number << " " << j << std::endl;
//    std::cout << "Number: " << page_number << "; j: " << cache_hit << std::endl;
    }

    first_pseudo_block->number = (-1)*HIR_section_size;                           //creating pseudo-empty list
    list_Q.push_front(first_pseudo_block);

    for (int i = 1; i < HIR_section_size; i++)
    {
        struct block *pseudo_block = (struct block*)calloc(1, sizeof(struct block));
        pseudo_block->number = (-1)*i;
        list_Q.push_front(pseudo_block);
    }

    for (int i = cache_size; i < page_amount + 1; i++) {             //main cycle
        file >> page_number;
        accessed_block = hash_get_block(page_number);
        if ((accessed_block->HIR == 1) && (accessed_block->cache_residency == 1)) {
            cache_hit++;
            HIR_resident_access(accessed_block, S);
        } else if ((accessed_block->HIR == 1)
                   && (accessed_block->cache_residency == 0)) {
            HIR_non_resident_access(accessed_block, S);
        } else if ((accessed_block->HIR) == 0) {
            cache_hit++;
            LIR_access(accessed_block, S);
        }
//        std::cout << "Number: " << page_number << "; Hits: " << cache_hit << std::endl;
    }    
    return cache_hit;
}