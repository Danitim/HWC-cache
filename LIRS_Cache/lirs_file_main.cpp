#include <fstream>
#include <iostream>
#include "lirs_file_read.hpp"

int main() {
    std::ifstream test;
    test.open("lirs_test.txt");
    std::cout << "Cache hits amount: " << lirs_file_read(test) << std::endl;
    return 0;
}