#include <iostream>
#include "list.h"
#include "utilities.h"
#include "functions.h"

int main()
{
    //typedef List<int> Intlist;
    
    List<int> blackList;
    int temp = 0;
    

    blackList.insert(0, 1);
    blackList.insert(1, 11);
    blackList.insert(2, 111);
    blackList.insert(3, 1111);
    blackList.insert(4, 11111);
     
    std::cout << std::boolalpha << blackList.empty() << std::endl
        << blackList.full() << std::endl
        << blackList.size() << std::endl;

    blackList.retrieve(0, temp);
    std::cout << "0." << temp << std::endl;

    blackList.retrieve(1, temp);
    std::cout << "1." << temp << std::endl;

    blackList.retrieve(2, temp);
    std::cout << "2." << temp << std::endl;

    blackList.retrieve(3, temp);
    std::cout << "3." << temp << std::endl;
    
    blackList.retrieve(4, temp);
    std::cout << "4." << temp << std::endl;

    blackList.insert(4, 22222);

    blackList.retrieve(4, temp);
    std::cout << "4." << temp << std::endl;

    blackList.retrieve(5, temp);
    std::cout << "5." << temp << std::endl;

    return 0;
}
