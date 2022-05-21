#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>

int main ()
{
    std::ifstream input("test.bmp");
    if(!input.good())
    {
        std::cout << "Error of read file!" << std::endl;
    }
    
    std::ofstream output("negatyw.bmp");

      while(!input.eof())
    {
        // TO DO
    }

    output.close();
    input.close();

    return 0;
}
