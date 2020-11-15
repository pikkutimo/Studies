#Week 46 home assignment

##Exercise 1.

Exercise 5.1 E1 (the exact assignment can be found in the file 5.1_E1_E2.jpg in moodle)
	

	
## Exercise 2.

Exercise 5.1 E2 (the exact assignment can be found in the file 5.1_E1_E2.jpg in moodle)



##Exercise 3.

This task is solved by programming the program to display execution times,
numbers of transfer orders, etc. (see below). You can then draw from these running results e.g., Excel charts; for example, a diagram showing the number of transfer instructions development as a function of the number of disks.

Confirm that the running time for the program hanoi increases approximately
like a constant multiple of 2 to a power of n, where n is the number of disks moved. To do this, make disks a variable, comment out the line that writes a message to the
user, and run the program for several successive values of disks, such as 10, 11,
... , 15. How does the CPU time change from one value of disks to the next?

Also consider the following ways to explore the heaviness of running Hanoi program:
- counting the number of transfer orders
- calculation of calls to the move() subroutine
- both of the former are observed, etc.



##Exercise 4.

Run the two different Hanoi programs to make sure that both algorithms solve the Hanoi tower problem (basic recursive and the one with tail recursion removed) work
in exactly the same way and correctly. Tip: Compare the running results of both programs to each other in relatively short runs (few disks). For example, on Unix / Linux systems with diff command you can compare the similarity of the contents of two text files; do so that these text files contain the outputs of the runned programs. For example in cmd-tool you can run hanoi as follows: hanoi.exe > output.txt . Make this with the other program as well and then compare output files with diff.



##Exercise 5.

Analyze by programming and using Excel for output processing how recursive version of Fibonacci() subroutine behaves:
- how many Fibonacci() calls are generated from arbitrary Fibonacci(n)
   call (n = 0, 1, 2, ..., 7, 8, ... <choose a reasonable upper limit for this!>). This
   must be analyzed by programming, i.e. your program will print this information with different values of n to the console
- how much time is spent processing Fibonacci() call hierarchies of different sizes
   (use, for example, the clock() system call here). Again, your program will print this information to the console
- how deep is the Fibonacci() call tree with different values of n (= how many Fibonacci() calls are at most waiting for a child Fibonacci() call to finish during processing)

Copy and paste your driving results from console output into Excel sheet to draw with it illustrative graphs for the question issues.



##Exercise 6.

The greatest common divisor (gcd) of two positive integers is the largest 
integer that divides both of them. Thus, for example, the gcd of 8 and 
12 is 4, the gcd of 9 and 18 is 9, and the gcd of 16 and 25 is 1.

(a) Write a nonrecursive function int gcd(int x, int y), where x and y 
    are required to be positive integers, that searches through the 
	positive integers until it finds the largest integer dividing both 
	x and y.
	
(b) Write a recursive function int gcd(int x, int y) that implements 
    Euclid’s algorithm: If y = 0, then the gcd of x and y is x; 
	otherwise the gcd of x and y is the same as the gcd of y and x%y.
	
	Recall that % is the modulus operator: The result of x%y is the 
	remainder after the integer division of integer x by nonzero 
	integer y.
	
(c) Rewrite the function of part (b) into iterative form.