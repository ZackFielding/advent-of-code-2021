#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>

// working day 1 solutions

template<typename ATYPE, size_t ASIZE>
bool readFileToArray(std::ifstream& file, std::array<ATYPE, ASIZE>& depths)
{
    size_t idx {0};
    for (; idx < ASIZE; ++idx)
    {
        if (!(file >> depths.at(idx)))
        {
            std::clog << "Error in file read... terminating...\n";
            break;
        }
    }
    file.close();
    return (idx == ASIZE) ? true : false;
}

template<typename ATYPE, size_t ASIZE>
int determineDepthChange(const std::array<ATYPE,ASIZE>& depths)
{
    int depth_change_tracker {0};
    for (size_t i {1}; i < ASIZE; ++i)
        if ((depths.at(i) - depths.at(i-1)) > 0) ++depth_change_tracker;
    return depth_change_tracker;
}

template<typename ATYPE, size_t ASIZE>
int movingWindowDDC(const std::array<ATYPE,ASIZE>& depths)
{
    auto l_sum3 = [&](size_t s_idx)->int
        { return (depths.at(s_idx) + depths.at(s_idx+1) + depths.at(s_idx+2)); };

    int depth_change_tracker {0};
    for (size_t mw_idx {0}; mw_idx < ASIZE-3; ++mw_idx)
        if (l_sum3(mw_idx+1) - l_sum3(mw_idx) > 0) ++depth_change_tracker;
    return depth_change_tracker;
}

int main()
{
    std::ifstream sfi; // stream file in
    sfi.open("data.txt"); // open file (read only as ifstream obj)
    std::array<int, 2000> depths;
    
    if (!!sfi)
    {
        if (readFileToArray<int,depths.size()>(sfi, depths)) // if file read to vec successfully...
        {
           std::cout << "Changes in depth occured " 
            << determineDepthChange<int,depths.size()>(depths) << " times.\n"
            << "Moving window depth change found " << movingWindowDDC(depths) << " times.\n";
        }
    }

   return 0; 
}