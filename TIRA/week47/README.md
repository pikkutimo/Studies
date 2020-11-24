##Exercises week47

#Data Structures and Program Design in C++

Robert L. Kruse
Alexander J. Ryba


Exercise 1.
-----------

Given the methods for lists described in this section, write functions to do each
of the following tasks. Be sure to specify the preconditions and postconditions
for each function. You may use local variables of types List and List_entry, but
do not write any code that depends on the choice of implementation. Include
code to detect and report an error if a function cannot complete normally.

	- Error_code insert_first(const List_entry &x, List &a_list) inserts entry x into position 0 of the List a_list.
	- Error_code remove_first(List_entry &x, List &a_list) removes the first entry of
	the List a_list, copying it to x.
	- Error_code insert_last(const List_entry &x, List &a_list) inserts x as the last entry
	of the List a_list.
	- Error_code remove_last(List_entry &x, List &a_list) removes the last entry of
	a_list, copying it to x.
	- Error_code median_list(List_entry &x, List &a_list) copies the central entry of the
	List a_list to x if a_list has an odd number of entries; otherwise, it copies the
	left-central entry of a_list to x.
	- Error_code interchange(int pos1, int pos2, List &a_list) interchanges the entries
	at positions pos1 and pos2 of the List a_list.
	- void reverse_traverse_list(List &a_list, void (*visit)(List_entry &)) traverses the
	List a_list in reverse order (from its last entry to its first).
	- Error_code copy(List &dest, List &source) copies all entriesfrom source into dest;
	source remains unchanged. You may assume that dest already exists, but any
	entries already in dest are to be discarded.
	- Error_code join(List &list1, List &list2) copies all entries from list1 onto the end
	of list2; list1 remains unchanged, as do all the entries previously in list2.
	- void reverse(List &a_list) reverses the order of all entries in a_list.
	- Error_code split(List &source, List &oddlist, List &evenlist) copies all entriesfrom
	source so that those in odd-numbered positions make up oddlist and those in
	even-numbered positions make up evenlist. You may assume that oddlist and
	evenlist already exist, but any entries they may contain are to be discarded.
	

Exercise 2.
-----------
Write C++ functions to implement the remaining operations for the contiguous
implementation of a List, as follows:

- The constructor List		
- clear									
- empty														 
- full
- replace
- retrieve
- remove

Exercise 3.
-----------
Write C++ functions to implement the constructors (both forms) for singly
linked and doubly linked Node objects.
	