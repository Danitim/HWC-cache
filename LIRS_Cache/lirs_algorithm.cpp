#include <iostream>
#include <unordered_map>
#include <list>
#include <stdlib.h>
#include "lirs_algorithm.hpp"

std::unordered_map<int, struct block*> hash_table;
std::list<struct block*> list_Q;

struct block *hash_get_block(int number) {
    if (hash_table.count(number) == 0)
    {
        hash_table[number] = (struct block *)calloc(1, sizeof(struct block));
        hash_table[number]->HIR = 1;
        hash_table[number]->cache_residency = 0;
        hash_table[number]->stack_residency = 0;
        hash_table[number]->number = number;
    }
    return hash_table[number];
}

void HIR_resident_access(struct block *accessed_block, Stack &S) {
    S.stack_push(accessed_block);
    if (accessed_block->stack_residency > 1)
    {
        struct block *block_buffer;
        accessed_block->HIR = 0;
        list_Q.remove(accessed_block);
        block_buffer = S.stack_get_bottom();
        list_Q.push_back(block_buffer);
        block_buffer->cache_residency = 1;
        block_buffer->HIR = 1;
        S.stack_pruning();
    }
    else
    {
        list_Q.push_back(accessed_block);
        list_Q.front()->cache_residency = 0;
        list_Q.pop_front();
    }
}

void HIR_non_resident_access(struct block *accessed_block, Stack &S) {
    list_Q.front()->cache_residency = 0;
    list_Q.remove(list_Q.front());
    list_Q.push_front(accessed_block);
    accessed_block->cache_residency = 1;
    S.stack_push(accessed_block);

    if (accessed_block->stack_residency > 1)
    {
        accessed_block->HIR = 0;
        list_Q.push_back(S.stack_get_bottom());
        S.stack_get_bottom()->HIR = 1;
        list_Q.pop_front();
        S.stack_pruning();
    }
    else
    {
        list_Q.push_back(accessed_block);
        list_Q.front()->cache_residency = 0;
        list_Q.pop_front();
        accessed_block->cache_residency = 1;
    }
}

void LIR_access(struct block *accessed_block, Stack &S) {
    S.stack_push(accessed_block);
    if (S.stack_get_bottom()->HIR == 0)
        S.stack_pruning();    
    }

