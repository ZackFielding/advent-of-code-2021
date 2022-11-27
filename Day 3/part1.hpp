#ifndef PART1_HPP
#define PART1_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdio>
#include <cmath>

bool readFileToVec(std::ifstream&, const std::int8_t, std::vector<char*>*);
double toBinary(const std::vector<int>*);
double findFinalBinary(std::vector<char*>*, const std::int8_t, std::vector<int>&, std::vector<int>&);

#endif