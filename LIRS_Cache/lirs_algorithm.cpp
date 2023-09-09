#include <iostream>
#include <unordered_map>
#include <list>
#include "lirs_algorithm.hpp"

std::unordered_map<int, struct block*> hash_table;
std::list<struct block*> list_Q;
struct stack S;

struct block *hash_get_block(int number) {
    if (hash_table[number] == 0)
    {
        hash_table[number] = (struct block *)calloc(1, sizeof(struct block));
        hash_table[number]->HIR = 1;
        hash_table[number]->cache_residency = 0;
        hash_table[number]->stack_residency = 0;
        hash_table[number]->number = number;
    }
    return hash_table[number];
}

void HIR_resident_access(struct block *accessed_block) {
    stack_push(&S, accessed_block);
    if (accessed_block->stack_residency > 1)
    {
        accessed_block->HIR = 0;
        list_Q.remove(accessed_block);
        list_Q.push_back(S.data[S.bottom_number]);
        S.data[S.bottom_number]->cache_residency = 1;
        S.data[S.bottom_number]->HIR = 1;
        stack_pruning(&S);
    }
    else
    {
        list_Q.remove(accessed_block);
        list_Q.push_back(S.data[S.bottom_number + 1]);
    }
}

void HIR_non_resident_access(struct block *accessed_block) {
    list_Q.front()->cache_residency = 0;
    list_Q.front() = accessed_block;
    accessed_block->cache_residency = 1;
    stack_push(&S, accessed_block);

    if (accessed_block->stack_residency > 1)
    {
        accessed_block->HIR = 0;
        list_Q.push_back(S.data[S.bottom_number]);
        list_Q.front()->cache_residency = 0;
        list_Q.pop_front();
        
        S.data[S.bottom_number]->cache_residency = 1;
        stack_pruning(&S);
    }
    else
    {
        list_Q.push_back(accessed_block);
        list_Q.front()->cache_residency = 0;
        list_Q.pop_front();
        accessed_block->cache_residency = 1;
        stack_pruning(&S);
    }
}

void LIR_access(struct block *accessed_block) {
    stack_push(&S, accessed_block);
    if (S.data[S.bottom_number + 1]->HIR == 0)
        stack_pruning(&S);    
}

