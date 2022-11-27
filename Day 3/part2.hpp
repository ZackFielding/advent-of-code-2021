#ifndef PART2_HPP
#define PART2_HPP

#include <iostream>
#include <vector>
#include "binary_DLL.hpp"

void createBinaryDLL(std::vector<char*>*, const char);
void freeListHeap(binary_DLL*);
void printBinaryDLLArrays(binary_DLL*, const char);

#endif