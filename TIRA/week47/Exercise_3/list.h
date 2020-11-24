#ifndef LIST_H
#define LIST_H

#include "utilities.h"
#include <iostream>

typedef int index;

template <class Node_entry>
struct Node {
//  data members
   Node_entry entry;
   Node<Node_entry> *next;
//  constructors
   Node();
   Node(Node_entry item, Node<Node_entry> *link = NULL);
};

template <class Node_entry>
Node<Node_entry>::Node()
{
   next = NULL;
}

// template <class Node_entry>
// Node<Node_entry>::Node(Node_entry item, Node<Node_entry> *link = NULL)
// {
//     entry = item;
//     next = link;
// }

template <class List_entry>
class List { //Single linked list
public:
//  Specifications for the methods of the list ADT go here.
    List();
    int size() const;
    bool full() const;
    bool empty() const;
    void clear();
    void traverse(void (*visit)(List_entry &));
    Error_code retrieve(int position, List_entry &x) const;
    Error_code replace(int position, const List_entry &x);
    Error_code remove(int position, List_entry &x);
    Error_code insert(int position, const List_entry &x);
//  The following methods replace compiler-generated defaults.
    ~List();
    List(const List<List_entry> &copy);
   void operator =(const List<List_entry> &copy);
protected:
//  Data members for the linked list implementation now follow.
   int count;
   Node<List_entry> *head;

//  The following auxiliary function is used to locate list positions
   Node<List_entry> *set_position(int position) const;
};

template <class List_entry>
List<List_entry>::List()
/*
Post: The List has been created and is initialized to be empty.
*/
{
    count = 0;
    head = NULL;
    //available = max_list;
}

template <class List_entry>
List<List_entry>::~List()
/*
Post: The List has been deleted.
*/
{
    while (head != 0)
    {
        Node<List_entry> *temp = head->next;
        delete head;
        head = temp;
    }
}

template <class List_entry>
int List<List_entry>::size() const
/*
Post: The function returns the number of entries in the List.
*/
{
   return count;
}

template <class List_entry>
bool List<List_entry>::full() const
/*
Post: The function returns true if List is full.
*/
{
   //For simplicity let's say the list will never be full
   return false;
}

template <class List_entry>
bool List<List_entry>::empty() const
/*
Post: The function returns true if List is empty.
*/
{
    return count == 0;
}

template <class List_entry>
void List<List_entry>::clear()
/*
Post:  All List entries have been removed; the List is empty.
*/
{
    Node<List_entry> *current = head;
    Node<List_entry> *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
        count--;
    }

}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/*
Post: The action specified by function *visit has been performed on every
      entry of the List, beginning at position 0 and doing each in turn.
*/
{
    Node<List_entry> *current = head;
    Node<List_entry> *next;

    while (current != NULL)
    {
        next = current->next;
        (*visit)(current->entry);
        current = next;
    }
}

template <class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x) const
/*
Post: If 0 ≤ position < n, where n is the number of entries in the List,
    the function succeeds: The entry at position is copied to x; all
    List entries remain unchanged.
    Else: The function fails with a diagnostic error code.
*/
{
    int counter = 0;
    if (this->empty())
        return underflow;

    Node<List_entry> *current = head;
    Node<List_entry> *next;

    while (current != NULL)
    {
        if (counter == position)
        {
            x = current->entry;
            break;
        }

        counter ++;    
        next = current->next;
        current = next;
    }
    
    return success;
}

template <class List_entry>
Error_code List<List_entry>::replace(int position, const List_entry &x)
/*
Post: If 0 ≤ position < n, where n is the number of entries in the List,
    the function succeeds: The entry at position is replaced by x; all
    other entries remain unchanged.
    Else: The function fails with a diagnostic error code.
*/
{
    int counter = 0;
    if (this->empty())
        return underflow;

    Node<List_entry> *current = head;
    Node<List_entry> *next;

    while (current != NULL)
    {
        if (counter == position)
        {
            current->entry = x;
            break;
        }

        counter ++;    
        next = current->next;
        current = next;
    }

    return success;
}

template <class List_entry>
Error_code List<List_entry>::remove(int position, List_entry &x)
/*
Post: If 0 ≤ position < n, where n is the number of entries in the List,
    the function succeeds: The entry at position is removed from the
    List, and all later entries have their position numbers decreased
    by 1. The parameter x records a copy of the entry formerly at
    position.
    Else: The function fails with a diagnostic error code   
*/
{
    int counter = 0;

    if (this->empty())
        return underflow;

    Node<List_entry> *current = head;
    Node<List_entry> *next;
    Node<List_entry> *previous;

    while (current != NULL)
    {
        if (counter == position)
        {
            x = current->entry;
            previous->next = current->next;
            free(current);
            break;
        }

        counter ++;    
        next = current->next;
        previous = current;
        current = next;
    }

    return success;
}

template <class List_entry>
Error_code List<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 ≤ position ≤ n, where n is the number
    of entries in the List, the function succeeds: Any entry formerly
    at position and all later entries have their position numbers increased
    by 1, and x is inserted at position in the List.
    Else: The function fails with a diagnostic error cod
*/
{
    int counter = 0;

    if (position < 0 || position > count)
        return utility_range_error;    

    Node<List_entry> *current = head;
    Node<List_entry> *next;
    Node<List_entry> *previous;

    while (current != NULL)
    {
        if (counter == position)
        {
            Node<List_entry> *insertion = new Node<List_entry>;
            insertion->entry = x;
            previous->next = insertion;
            insertion->next = current;
            count++;
            
            return success;
        }

        counter ++;    
        next = current->next;
        previous = current;
        current = next;
    }

    return success;
}

template <class List_entry>
Node<List_entry> *List<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List; 0 <= position < count.
Post: Returns a pointer to the Node in position.
*/
{
   Node<List_entry> *q = head;
   for (int i = 0; i < position; i++) q = q->next;
   return q;
}

#endif