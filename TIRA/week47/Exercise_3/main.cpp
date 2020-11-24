#include <iostream>
#include "list.h"
#include "doublelist.h"
#include "utilities.h"

int main()
{
    std::cout << "Single linked list" << std::endl;

    List<int> listA;
    std::cout << std::boolalpha << "ListA is empty? " << listA.empty() << std::endl
            << "ListA is full? " << listA.full() << std::endl
            << "ListA contains how many nodes? " << listA.size() << std::endl;

    DoubleList<char> listB;
    std::cout << std::boolalpha << "ListB is empty? " << listB.empty() << std::endl
            << "ListB is full? " << listB.full() << std::endl
            << "ListB contains how many nodes? " << listB.size() << std::endl;

    return 0;
}
