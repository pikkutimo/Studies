Compilation

    The program is compiled and linked through following command on linux machine or alternatively
    using the included make file. [Requirements are gcc compiler and gnu make.]

    g++ -std=c++11 -o main main.cpp functions.cpp stack.cpp utilities.cpp

    or

    make

Running the program

    ./main

    Running the program with the argument -p activates the prompt mode.

    ./main -p

Testing the program

    My testing consisted of basic calculations done by me and checking the given results by calculator.

    [SUM]: 1 1 + =>2 || 2 3 + => 5 || 134 1413 + => 1547

    [MINUS]: 90 - 13 => 77 || 13123 - 342 => 12781 || 1341341 - 1231341 => 110000

    [MULTIPLY]: 3 3 * => 9 || 27 3 * => 81 || 81 81 * => 6561

    [DIVISION]: 6561 81 / => 81 || 81 9 / => 9 || 9 9 / => 1

    [EXHANGE]: 1 2 x => 1 || 1 3 x => 1

    [EXPONENTIATION]: 12 2 ^ => 144 || 0 ^ => 1 || 100 10 ^ => 100,000,000,000,000,000,000

    [MODULO]: 999 3 % => 0 || 347 7 % => 4 || 7919 % 9 => 8

    [SQUAREROOT]: 9 v => 3 || 6561 v => 81 || 7919 v => 88.9888

    [AVERAGE]: 1 2 3 4 5 a => 3 || 12.2 234.12 352424.2 a = > 117557 || 1000 100 10 1 a => 277.75

    [STACK SUM]: 1 2 3 4 5 s => 15 || 4 6 8 10 12 => 40 || 23.2 141.2 23.1 1341.1 635.24 246.124 => 2409.96

Points I'm aiming for

    The only option is five points.

My contact information

    Timo Vilén
    timo.a.vilen@tuni.fi
    +358 40 595 4534

Hours

    Friday, October 9th - 3 hours - Reconstituting the sources from the book. Some complications relating
                                    to my systems reinstall.

    Monday, October 12th - 2 hours - Added all the functions needed to complete the books example.

    Wednesday, October 14th - 4 hours - Added the parts required for five points. Refactored the codebase
                                        and added some comments.

    Thursday, October 15th - ? hours - Improve the input for the prompt. Finish this document.

Desing decisions

    I decided to split the program into two separate parts based whether command line parameters were 
    used or not. For the base version, I simple created the necessary lines of code to fill the gaps 
    and later on, I refactored these parts into separate functions usable in both versions. For both 
    versions I simple followed the basic layout of the books example.

    The base version excepts input one character at a time, except for the numbers.

    The prompt version reads input one line at a time. After that the function goes through the input
    one character at the time. The action following each character is decided with couple of
    if-statements and a switch-case. After the every operation on the line has been done, the program
    shows the top most element in the stack.

    Both versions continue until the input is q, which ends the loop.