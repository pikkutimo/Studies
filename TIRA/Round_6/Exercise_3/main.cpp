#include "queue.h"
#include "utilities.h"
#include <string>
#include <sstream>

void comparator(std::string&);

int main(){

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
        comparator(input);
    }
    
    return 0;
}

void comparator(std::string& line)
{
    Extended_queue left_queue;
    Extended_queue right_queue;
    bool isColon{false};

    for (auto character : line)
    {
        if (character == ':')
            isColon = true;
        else if (isColon)
            right_queue.append(character);
        else 
            left_queue.append(character);
    }
    
    if (right_queue.empty())
        std::cout << "N";
    else if (right_queue.size() > left_queue.size())
        std::cout << "R";
    else if (right_queue.size() < left_queue.size())
        std::cout << "L";
    else
    {
        Queue_entry left;
        Queue_entry right;
        bool isSame(true);

        while(!left_queue.empty())
        {
            left_queue.serve_and_retrieve(left);
            right_queue.serve_and_retrieve(right);

            if (left != right)
                isSame = false;
                break;
        }

        if (isSame)
            std::cout << "S";
        else
            std::cout << "D";
    }

    std::cout << std::endl;
}
