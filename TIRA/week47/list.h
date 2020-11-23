#ifndef LIST_H
#define LIST_H

#include "utilities.h"
#include <iostream>

typedef int index;
const int max_list = 10; //  small value for testing purposes


template <class List_entry>
class Node {
public:
   List_entry entry;
   index next;
};


template <class List_entry>
class List {
public:
//  Methods of the list ADT
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

protected:
//  Data members
   Node<List_entry> workspace[max_list];
   index available, head;
   int count;
};

template <class List_entry>
List<List_entry>::List()
/*
Post: The List has been created and is initialized to be empty.
*/
{
    count = 0;
    head = 0;
    //available = max_list;
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
    return count == max_list;
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
    count = 0;
    available = max_list;
}

template <class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &))
/*
Post: The action specified by function *visit has been performed on every
      entry of the List, beginning at position 0 and doing each in turn.
*/
{
   for (index n = 0; n != -1; n = workspace[n].next)
      (*visit)(workspace[n].entry);
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
    if (this->empty())
        return fail;
    else if (position >= 0 && position < max_list)
    {
        x = workspace[position].entry;
        return success;
    }
    else
        return fail;
    
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
    if (this->empty())
        return fail;
    else if (position >= 0 && position < max_list)
    {
        workspace[position].entry = x;
        return success;
    }
    else
        return fail;
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
    if (this->empty())
        return fail;
    else if (position >= 0 && position < max_list)
    {
        x = workspace[position].entry;

        for (index n = position; n < (max_list - 1); n++)
        {
            workspace[n].entry = workspace[n+1].entry;
        }

        return success;
    }
    else
        return fail;
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
    if (this->full())
        return fail;
    else if (position >= this->count)
    {
        workspace[position].entry = x;
        count++;
    }
    else
    {
        List_entry current = workspace[position].entry;
        List_entry next;
        workspace[position].entry = x;
        position++;
        count++;

        while (position <= count)
        {
            next = workspace[position].entry;
            workspace[position].entry = current;
            current = next;
            position++; 
        }
    }

    return success;
}

#endif