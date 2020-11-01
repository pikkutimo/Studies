#include "queue.h"

Queue::Queue()
/*
Post: The Queue is initialized to be empty.
*/
{
   front = rear = NULL;
}


bool Queue::empty() const
/*
Post: Returns true or false whether the queue is empty or not.
*/
{
    if (front == NULL && rear == NULL)
        return true;

    return false;
}


Error_code Queue::append(const Queue_entry &item)
/*
Post: Add item to the rear of the Queue and return a code of success
      or return a code of overflow if dynamic memory is exhausted.
*/
{
   Node *new_rear = new Node(item);
   if (new_rear == NULL) return overflow;
   if (rear == NULL) front = rear = new_rear;
   else {
      rear->next = new_rear;
      rear = new_rear;
   }
   return success;
}


Error_code Queue::serve()
/*
Post: The front of the Queue is removed.  If the Queue
      is empty, return an Error_code of underflow.
*/
{
   if (front == NULL) return underflow;
   Node *old_front = front;
   front = old_front->next;
   if (front == NULL) rear = NULL;
   delete old_front;
   return success;
}

Error_code Queue::retrieve(Queue_entry &item) const
/*
Post: Get the value from the front of the Queue
*/
{
    if (front == NULL)
        return underflow;
    
    item = front->entry;
    return success;
}

Queue::~Queue()
/*
Post: The Queue and every node within is destroyed.
*/
{
    while(!empty())
    {
        serve();
    }

    delete rear;
    delete front;
}

Queue::Queue(const Queue &original)
/*
Post: Copy constructor.
*/
{
    Node *queue_node = original.front;
    while (queue_node != NULL)
    {
        append(queue_node->entry);
        queue_node = queue_node->next;
    }
}

void Queue::operator =(const Queue &original)
/*
Overloaded assignment operator
*/
{
   Queue *new_copy = new Queue(original);
   front = new_copy->front;
   rear = new_copy->rear;
}

int Extended_queue::size() const
/*
Post: Return the number of entries in the Extended_queue.
*/
{
   Node *window = front;
   int count = 0;
   while (window != NULL) {
      window = window->next;
      count++;
   }
   return count;
}