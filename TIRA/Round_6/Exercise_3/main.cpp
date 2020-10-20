#include "queue.h"
#include "utilities.h"
#include <string>
#include <sstream>

void comparator(std::string&, Extended_queue&);

int main(){

    Extended_queue test_queue;
    
    std::cout << "The input is supposed to consist of two parts separated by a colon : ." << std::endl
                << "As its result, the output should be a single character based on the input:" << std::endl
                << std::endl
                << "N\tNo colon on the line." << std::endl
                << "L\tThe left part (before the colon) is longer than the right." << std::endl
                << "R\tThe right part (after the colon) is longer than the left." << std::endl
                << "D\tThe left and right parts have the same length but are different." << std::endl
                << "S\tThe left and right parts are exactly the same." << std::endl
                << "Q\tTo quit" << std::endl
                << std::endl;

    std::string input{""};
    bool comparatorOn{true};
    
    while(comparatorOn)
    {
        std::getline(std::cin, input);
        if (input == "q" || input == "Q")
            comparatorOn = false;
        comparator(input, test_queue);
    }
    
    return 0;
}

void comparator(std::string& line, Extended_queue& test_queue)
{
    
    std::stringstream str(line);
    bool colonIs{false};

    std::string buffer{""};

    while(str >> buffer)
    {
        if (buffer == ":") colonIs = true;
        else
            test_queue.append(buffer);
    }
    
    if (colonIs == false)
        std::cout << "N" << std::endl;
    else
    {
        test_queue.compare();
    }
    
}
