#include <iostream>
#include <unordered_map>
#include <list>
#include "lirs_algorithm.hpp"

extern std::unordered_map<int, struct block*> hash_table;
extern std::list<struct block*> list_Q;
extern struct stack S;

int main()
{
    long long cache_size = 0, HIR_section_size = 0, page_number = 0, cache_hit = 0, page_amount = 0;
    struct block *accessed_block;
    struct block *first_pseudo_block = (struct block *)calloc(1, sizeof(struct block));

//    std::cout << "Print cache size: ";
    std::cin >> cache_size;
    if (cache_size < 0) {
        std::cout << "Can't be negative number " << std::endl;
        return 0;
    }
    HIR_section_size = cache_size/100;
    if (HIR_section_size == 0)
        HIR_section_size = 1;

//    std::cout << "Print amount of pages: ";
    std::cin >> page_amount;
    if (page_amount < 0) {
        std::cout << "Can't be negative number " << std::endl;
        return 0;
    }

    stack_create(&S, page_amount*2);                                               //creation of stack

    for (int j = 0; j < cache_size - HIR_section_size; j++)                       //filling cache with LIR blocks
    {
        std::cin >> page_number;
        if (hash_table[page_number] != 0) {
            cache_hit++;
            j--;
        }
        else
            hash_table[page_number] = (struct block *)calloc(1, sizeof(struct block));
        stack_push(&S, hash_table[page_number]);

        hash_table[page_number]->HIR = 0;
        hash_table[page_number]->cache_residency = 1;
    }

    first_pseudo_block->number = (-1)*HIR_section_size;                           //creating pseudo-empty list
    list_Q.push_front(first_pseudo_block);

    for (int i = 1; i < HIR_section_size; i++)
    {
        struct block *pseudo_block = (struct block*)calloc(1, sizeof(struct block));
        pseudo_block->number = (-1)*i;
        list_Q.push_front(pseudo_block);
    }

    for (int i = cache_size-HIR_section_size; i < page_amount; i++) {             //main cycle
        std::cin >> page_number;
        accessed_block = hash_get_block(page_number);
        if ((accessed_block->HIR == 1) && (accessed_block->cache_residency == 1)) {
            cache_hit++;
            HIR_resident_access(accessed_block);
        } else if ((accessed_block->HIR == 1)
                   && (accessed_block->cache_residency == 0)) {
            HIR_non_resident_access(accessed_block);
        } else if ((accessed_block->HIR) == 0) {
            cache_hit++;
            LIR_access(accessed_block);
        }
    }
    std::cout /*<< "Cache hits amount: "*/ << cache_hit << std::endl;
    return 0;
}