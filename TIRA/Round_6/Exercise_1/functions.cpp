#include "functions.h"

char get_command()
{
   char command;
   bool waiting = true;
   std::cout << "Select command and press <Enter>:";

   while (waiting) {
      std::cin >> command;
      command = tolower(command);
      if (command == 'a' || command == 's' || command == 'r' ||
          command == '#' || command == 'c' || command == 'p' ||
          command == 'h' || command == 'q') waiting = false;


      else {
         std::cout << "Please enter a valid command:"   << std::endl
              << "[A]ppend to queue" << std::endl
              << "[S]erve the queue" << std::endl
              << "[R]etrieve the first element in the queue" << std::endl
              << "[#] of items in the queue" << std::endl
              << "[C]lear the queue" << std::endl
              << "[P]rint the queue" << std::endl
              << "[H]elp" << std::endl
              << "[Q]uit." << std::endl;
      }
   }
   return command;
}

void help()
/*
Post: A help screen for the program is printed, giving the meaning of each
      command that the user may enter.
*/

{
   std::cout << std::endl
        << "This program allows the user to enter one command" << std::endl
        << "(but only one) on each input line." << std::endl
        << "For example, if the command S is entered, then" << std::endl
        << "the program will serve the front of the queue." << std::endl
        << std::endl

        << " The valid commands are:" << std::endl
        << "A - Append the next input character to the extended queue" << std::endl
        << "S - Serve the front of the extended queue" << std::endl
        << "R - Retrieve and print the front entry." << std::endl
        << "# - The current size of the extended queue" << std::endl
        << "C - Clear the extended queue (same as delete)" << std::endl
        << "P - Print the extended queue" << std::endl
        << "H - This help screen" << std::endl
        << "Q - Quit" << std::endl

        << "Press <Enter> to continue." << std::flush;

   char c;
   do {
      std::cin.get(c);
   } while (c != '\n');
}


bool do_command(char c, Extended_queue &test_queue)
/*
Pre:  c represents a valid command.
Post: Performs the given command c on the Extended_queue test_queue.
      Returns false if c == 'q', otherwise returns true.
Uses: The class Extended_queue.
*/
{
   bool continue_input = true;
   Queue_entry x;

   switch (c) {
   case 'a':
      if (test_queue.full())
         std::cout << "The Queue is already full" << std::endl;
      else
      {
         std::cout << "Please enter the entry: ";
         std::cin >> x;
         std::cout << std::endl;

         test_queue.append(x);
      }
      break;

   case 's':
      if (test_queue.empty())
         std::cout << "The queue is already empty - nothing to serve." << std::endl;
      else
         test_queue.serve();
      
      break;
   
   case 'r':
      if (test_queue.retrieve(x) == underflow)
         std::cout << "Queue is empty." << std::endl;
      else
         std::cout << std::endl
              << "The first entry is: " << x
              << std::endl;
      break;

   case '#':
      std::cout << "The queue contains " << test_queue.size()
               << " elements out of " << maxqueue << std::endl; 
      break;

   case 'c':
      std::cout << "Clearing the queue." << std::endl;
      test_queue.clear();
      break;

   case 'p':
      print_queue(test_queue);
      break;

   case 'h':
      help();
      break;

   case 'q':
      std::cout << "Extended queue demonstration finished." << std::endl;
      continue_input = false;
      break;
   }
   return continue_input;
}

void introduction()
/*
Pre:
Post: The purpose of this function is to explain briefly what the program
      does and to show the user how to begin. 
*/
{
   std::cout << "Introduction" << std::endl
      << "This program allows the user to enter one command" << std::endl
      << "(but only one) on each input line." << std::endl
      << "For example, if the command S is entered, then" << std::endl
      << "the program will serve the front of the queue." << std::endl
      << std::endl;
}

void print_queue(Extended_queue poolQueue)
{
   Queue_entry x;
   
   if (poolQueue.empty())
      std::cout << "The queue is empty." << std::endl;
   else
   {
      while(!poolQueue.empty())
      {
         poolQueue.serve_and_retrieve(x);
         std::cout << x << std::endl;
      }
   }
   
   
}