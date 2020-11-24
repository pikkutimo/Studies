#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "list.h"
#include "utilities.h"

template <class List, class List_entry>
Error_code insert_first(const List_entry &x, List &a_list);

template <class List, class List_entry>
Error_code remove_first(List_entry &x, List &a_list);

template <class List, class List_entry>
Error_code insert_last(const List_entry &x, List &a_list);

template <class List, class List_entry>
Error_code remove_last(List_entry &x, List &a_list);

template <class List, class List_entry>
Error_code median_list(List_entry &x, List &a_list);

template <class List, class List_entry>
Error_code interchange(int pos1, int pos2, List &a_list);
    
template <class List, class List_entry>
void reverse_traverse_list(List &a_list, void (*visit)(List_entry &));

template <class List, class List_entry>
Error_code copy(List &dest, List &source);

template <class List, class List_entry>
Error_code join(List &list1, List &list2);

template <class List, class List_entry>
void reverse(List &a_list);

template <class List, class List_entry>
Error_code split(List &source, List &oddlist, List &evenlist);

#endif