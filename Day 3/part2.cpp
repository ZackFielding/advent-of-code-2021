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
    free_me = head->next;
    binary_DLL* cache_next_ptr {nullptr};
    unsigned free_counter {0};

    while (free_me->next != nullptr) 
    {
        cache_next_ptr = free_me->next; // cache ptr to next prior to mem dealloc
        delete free_me; 
        free_me = cache_next_ptr;
        ++free_counter;
        //std::cout << free_counter << " ... ";
    }
    delete free_me; // last item of list
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

     // const ptr to size member ... determine what size member to decrement
    unsigned* const copy_size_ptr = 
        [&head, outcome_str]()->unsigned*
            {
                const char oxygen_str[] {"Oxygen"};
                return (std::strcmp(outcome_str, oxygen_str) == 0) ? &head.OGR_size : &head.CO2SR_size; 
            }();

    while (temp_binary_DLL->next != nullptr)
    {
        if (temp_binary_DLL->carray_ptr[idx] != ref_char)
        {
            // remove from list
            updated_next = temp_binary_DLL->next; // copy of ptr to next obj in list
            traversal_binary_DLL = temp_binary_DLL->previous; // move -1 in list
            traversal_binary_DLL->next = updated_next; // assign -1 obj next to n+1 obj ref

            updated_previous = temp_binary_DLL->previous; // same steps as above but for n+1 previous ptr
            traversal_binary_DLL = temp_binary_DLL->next;
            traversal_binary_DLL->previous = updated_previous;
            //temp_binary_DLL->previous = nullptr; // null prev

            // free memory assoc. with obj that now points nowhere
            delete temp_binary_DLL;
            temp_binary_DLL = updated_next; // cycle to next obj
            ++node_removal_count;
            --(*copy_size_ptr); // decrement correct size ptr
        } 
        else temp_binary_DLL = temp_binary_DLL->next; // cycle to next obj if reference match
    }

        // need to check last item separately
    if (temp_binary_DLL->carray_ptr[idx] != ref_char)
    {
        traversal_binary_DLL = temp_binary_DLL->previous; // traverse back to 2nd last node
        traversal_binary_DLL->next = nullptr; // set next to null ptr
        delete temp_binary_DLL; // dealloc
        ++node_removal_count;
        --(*copy_size_ptr);
    } else 
    {
        temp_binary_DLL = nullptr; // didn't ended up removing last node -> set to nullptr
        delete temp_binary_DLL;
    }

    traversal_binary_DLL = nullptr;
    delete traversal_binary_DLL;
    std::clog << "Number of items removed from " << outcome_str << " list: " << node_removal_count 
        << " ... size of list is now: " << *copy_size_ptr << '\n';
}