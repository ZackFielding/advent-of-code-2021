#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cmath>

class binary_DLL // double linked list
{
    static unsigned OGR_size; // tracks list size
    static unsigned CO2SR_size; // tracks list size
    static binary_DLL* OGR_previous_DLL; // caches previous binary obj for next obj to be created
    static binary_DLL* CO2SR_previous_DLL;

public:
    char* carray_ptr;
    binary_DLL* next;
    binary_DLL* previous;
    // ctors
    binary_DLL(const char head_char) : carray_ptr {nullptr}, next {nullptr}, previous {nullptr}
    {
         // creating heads for each list
        if (head_char == 'O')
        {
            OGR_previous_DLL = this;
            ++OGR_size;
        }
        else if (head_char == 'C')
        {
            CO2SR_previous_DLL = this;
            ++CO2SR_size;
        }
    }
        // delegate with single arg ctor + add ref to carray
    binary_DLL(char* arg_carray_ptr, const char head_char) : binary_DLL(head_char)
        { 
             // everything in single arg ctor ...
           carray_ptr = arg_carray_ptr; // copy pointer to char array 
        }
};
     // init static vars
    unsigned binary_DLL::OGR_size {0}; 
    unsigned binary_DLL::CO2SR_size {0}; 
    binary_DLL* binary_DLL::OGR_previous_DLL {nullptr}; 
    binary_DLL* binary_DLL::CO2SR_previous_DLL {nullptr}; 

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

double findFinalBinary(std::vector<char*>* vec, const std::int8_t arr_size, std::vector<int>& gamma_vec, std::vector<int>&epsilon_vec)
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

void assignNextBinaryDLLPtr(binary_DLL* binary_DLL_ptr)
{
    static binary_DLL* previous_binary_DLL;
    previous_binary_DLL = binary_DLL_ptr->previous; // get ref to previous object
    previous_binary_DLL->next = binary_DLL_ptr; // assign previous object next member to point to current, new object
}

void createBinaryDLL(std::vector<char*>* vec_of_char, const char gamma_0th_idx)
{
     // FIX -> current block does not assign any values to heads of list
     // this func loops through each binary array and compares the 0th idx values to the most common 0th idx
     // it then creates a new double linked list object & assigns copies the carray ptr to it
     // each loop adds to either the most common OXYGEN ('O') list, or the least common CO2 ('C') list
    for (auto iter {vec_of_char->cbegin()}; iter != vec_of_char->cend(); ++iter)
    {
        if((*iter)[0] == gamma_0th_idx)
        {
             //  if 0th idx is most common -> create new linked list on heap for oxygen sensor list
            binary_DLL* temp_binary_DLL = new binary_DLL {*iter, 'O'};
            assignNextBinaryDLLPtr(temp_binary_DLL);
        }
        else
        {
             // else -> do the same but for CO2 scrubbing rate
            binary_DLL* temp_binary_DLL = new binary_DLL {*iter, 'C'};
            assignNextBinaryDLLPtr(temp_binary_DLL);
        } 
    }
}

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
        std::printf("Product of computed gamma and epsilon values: %.0f",
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
        
    }

    // free heap alloc
    for (auto& free_me : vec_of_char) delete [] free_me;
    return 0;
}