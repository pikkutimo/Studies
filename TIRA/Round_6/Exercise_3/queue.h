#ifndef QUEUE_H
#define QUEUE_H

#include "utilities.h"
#include <string>

const int maxqueue = 10; //  small value for testing
typedef std::string Queue_entry;

class Queue {
public:
   Queue();
   bool empty() const;
   Error_code serve();
   Error_code append(const Queue_entry &item);
   Error_code retrieve(Queue_entry &item) const;

protected:
   int count;
   int front, rear;
   Queue_entry entry[maxqueue];
};

class Extended_queue: public Queue {
public:
   bool full() const;
   int size() const;
   void clear();
   Error_code serve_and_retrieve(Queue_entry &item);
   Error_code compare();
};

#endif 