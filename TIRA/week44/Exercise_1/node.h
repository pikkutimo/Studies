#ifndef NODE_H
#define NODE_H

#include <cstddef>

typedef double Node_entry;

struct Node {
//  data members
   Node_entry entry;
   Node *next;
//  constructors
   Node();
   Node(Node_entry item, Node *add_on = NULL);
};

#endif 