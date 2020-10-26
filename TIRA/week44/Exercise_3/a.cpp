#include "node.h"
#include <iostream>

void displayList(struct Node *node);

int main(int argc, char* argv[])
{
      //E3. a)
      Node *p0 = new Node('0');
      Node *p1 = p0->next = new Node('1');

      displayList(p0);
 
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