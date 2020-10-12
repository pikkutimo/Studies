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
          command == '%' || command == '^' || command == 'v' ||
          command == 'x' || command == 's' || command == 'a' ||
          command == 'q' ) waiting = false;


      else {
         std::cout << "Please enter a valid command:"   << std::endl
              << "[?]push to stack   [=]print top" << std::endl
              << "[x]to swap two topmost elements" << std::endl
              << "[s]to sum all elements of the stack, clear it and insert the sum" << std::endl
              << "[a]to clear the stack and insert the average"
              << "[+] [-] [*] [/]   are arithmetic operations" << std::endl
              << "[%] [^] [v] are modulo, exponent and square" << std::endl
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
   double p = 0;
   double q = 0;
   int count = 0;

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

   case '%':
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
            count = q / p;
            q = q - (count * p);
            if (numbers.push(q) == overflow)
               std::cout << "Warning: Stack full, lost result" << std::endl;
         }
      }
      break;

   case '^':
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
            q = pow(p, q);
            if (numbers.push(q) == overflow)
               std::cout << "Warning: Stack full, lost result" << std::endl;
         }
      }
      break;

   case 'v':
      if (numbers.top(p) == underflow)
      {
         std::cout << "Stack empty" << std::endl;
      }
      else
      {
         numbers.pop();
         q = sqrt(p);
         if (numbers.push(q) == overflow)
               std::cout << "Warning: Stack full, lost result" << std::endl;
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

   case 's':
      if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else
      {
         while (!numbers.empty())
         {
            q += p;
            numbers.pop();
            numbers.top(p);
         }

         numbers.push(q);
      }
      break;

   case 'a':
      if (numbers.top(p) == underflow)
         std::cout << "Stack empty" << std::endl;
      else
      {
         while (!numbers.empty())
         {
            count++;
            q += p;
            numbers.pop();
            numbers.top(p);
         }

         numbers.push(q/count);
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