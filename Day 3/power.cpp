#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include "binary_DLL.hpp"
#include "part1.hpp"
#include "part2.hpp"

    // init static vars for double linked list class
unsigned binary_DLL::OGR_size {0}; 
unsigned binary_DLL::CO2SR_size {0}; 
binary_DLL* binary_DLL::OGR_previous_DLL {nullptr}; 
binary_DLL* binary_DLL::CO2SR_previous_DLL {nullptr}; 

int main()
{
    // data.txt contains 1000 rows of 12 digit binary values
    std::ifstream sfi;
    sfi.open("data.txt");
    std::vector<char*> vec_of_char(1000); // to hold 12 digit binary values
    constexpr std::int8_t char_arr_size {13};
    std::vector<int> gamma_vec (char_arr_size-1, -1), epsilon_vec (char_arr_size-1, -1); // -1 to catch errors 

    if (!!sfi)
    {
        // read file into vector of char arrays
        if (!readFileToVec(sfi, char_arr_size, &vec_of_char)) std::cout << "File read to vector failed... terminating program.\n";
        sfi.close(); // close stream post file read
        std::printf("Product of computed gamma and epsilon values: %.0f \n",
                        findFinalBinary(&vec_of_char, char_arr_size, gamma_vec, epsilon_vec));

         // create heads to list on stack so the entire lists can be accessed here and free'd has needed
        binary_DLL OGR_head {'O'};
        binary_DLL CO2SR_head {'C'};
         // return first idx as char character
        auto l_gamma_0th_idx = [&]()->const char
            {
                if (gamma_vec.at(0) == 1) return '1';
                else return '0';
            };

            // create both OXYGEN and CO2 double linked lists based on most common 0th idx value
        createBinaryDLL(&vec_of_char, l_gamma_0th_idx()); 

            // print all arrays [TEST]
        //printBinaryDLLArrays(&CO2SR_head, 'C');

         // free heap-allocated lists before list-heads are popped
        freeListHeap(&OGR_head);
        freeListHeap(&CO2SR_head); 
    }

    // free heap alloc
    for (auto& free_me : vec_of_char) delete [] free_me;
    return 0;
}