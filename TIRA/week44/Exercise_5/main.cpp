#include "node.h"
#include "stack.h"
#include <iostream>


int main()
{
    Stack pancakeStack;

    std::cout << "The size of the stack with size-method: " << pancakeStack.size() << std::endl;
    std::cout << "The size of the stack with getCounter-method: " << pancakeStack.getCounter() << std::endl;

    pancakeStack.push('q');
    pancakeStack.push('e');
    pancakeStack.push('g');

    Stack_entry temp;
    pancakeStack.top(temp);

    std::cout << "The size of the stack with size-method: " << pancakeStack.size() << std::endl;
    std::cout << "The size of the stack with getCounter-method: " << pancakeStack.getCounter() << std::endl;
    std::cout << "The top of the stack " << temp << std::endl;

    return 0;
}