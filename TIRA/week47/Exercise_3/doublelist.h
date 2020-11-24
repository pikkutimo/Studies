#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include "utilities.h"
#include <iostream>

// Double linked list

template <class dNode_entry>
struct dNode {
//  data members
   dNode_entry entry;
   dNode<dNode_entry> *next;
   dNode<dNode_entry> *back;
//  constructors
   dNode();
   dNode(dNode_entry item, dNode<dNode_entry> *link = NULL);
};

template <class dNode_entry>
dNode<dNode_entry>::dNode()
{
   next = NULL;
   back = NULL;
}

template <class List_entry>
class DoubleList { //Single linked list
public:
//  Specifications for the methods of the list ADT go here.
    DoubleList();
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
    ~DoubleList();
    DoubleList(const List<List_entry> &copy);
   void operator =(const List<List_entry> &copy);
protected:
//  Data members for the linked-list implementation with
//  current position follow:
   int count;
   mutable int current_position;
   dNode<List_entry> *head;
   mutable dNode<List_entry> *current;
   //  The following auxiliary function is used to locate list positions
   void set_position(int position) const;
};

template <class List_entry>
DoubleList<List_entry>::DoubleList()
/*
Post: The List has been created and is initialized to be empty.
*/
{
    head = new dNode<List_entry>;
    head->next = head->back = head;
    count = 0;
}

template <class List_entry>
DoubleList<List_entry>::~DoubleList()
/*
Post: The List has been created and is initialized to be empty.
*/
{
    dNode<List_entry> *p = head->next;

    while (p != head) {
        dNode<List_entry> *next = p->next;
        delete p;
        p = next;
    }

    delete head; 
}

template <class List_entry>
int DoubleList<List_entry>::size() const
/*
Post: The function returns the number of entries in the List.
*/
{
   return count;
}

template <class List_entry>
bool DoubleList<List_entry>::full() const
/*
Post: The function returns true if List is full.
*/
{
   //For simplicity let's say the list will never be full
   return false;
}

template <class List_entry>
bool DoubleList<List_entry>::empty() const
/*
Post: The function returns true if List is empty.
*/
{
    return count == 0;
}

template <class List_entry>
void DoubleList<List_entry>::clear()
/*
Post:  All List entries have been removed; the List is empty.
*/
{
    dNode<List_entry> *temp = new dNode<List_entry>;

    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

template <class List_entry>
void DoubleList<List_entry>::traverse(void (*visit)(List_entry &))
/*
Post: The action specified by function *visit has been performed on every
      entry of the List, beginning at position 0 and doing each in turn.
*/
{
   dNode<List_entry> *temp = new dNode<List_entry>;

    while(head != NULL) {
        temp = head;
        (*visit)(head);
        head = head->next;
    }
}

template <class List_entry>
Error_code DoubleList<List_entry>::retrieve(int position, List_entry &x) const
/*
Post: If 0 ≤ position < n, where n is the number of entries in the List,
    the function succeeds: The entry at position is copied to x; all
    List entries remain unchanged.
    Else: The function fails with a diagnostic error code.
*/
{
    dNode<List_entry> *current = head;
    int count = 0;

    while (current != NULL) {
        if (count == position)
        {
            x = current->entry;
            return success;
        }    
        count++;
        current = current->next;
    }

    return utility_range_error;
}

template <class List_entry>
Error_code DoubleList<List_entry>::replace(int position, const List_entry &x)
/*
Post: If 0 ≤ position < n, where n is the number of entries in the List,
    the function succeeds: The entry at position is replaced by x; all
    other entries remain unchanged.
    Else: The function fails with a diagnostic error code.
*/
{
    dNode<List_entry> *current = head;
    int count = 0;

    while (current != NULL) {
        if (count == position)
        {
            current->entry = x;
            return success;
        }    
        count++;
        current = current->next;
    }

    return utility_range_error;
}

template <class List_entry>
Error_code DoubleList<List_entry>::remove(int position, List_entry &x)
/*
Post: If 0 ≤ position < n, where n is the number of entries in the List,
    the function succeeds: The entry at position is removed from the
    List, and all later entries have their position numbers decreased
    by 1. The parameter x records a copy of the entry formerly at
    position.
    Else: The function fails with a diagnostic error code   
*/
{
    dNode<List_entry> *current = head;
    dNode<List_entry> *previous;
    int count = 0;

    while (current != NULL) {
        if (count == position)
        {
            x = current->entry;
            previous->next = current->next;
            free(current);
            
            return success;
        }    
        count++;
        previous = current;
        current = current->next;
    }

    return utility_range_error;
}

template <class List_entry>
Error_code DoubleList<List_entry>::insert(int position, const List_entry &x)
/*
Post: If the List is not full and 0 <= position <= n,
      where n is the number of entries in the List, the function succeeds:
      Any entry formerly at position and all later entries have their
      position numbers increased by 1 and x is inserted at position of the List.
      Else: the function fails with a diagnostic error code.
*/
{
   dNode<List_entry> *new_dNode, *following, *preceding;
   if (position < 0 || position > count)
        return utility_range_error;
   if (position == 0) {
      if (count == 0) following = NULL;
      else {
         set_position(0);
         following = current;
      }
      preceding = NULL;
   }
   else {
      set_position(position - 1);
      preceding = current;
      following = preceding->next;
   }
   new_dNode = new dNode<List_entry>(x, preceding, following);

   if (new_dNode == NULL) return overflow;
   if (preceding != NULL) preceding->next = new_dNode;
   if (following != NULL) following->back = new_dNode;
   current = new_dNode;
   current_position = position;
   count++;
   return success;
}

template <class List_entry>
void DoubleList<List_entry>::set_position(int position) const
/*
Pre:  position is a valid position in the List: 0 <= position < count.
Post: The current dNode pointer references the dNode at position.
*/
{
   if (current_position <= position)
      for ( ; current_position != position; current_position++)
         current = current->next;
   else
      for ( ; current_position != position; current_position--)
         current = current->back;
}

#endif