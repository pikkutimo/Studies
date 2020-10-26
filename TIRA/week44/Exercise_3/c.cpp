#include "node.h"
#include <iostream>

void displayList(struct Node *node);

int main(int argc, char* argv[])
{
    //E3 c)
    Node *p0 = new Node('0');
    Node *p1 = p0->next = new Node('1');
    Node *p2 = p1->next = new Node('2', p1);

    displayList(p0);            
}

void displayList(struct Node *node)
{
    int counter{0};
    //traverse the list to display each node
    while (node != NULL && counter != 10)
    {
        std::cout << node->entry <<"-->";
        node = node->next;
        counter++;
    }
 
    if (node == NULL)
        std::cout << "Null" << std::endl;
    else
        std::cout << "\n\nThis was an infinite loop, therefore I decided to end it." << std::endl;
} 