#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream file;
    file.open("data.txt");

    if (!!file)
    {
        std::string str;
        if (file >> str) std::cout << str << '\n';
    }

    file.close();
    return 0;
}