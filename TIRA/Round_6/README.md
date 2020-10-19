##Programming Languages 3, 5. exercises


#Exercise 1.

Write the remaining methods for queues as implemented in this section:

    (a) empty 			(b) retrieve


#Exercise 2.

Write the remaining methods for extended queues as implemented in this section:

    (a) full 			(b) clear 			(c) serve_and_retrieve
	

#Exercise 3.

Write a function that will read one line of input from the terminal. The input
is supposed to consist of two parts separated by a colon : . As its result, your
function should produce a single character as follows:

N        No colon on the line.
L        The left part (before the colon) is longer than the right.
R        The right part (after the colon) is longer than the left.
D        The left and right parts have the same length but are different.
S        The left and right parts are exactly the same.

>Examples:       Input           Output
>                Sample Sample   N
>                Left:Right      R
>                Sample:Sample   S

Use either a queue or an extended queue to keep track of the left part of the
line while reading the right part.