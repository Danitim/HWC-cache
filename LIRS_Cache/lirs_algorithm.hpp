#ifndef LIRS_ALGORITHM_HPP
#define LIRS_ALGORITHM_HPP
#include "stack_implementation.hpp"

struct block *hash_get_block(int number);
void HIR_resident_access(struct block *accessed_block, Stack &S);
void HIR_non_resident_access(struct block *accessed_block, Stack &S);
void LIR_access(struct block *accessed_block, Stack &S);

#endif /*LIRS_ALGORITHM_HPP*/