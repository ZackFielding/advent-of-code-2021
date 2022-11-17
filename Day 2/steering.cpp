#include <iostream>
#include <string>
#include <fstream>
#include <string>

void getDisplacementWithAim(std::ifstream& sfi)
{
    unsigned i_hold {0}, depth {0};
    signed aim {0};
    int horizontal {0}, direction_counter {0};
    std::string str_hold;
    while (sfi >> str_hold && sfi >> i_hold)
    {
        if (str_hold == "forward")
        {
            horizontal += i_hold;
            depth += aim * i_hold;
        }
        else (str_hold == "up") ? aim -= i_hold : aim += i_hold;
        ++direction_counter;
    }
    std::cout << "The submarine has moved " << depth << " units down, and " << horizontal 
                << " units forward for a product of " << (depth * horizontal) << " units.\n" 
                << "  A total of " << direction_counter << " movements were recorded.\n"; 

}

void getDisplacement(std::ifstream& sfi)
{
    unsigned i_hold {0}, depth {0};
    int horizontal {0}, direction_counter {0};
    std::string str_hold;
    while (sfi >> str_hold && sfi >> i_hold)
    {
        if (str_hold == "forward") horizontal += i_hold;
        else (str_hold == "up") ? depth -= i_hold : depth += i_hold;
        ++direction_counter;
    }
    std::cout << "The submarine has moved " << depth << " units down, and " << horizontal 
                << " units forward for a product of " << (depth * horizontal) << " units.\n" 
                << "  A total of " << direction_counter << " movements were recorded.\n"; 
}

int main()
{
    std::ifstream sfi;
    sfi.open("data.txt");

    if (!!sfi) getDisplacement(sfi); 

     // clear any failed file stream flags & reset file poniter
    sfi.clear(); 
    sfi.seekg(0L, std::ios_base::beg);

    std::cout << "After finding and reading the manual... ";
    if (!!sfi) getDisplacementWithAim(sfi);

    sfi.close();
    return 0;
}
