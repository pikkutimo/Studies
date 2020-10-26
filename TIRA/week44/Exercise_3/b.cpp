#include "node.h"
#include <iostream>

void displayList(struct Node *node);

int main(int argc, char* argv[])
{
    //E3 b)
    Node firstNode('0');
    Node *p0 = &firstNode;
    Node *p1 = new Node('1', p0);
    Node *p2 = new Node('1', p0);

    displayList(p1);
    displayList(p2);
}

void displayList(struct Node *node)
{
      //traverse the list to display each node
      while (node != NULL)
      {
            std::cout << node->entry <<"-->";
            node = node->next;
      }
 
      if (node == NULL)
      std::cout << "Null" << std::endl; 
} 