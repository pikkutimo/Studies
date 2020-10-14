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
      sum(numbers);
      break;

   case '-':
      minus(numbers);
      break;
   
   case '*':
      multiply(numbers);
      break;

   case '/':
      divide(numbers);
      break;

   case '%':
      modulo(numbers);
      break;

   case '^':
      exponentation(numbers);
      break;

   case 'v':
      square(numbers);
      break;

   case 'x':
      exhange(numbers);
      break;

   case 's':
      count_sum(numbers);
      break;

   case 'a':
      count_average(numbers);
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

void do_desk_calculator(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   std::string lineInput{""};
   std::string inputNumber{""};
   char prevCharacter;
   bool isOn{true};
   double topOfStack{0};
   double temp{0};

   while (isOn)
   {
      std::getline(std::cin, lineInput);
      lineInput += " ";
      
      for (char ch: lineInput)
      {
         char command = tolower(ch);
         if (isdigit(command))
         {
            inputNumber += command;
            prevCharacter = command;
         }
         else if(command =='.' || command == ',' && isdigit(prevCharacter))
            inputNumber += command;
         else if (command == ' ' && isdigit(prevCharacter))
         {
            temp = std::stod(inputNumber);
            // std::cout << temp << " ";
            numbers.push(temp);
            // numbers.top(topOfStack);
            // std::cout << topOfStack << std::endl;
            inputNumber.clear();
            prevCharacter = ' ';
         }
         else if (command == 'a' || command == '+' || command == 'q' ||
            command == '-' || command == '*' || command == '/' ||
            command == '%' || command == '^' || command == 'v' ||
            command == 'x' || command == 's')
         {
            switch(command)
            {
               case 'a':
                  count_average(numbers);
                  break;
               case '+':
                  sum(numbers);
                  break;
               case 'q':
                  isOn = false;
                  break;
               case '-':
                  minus(numbers);
                  break;
               case '*':
                  multiply(numbers);
                  break;
               case '/':
                  divide(numbers);
                  break;
               case '%':
                  modulo(numbers);
                  break;
               case '^':
                  exponentation(numbers);
                  break;
               case 'v':
                  square(numbers);
                  break;
               case 'x':
                  exhange(numbers);
                  break;
               case 's':
                  count_sum(numbers);
                  break;
            }
         }
         else
            continue;
      }

      numbers.top(topOfStack);
      std::cout << topOfStack << std::endl;
   }
}

void count_average(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double last{0};
   double sum{0};
   int count{0};
   
   if (numbers.top(last) == underflow)
      std::cout << "Stack empty" << std::endl;
   else
   {
      while (!numbers.empty())
      {
         count++;
         sum += last;
         numbers.pop();
         numbers.top(last);
      }
      numbers.push(sum/count);
   }
}

void sum(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double final{0};
   double penultimate{0};

   if (numbers.top(final) == underflow)
         std::cout << "Stack empty" << std::endl;
   else {
      numbers.pop();
      if (numbers.top(penultimate) == underflow) {
         std::cout << "Stack has just one entry" << std::endl;
         numbers.push(final);
      }
      else {
         numbers.pop();
         if (numbers.push(final + penultimate) == overflow)
            std::cout << "Warning: Stack full, lost result" << std::endl;
      }
   }
}

void minus(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double final{0};
   double penultimate{0};

   if (numbers.top(final) == underflow)
         std::cout << "Stack empty" << std::endl;
   else {
      numbers.pop();
      if (numbers.top(penultimate) == underflow) {
         std::cout << "Stack has just one entry" << std::endl;
         numbers.push(final);
      }
      else 
      {
         numbers.pop();
         if (numbers.push(penultimate - final) == overflow)
            std::cout << "Warning: Stack full, lost result" << std::endl;
      }
   }
}

void multiply(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double final{0};
   double penultimate{0};

   if (numbers.top(final) == underflow)
         std::cout << "Stack empty" << std::endl;
   else {
      numbers.pop();
      if (numbers.top(penultimate) == underflow) {
         std::cout << "Stack has just one entry" << std::endl;
         numbers.push(final);
      }

      else {
         numbers.pop();
         if (numbers.push(final * penultimate) == overflow)
            std::cout << "Warning: Stack full, lost result" << std::endl;
      }
   }
}

void divide(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double final{0};
   double penultimate{0};
   double remainder{0};

   if (numbers.top(final) == underflow)
      std::cout << "Stack empty" << std::endl;
   else {
      numbers.pop();
      if (numbers.top(penultimate) == underflow) {
         std::cout << "Stack has just one entry" << std::endl;
         numbers.push(final);
      }

      else {
         numbers.pop();
         remainder = penultimate/final;
         if (numbers.push(remainder) == overflow)
            std::cout << "Warning: Stack full, lost result" << std::endl;
      }
   }
}

void modulo(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double final{0};
   double penultimate{0};
   int size{0};

   if (numbers.top(final) == underflow)
         std::cout << "Stack empty" << std::endl;
   else {
      numbers.pop();
      if (numbers.top(penultimate) == underflow) 
      {
         std::cout << "Stack has just one entry" << std::endl;
         numbers.push(final);
      }
      else 
      {
         numbers.pop();
         size = penultimate / final;
         penultimate = penultimate - (size * final);
         if (numbers.push(penultimate) == overflow)
            std::cout << "Warning: Stack full, lost result" << std::endl;
      }
   }
}

void exponentation(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double final{0};
   double penultimate{0};

   if (numbers.top(final) == underflow)
         std::cout << "Stack empty" << std::endl;
   else {
      numbers.pop();
      if (numbers.top(penultimate) == underflow) {
         std::cout << "Stack has just one entry" << std::endl;
         numbers.push(final);
      }
      else
      {
         numbers.pop();
         penultimate = pow(penultimate, final);
         if (numbers.push(penultimate) == overflow)
            std::cout << "Warning: Stack full, lost result" << std::endl;
      }
   }
}

void square(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double topmost{0};

   if (numbers.top(topmost) == underflow)
   {
      std::cout << "Stack empty" << std::endl;
   }
   else
   {
      numbers.pop();
      topmost = sqrt(topmost);
      if (numbers.push(topmost) == overflow)
            std::cout << "Warning: Stack full, lost result" << std::endl;
   }
}

void exhange(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double final{0};
   double penultimate{0};

   if (numbers.top(final) == underflow)
         std::cout << "Stack empty" << std::endl;
   else {
      numbers.pop();
      if (numbers.top(penultimate) == underflow) {
         std::cout << "Stack has just one entry" << std::endl;
         numbers.push(final);
      }
      else
      {
         numbers.pop();
         numbers.push(final);
         numbers.push(penultimate);
      }
   }
}

void count_sum(Stack &numbers)
/*
Pre:  
Post: 
Uses: 
*/
{
   double sum{0};
   double final{0};

   if (!check_underflow(numbers, final))
   // if (numbers.top(final) == underflow)
   //       std::cout << "Stack empty" << std::endl;
   {
      while (!numbers.empty())
      {
         sum += final;
         numbers.pop();
         numbers.top(final);
      }

      numbers.push(sum);
   }
}

bool check_underflow(Stack &numbers, double &final)
/*
Pre:  
Post: 
Uses: 
*/
{
   if (numbers.top(final) == underflow)
   {
      std::cout << "Stack empty" << std::endl;
      return true;
   }

   return false;      
}