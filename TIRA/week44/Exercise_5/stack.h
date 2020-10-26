#ifndef STACK_H
#define STACK_H

#include "node.h"
#include "utilities.h"

typedef char Stack_entry;

class Stack {
public:
//  Standard Stack methods
   Stack();
   bool empty() const;
   int size();
   int getCounter() const;
   Error_code push(const Stack_entry &item);
   Error_code pop();
   Error_code top(Stack_entry &item) const;
//  Safety features for linked structures
   ~Stack();
   Stack(const Stack &original);
   void operator =(const Stack &original);
protected:
   Node *top_node;
private:
   int counter;
};

#endif