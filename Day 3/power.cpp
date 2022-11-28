#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cmath>
#include <string>
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
        auto l_return_int_as_char = [](const std::vector<int>& vec_of_carray, const int idx)->const char
            { return (vec_of_carray.at(idx) == 1) ? '1' : '0'; };

            // create both OXYGEN and CO2 double linked lists based on most common 0th idx value
        createBinaryDLL(&vec_of_char, l_return_int_as_char(gamma_vec, 0)); 

        int O2_idx {1};
        while (OGR_head.OGR_size > 1) // while within char array range && >1 item is left in list
        {
            traverseRemove("Oxygen", OGR_head, O2_idx, l_return_int_as_char(gamma_vec, O2_idx));
            ++O2_idx;
        }
        
        int CO2_idx {1};
        while (CO2SR_head.CO2SR_size > 1)
        {
            traverseRemove("CO2", CO2SR_head, CO2_idx, l_return_int_as_char(epsilon_vec, CO2_idx));
            ++CO2_idx;
        }
        
        printBinaryDLLArrays(&CO2SR_head, 'C');

        // free heap-allocated lists before list-heads are popped ... ensure there are nodes left to be freed
        if (OGR_head.OGR_size > 0) freeListHeap(&OGR_head);
        if (CO2SR_head.CO2SR_size > 0) freeListHeap(&CO2SR_head); 
    }

    // free heap alloc
    for (auto& free_me : vec_of_char) delete [] free_me;
    return 0;
}