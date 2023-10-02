#include <iostream>
#include <list>
#include "stack_implementation.hpp"

void Stack::stack_push(struct block *accessed_block) {
    stack_list.push_front(accessed_block);
    accessed_block->stack_residency++;
}

struct block* Stack::stack_pop() {
    struct block *accessed_block = stack_list.front();
    accessed_block->stack_residency--;
    stack_list.pop_front();
    return accessed_block;
}

struct block* Stack::stack_get_top() {
    return stack_list.front();
}

struct block* Stack::stack_get_bottom() {
    return stack_list.back();
}

void Stack::stack_pruning() {
    while(stack_list.back()->HIR == 1) {
        stack_list.back()->stack_residency--;
        stack_list.pop_back();
    }
}