#include "functions.h"

template <class List, class List_entry>
Error_code insert_first(const List_entry &x, List &a_list)
/*
Post: Inserts x into position 0 of list. Any entry formerly
    at position0 and all later entries have their position numbers increased
    by 1
*/
{
    if (a_list.insert(0, x))
        return success;
    else 
        return fail;
}

template <class List, class List_entry>
Error_code remove_first(List_entry &x, List &a_list)
/*
Post: Removes the first entry of the List a_list, copying it to x
*/
{
    if (a_list.remove(0, x))
        return success;
    else
        return fail;
}

template <class List, class List_entry>
Error_code insert_last(const List_entry &x, List &a_list)
/*
Post: Inserts x as the last entry of the List a_list.
*/
{
    int position = 0;

    if (a_list.empty() == false)
        position = a_list.size() - 1;

    if (a_list.insert(position, x))
        return success;
    else
        return fail;
}

template <class List, class List_entry>
Error_code remove_last(List_entry &x, List &a_list)
/*
Post: Removes the last entry of a_list, copying it to x.
*/
{
    int position = a_list.size();

    if (a_list.remove(position, x))
        return success;
    else
        return fail;
}

template <class List, class List_entry>
Error_code median_list(List_entry &x, List &a_list)
/*
Post:  Copies the central entry of the List a_list to x 
    if a_list has an odd number of entries; otherwise, it copies the
    left-central entry of a_list to x.
*/
{
    int position = 0;

    if (a_list.size() % 2 != 0)
        position = a_list.size() / 2 + 1;
    else
        position = a_list.size() / 2 - 1;

    if (a_list.retriece(position, x))
        return success;
    else
        return fail;
}

template <class List, class List_entry>
Error_code interchange(int pos1, int pos2, List &a_list)
/*
Post: Interchanges the entries at positions pos1 and pos2 of the List a_list.
*/
{
    List_entry pos1_value;
    List_entry pos2_value;

    if (a_list.retrieve(pos1, pos1_value) != success)
        return fail;
    if (a_list.retrieve(pos2, pos2_value) != success)
        return fail;
    if (a_list.replace(pos1, pos2_value) != success)
        return fail;
    if (a_list.replace(pos2, pos1_value) != success)
        return fail;

    return success;
}
    
template <class List, class List_entry>
void reverse_traverse_list(List &a_list, void (*visit)(List_entry &))
/*
Post:  Traverses the List a_list in reverse order
    (from its last entry to its first)
*/
{
    for (index n = (max_list - 1); n >= 0; --n)
    {
        List_entry x;
        a_list.retrieve(n, x);
        (*visit)(x);
    }
}

template <class List, class List_entry>
Error_code copy(List &dest, List &source)
/*
Post: Copies all entriesfrom source into dest;
    source remains unchanged. You may assume that dest already exists, but any
    entries already in dest are to be discarded.
*/
{
    if (source.size() > 0)
        dest.clear();

    List_entry temp = 0;

    for (index n = 0; n < source.size(); ++n)
    {
        if (source.retrieve(n, temp) != success)
            return fail;
        if (dest.insert(n, temp) != success)
            return fail;    
    }

    return success;
}

template <class List, class List_entry>
Error_code join(List &list1, List &list2)
/*
Post: Copies all entries from list1 onto the end of list2;
    list1 remains unchanged, as do all the entries previously in list2.
*/
{
    if (list2.full())
        return fail;

    List_entry temp = 0;

    for (index n = 0; n < list1.size(); ++n)
    {
        if (list1.retrieve(n, temp) != success)
            return fail;
        if (insert_last(temp, list2) != success)
            return fail;    
    }

    return success;
}

template <class List, class List_entry>
void reverse(List &a_list)
/*
Post: Reverses the order of all entries in a_list
*/
{
    List_entry temp = 0;
    index start = 0;
    index end = (a_list.size() - 1);

    while (start < end)
    {
        interchange(start, end, a_list);
        start++;
        end--;
    }
}

template <class List, class List_entry>
Error_code split(List &source, List &oddlist, List &evenlist)
/*
Post: Copies all entries from source so that those in odd-numbered
    positions make up oddlist and those in even-numbered positions
    make up evenlist. You may assume that oddlist and evenlist 
    already exist, but any entries they may contain are to be discarded.
*/
{
    List_entry temp = 0;
    oddlist.clear();
    evenlist.clear();

    for (index n = 0; n < source.size(); ++n)
    {
        source.retrieve(n, temp);

        if (n % 2 == 0)
            if (insert_last(temp, evenlist) != success)
                return fail;
        else
            if (insert_last(temp, oddlist) != success)
                return fail;
    }

    return success;
}