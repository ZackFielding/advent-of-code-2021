#include <iostream>
#include <string>
#include <fstream>
#include <string>

int main()
{
    std::ifstream sfi;
    sfi.open("data.txt");

    if (!!sfi)
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
                    << " units for a product of " << (depth * horizontal) << " units.\n" 
                    << "  A total of " << direction_counter << " movements were recorded.\n"; 
    } 
    sfi.close();
    return 0;
}
