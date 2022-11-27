#include <iostream>
#include <vector>
#include <cstring>

#include "part2.hpp"
#include "binary_DLL.hpp"

void createBinaryDLL(std::vector<char*>* vec_of_char, const char gamma_0th_idx)
{
     // this func loops through each binary array and compares the 0th idx values to the most common 0th idx
     // it then creates a new double linked list object & assigns copies the carray ptr to it
     // each loop adds to either the most common OXYGEN ('O') list, or the least common CO2 ('C') list
    for (auto iter {vec_of_char->cbegin()}; iter != vec_of_char->cend(); ++iter)
    {
        if((*iter)[0] == gamma_0th_idx) new binary_DLL(*iter, 'O');
        else new binary_DLL (*iter, 'C');
    }
}

void freeListHeap(binary_DLL* head)
{
    binary_DLL* free_me = new binary_DLL('T'); // temp to free
    free_me = head->next; // assign to 1st non-head obj node
    free_me = free_me->next; // skip to 2nd node (deleting previous obj .. head is NOT a heap alloc)
    unsigned free_counter {0};
    while (free_me != nullptr) // if previous is not a nullptr (i.e., end of list) 
    {
        delete free_me->previous;  // delete obj behind
        free_me = free_me->next; // set free me to next obj
        ++free_counter;
    }
    delete free_me;
    std::clog << "Number of nodes with heap memory freed: " << free_counter << '\n';
}

void printBinaryDLLArrays(binary_DLL* head, const char head_char)
{
    binary_DLL* ptr_to_next = new binary_DLL('T'); 
    ptr_to_next = head->next;
    while (ptr_to_next != nullptr) // if != nullptr (i.e., end of list)
    {
        std::cout << ptr_to_next->carray_ptr << '\n';     
        ptr_to_next = ptr_to_next->next; // assign next list to next var
    }

    delete ptr_to_next;
    std::cout << "Size of list: " 
        << ((head_char == 'O') ? head->OGR_size : head->CO2SR_size) << '\n'; 
}

void traverseRemove(const char* outcome_str, binary_DLL& head, const int idx, const char ref_char)
{
    // loop through list accessing idx-th carray value
        // if value != ref_char -> remove from list && and correct list pointers 
    binary_DLL* temp_binary_DLL = new binary_DLL{'T'};
    temp_binary_DLL = head.next;
    binary_DLL* traversal_binary_DLL = new binary_DLL{'T'};
    binary_DLL* updated_next {nullptr}, *updated_previous {nullptr};
    unsigned node_removal_count {0};
    unsigned* copy_size_ptr = 
        [&head, outcome_str]()->unsigned*
            {return (std::strcmp(outcome_str, "Oyxgen")) ? &head.OGR_size : &head.CO2SR_size; }();

    while (temp_binary_DLL != nullptr)
    {
        if (temp_binary_DLL->carray_ptr[idx] != ref_char)
        {
            // remove from list
            updated_next = temp_binary_DLL->next; // copy of ptr to next obj in list
            traversal_binary_DLL = temp_binary_DLL->previous; // move -1 in list
            traversal_binary_DLL->next = updated_next; // assign -1 obj next to n+1 obj ref
            temp_binary_DLL->next = nullptr; // null current obj next ptr

            updated_previous = temp_binary_DLL->previous; // same steps as above but for n+1 previous ptr
            traversal_binary_DLL = temp_binary_DLL->next;
            temp_binary_DLL->previous = updated_previous;
            temp_binary_DLL->previous = nullptr; // null prev

            // free memory assoc. with obj that now points nowhere
            delete temp_binary_DLL;
            temp_binary_DLL = updated_next; // cycle to next obj
            ++node_removal_count;
            --(*copy_size_ptr); // decrement correct size ptr
        }
        temp_binary_DLL = temp_binary_DLL->next; // cycle to next obj if reference match
    }

    delete temp_binary_DLL;
    delete traversal_binary_DLL;
    std::clog << "Number of items removed from " << outcome_str << " list: " << node_removal_count << '\n';
}