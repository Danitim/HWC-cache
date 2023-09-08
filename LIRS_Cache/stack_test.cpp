#include <iostream>
#include <fstream> 
#include "stack_implementation.hpp"


int main()
{

    int a;
    std::ifstream test;
    test.open("stack_test.txt");
    test >> a;

    if (a == 0)
    {
        return 0;
    }
    struct block* page = (block*)calloc(a ,sizeof(block));


    for (int i = 0; i < a; i++)
    {
        test >> page[i].number >> page[i].HIR >> page[i].cache_residency >> page[i].stack_residency;
    }
    struct stack stack_test;
    stack_create(&stack_test, 2);
    for (int i = 0; i<a; i++)
    {
        stack_push(&stack_test, page+i);
    }

    stack_print((struct stack*)(&stack_test));

    struct block* block1;
   /* printf("test 1\n");
    block1 = stack_pop(&stack_test);
    block1 = stack_pop(&stack_test);

    for (int i = 0; i < a; i++)
    {
        fscanf(test, "%d%d%d%d", &(page[i].number), &(page[i].HIR),
                                 &(page[i].cache_residency), &(page[i].stack_residency));
    }
    for (int i = 0; i<a; i++)
    {
        stack_push(&stack_test, page+i);
    }


    printf("test 2\n");
    stack_pruning(&stack_test);
    stack_print(&stack_test);

    stack_print(&stack_test);
    stack_delete(&stack_test);
    stack_create(&stack_test, 2);   */
    std::cout << "test 3" << std::endl;

    for (int k = 0; k < 6; k++)
    {
        stack_pruning(&stack_test);
        block1 = stack_pop(&stack_test);
        for (int i = 0; i < a; i++)
        {
            test >> page[i].number >> page[i].HIR >> page[i].cache_residency >> page[i].stack_residency;
        }

        for (int i = 0; i<a; i++)
        {
            stack_push(&stack_test, page+i);
        }
        stack_print((struct stack*)(&stack_test));
    }
    test.close();
    return 0;
}



