#include "functions.h"


char get_command()
{
   char command;
   bool waiting = true;
   std::cout << "Select command and press <Enter>:";

   while (waiting) {
      std::cin >> command;
      command = tolower(command);
      if (command == '?' || command == '=' || command == '+' ||
          command == '-' || command == '*' || command == '/' ||
          command == 'x' || command == 'q' ) waiting = false;


      else {
         std::cout << "Please enter a valid command:"   << std::endl
              << "[?]push to stack   [=]print top" << std::endl
              << "[+] [-] [*] [/]   are arithmetic operations" << std::endl
              << "[Q]uit." << std::endl;
      }
   }
   return command;
}


bool do_command(char command, Stack &numbers)
/*
Pre:  The first parameter specifies a valid calculator command.
Post: The command specified by the first parameter
      has been applied to the Stack of numbers given by the second parameter.
      A result of true is returned unless command == 'q'.
Uses: The class Stack.
*/

{
   double p, q;
   switch (command) {
   case '?':
      std::cout << "Enter a real number: " << std::flush;
      std::cin >> p;
      if (numbers.push(p) == overflow)
         std::cout << "Warning: Stack full, lost number" << std::endl;
      break;

   case '=':
      if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else
         std::cout << p << std::endl;
      break;

   case '+':
      if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else {
         numbers.pop();
         if (numbers.top(q) == underflow) {
            std::cout << "Stack has just one entry" << std::endl;
            numbers.push(p);
         }

         else {
            numbers.pop();
            if (numbers.push(q + p) == overflow)
               std::cout << "Warning: Stack full, lost result" << std::endl;
         }
      }
      break;

   case '-':
       if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else {
         numbers.pop();
         if (numbers.top(q) == underflow) {
            std::cout << "Stack has just one entry" << std::endl;
            numbers.push(p);
         }

         else {
            numbers.pop();
            if (numbers.push(q - p) == overflow)
               std::cout << "Warning: Stack full, lost result" << std::endl;
         }
      }
      break;
   
   case '*':
       if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else {
         numbers.pop();
         if (numbers.top(q) == underflow) {
            std::cout << "Stack has just one entry" << std::endl;
            numbers.push(p);
         }

         else {
            numbers.pop();
            if (numbers.push(q * p) == overflow)
               std::cout << "Warning: Stack full, lost result" << std::endl;
         }
      }
      break;

   case '/':
       if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else {
         numbers.pop();
         if (numbers.top(q) == underflow) {
            std::cout << "Stack has just one entry" << std::endl;
            numbers.push(p);
         }

         else {
            numbers.pop();
            if (numbers.push(q / p) == overflow)
               std::cout << "Warning: Stack full, lost result" << std::endl;
         }
      }
      break;

   case 'x':
       if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else {
         numbers.pop();
         if (numbers.top(q) == underflow) {
            std::cout << "Stack has just one entry" << std::endl;
            numbers.push(p);
         }

         else {
            numbers.pop();
            numbers.push(q);
            numbers.push(p);
         }
      }
      break;
    case 'q':
      std::cout << "Calculation finished.\n";
      return false;
   }
   return true;
}

void introduction()
/*
Pre:  
Post:
Uses: 
*/
{
   std::cout << "Introduction." << std::endl;
}

void instructions()
/*
Pre:  
Post: 
Uses: 
*/
{
   std::cout << "Instructions." << std::endl;
}