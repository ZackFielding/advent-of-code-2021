#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cmath>

bool readFileToVec(std::ifstream& sfi, const std::int8_t arr_size, std::vector<char*>* vec)
{
    for (auto iter {vec->begin()}; iter != vec->end(); ++iter)
    {
        *iter = new char[arr_size]; // alloc to heap
        (*iter)[arr_size-1] = '\n'; // last idx need to be null terminated for get() func & variants
            // read in 12 digit code - if stream fails - return false to calling func
        if (!(sfi.getline(*iter, arr_size))) return false; 
    }
    return true;
}

double toBinary(const std::vector<int>* vec)
{
    double result {0}; float exp {0}; // exp2 expects floating point - avoid uncessary conversions
    for (auto rev_iter {vec->crbegin()}; rev_iter != vec->crend(); ++rev_iter)
    {
        if (*rev_iter == 1) result += std::exp2(exp);  // if 1 -> 2^exp
        ++exp; // increment exp for next binary position
    }
    return result;
}

double findFinalBinary(std::vector<char*>* vec, const std::int8_t arr_size)
{
    // single-nested loop - outter iterates over std::vec and inner a c-style array of chars
    std::vector<unsigned> binary_one_counter ((arr_size-1),0);
    for (auto iter {vec->cbegin()}; iter != vec->cend(); ++iter)
    {
        for (std::int8_t inlp {0}; inlp < (arr_size-1); ++inlp) // carray = 12 chars + null (final letter char @ [11])
           if ((*iter)[inlp] == '1') ++binary_one_counter.at(inlp); 
    }

    // loop through binary counter vector and get gamma & epsilon binary (still in arrays)
    // most common bit = gamma -> least common -> epsilon
    std::vector<int> gamma_vec (arr_size-1, -1), epsilon_vec (arr_size-1, -1); // -1 to catch errors 
    for (std::int8_t idx {0}; idx < (arr_size-1); ++idx) // loop over binary counter
    {
        if (binary_one_counter.at(idx) > (vec->size())/2) // if 1 counter > half size of vector == most common
        {
           gamma_vec.at(idx) = 1; // gamma gets most common binary
           epsilon_vec.at(idx) = 0; // gamma gets least common binary
        }
        else // if there was more 0s than 1s, index the opposite
        {
            gamma_vec.at(idx) = 0;
            epsilon_vec.at(idx) = 1;
        }
    }
    
    return (toBinary(&gamma_vec) * toBinary(&epsilon_vec));
}

int main()
{
    // data.txt contains 1000 rows of 12 digit binary values
    std::ifstream sfi;
    sfi.open("data.txt");
    std::vector<char*> vec_of_char(1000); // to hold 12 digit binary values
    constexpr std::int8_t char_arr_size {13};

    if (!!sfi)
    {
        // read file into vector of char arrays
        if (!readFileToVec(sfi, char_arr_size, &vec_of_char)) std::cout << "File read to vector failed... terminating program.\n";
        sfi.close(); // close stream post file read
        std::printf("Product of computed gamma and epsilon values: %.0f", findFinalBinary(&vec_of_char, char_arr_size));
    }

    // free heap alloc
    for (auto& free_me : vec_of_char) delete [] free_me;
    return 0;
}