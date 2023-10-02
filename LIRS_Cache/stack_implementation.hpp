#ifndef STACK_IMPLEMENTATION_HPP
#define STACK_IMPLEMENTATION_HPP

#include <list>

struct block
{
    int number;                            //page number without hash-function used
    int HIR;                               //LIR/HIR block status flag, 0 - LIR, 1 - HIR
    int cache_residency;                   //cache residency flag, 0 - non-resident block, 1 - resident block
    int stack_residency;                   //stack_residency
};

// Implementation of the functions working with stack

class Stack {
private:
    std::list<struct block*> stack_list;

public:
    Stack() = default;

    void stack_push(struct block* x);     //push a new block into the stack
    struct block* stack_pop();       //pop the top element from the stack
    struct block* stack_get_top();       // returns the top element of the stack
    struct block* stack_get_bottom();
    void stack_pruning ();           // removes the HIR blocks in the bottom of the stack until an LIR block sits in the stack bottom
};

#endif /*STACK_IMPLEMENTATION_HPP*/
