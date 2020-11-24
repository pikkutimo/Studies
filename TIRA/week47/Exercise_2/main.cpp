#include <iostream>
#include "list.h"
#include "utilities.h"
#include "functions.h"

int main()
{
    //typedef List<int> Intlist;
    
    List<int> blackList;
    int temp = 0;
    

    blackList.insert(0, 2);
    blackList.insert(1, 22);
    blackList.insert(2, 222);
    blackList.insert(3, 2222);
    blackList.insert(4, 22222);
     
    std::cout << std::boolalpha << "Is the list empty? " << blackList.empty() << std::endl
        << "Is the list full? " <<blackList.full() << std::endl
        << "What is the size of the list? " << blackList.size() << std::endl;

    blackList.retrieve(0, temp);
    std::cout << "0." << temp << std::endl;

    blackList.retrieve(1, temp);
    std::cout << "1." << temp << std::endl;

    blackList.retrieve(2, temp);
    std::cout << "Current 2." << temp << std::endl
        << "Let's remove the item from the index 2..." << std::endl;

    blackList.remove(2, temp);

    blackList.retrieve(2, temp);
    std::cout << "Current 2." << temp << std::endl;

    blackList.retrieve(3, temp);
    std::cout << "3." << temp << std::endl;
    
    // blackList.retrieve(4, temp);
    // std::cout << "4." << temp << std::endl;

    // blackList.insert(4, 22222);

    // blackList.retrieve(4, temp);
    // std::cout << "4." << temp << std::endl;

    // blackList.retrieve(5, temp);
    // std::cout << "5." << temp << std::endl;

    return 0;
}
