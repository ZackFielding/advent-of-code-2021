#ifndef BINARY_DLL_HPP
#define BINARY_DLL_HPP

class binary_DLL // double linked list
{
    static binary_DLL* OGR_previous_DLL; // caches previous binary obj for next obj to be created
    static binary_DLL* CO2SR_previous_DLL;
public:
    static unsigned OGR_size; // tracks list size
    static unsigned CO2SR_size; // tracks list size
    char* carray_ptr;
    binary_DLL* next;
    binary_DLL* previous;
    // ctors
    binary_DLL(const char head_char);
    // delegate with single arg ctor + add ref to carray
    binary_DLL(char* arg_carray_ptr, const char head_char);
};
#endif