##Exercises week45

Programming Languages 3, 7. exercises:
======================================


Exercise 1.
-----------

Write the following methods for linked queues:

	(a) the method empty,
	(b) the method retrieve,
	(c) the destructor,
	(d) the copy constructor,
	(e) the overloaded assignment operator.
	

Exercise 2.
-----------

Write an implementation of the Extended_queue method full. In light of the
simplicity of this method in the linked implementation, why is it still important
to include it in the linked class Extended_queue?


Exercise 3.
-----------

Write the following methods for the linked class Extended_queue:

	(a) clear; (b) serve_and_retrieve;


Exercise 4.
-----------

For a linked Extended_queue, the function size requires a loop that moves
through the entire queue to count the entries, since the number of entries in
the queue is not kept as a separate member in the class. Consider modifying
the declaration of a linked Extended_queue to add a count data member to the
class. What changes will need to be made to all the other methods of the class?
Discuss the advantages and disadvantages of this modification compared to
the original implementation.
	