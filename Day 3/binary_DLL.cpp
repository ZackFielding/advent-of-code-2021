#include "binary_DLL.hpp"
#include <iostream>

binary_DLL::binary_DLL(const char head_char) : carray_ptr {nullptr}, next {nullptr}, previous {nullptr}
{
    if (head_char == 'O') OGR_previous_DLL = this;
    else if (head_char == 'C') CO2SR_previous_DLL = this;
    else std::clog << "Temporary instance of binary_DLL constructed ... no static prevous pointer set.\n";
}

binary_DLL::binary_DLL(char* arg_carray_ptr, const char head_char) : carray_ptr {arg_carray_ptr}, next {nullptr}, previous {nullptr} 
{
     // set previous obj->next to this obj* ...
        // set local this->previous to current static previous
        // set static previous to this
    binary_DLL* copy_of_this {this}; // copy this to allow previous->next assignment
    if (head_char == 'O')
    {
        OGR_previous_DLL->next = copy_of_this;
        this->previous = OGR_previous_DLL;
        OGR_previous_DLL = this;
        ++OGR_size; // increment list size tracker
    }
    else if (head_char == 'C') 
    {
        CO2SR_previous_DLL->next = copy_of_this;
        this->previous = CO2SR_previous_DLL;
        CO2SR_previous_DLL = this;
        ++CO2SR_size;
    }
}
