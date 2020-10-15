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
Post: Prints out short introduction to the ideas behind Polish reverse notation. 
*/
{
   std::cout << "Reverse Polish notation (RPN), also known as Polish postfix notation or" << std::endl
            << "postfix notation, is a mathematical notation in which operators follow their operands," << std::endl
            << "in contrast to Polish notation (PN), in which operators precede their operands." << std::endl
            << "does not need any parentheses as long as each operator has a fixed number of operands.\n" << std::endl;
}

void instructions(bool &prompt)
/*
Pre:  
Post: Prints out the instructions fo the usage of the calculator.
*/
{
   std::cout << "Please enter a valid command:"   << std::endl;
   if (prompt == false)
      std::cout << "[?]push to stack   [=]print top" << std::endl;
   else
      std::cout << "The result or the top most element will be shown after you press [ENTER]" << std::endl;
   std::cout << "[x]to swap two topmost elements" << std::endl
      << "[s]to sum all elements of the stack, clear it and insert the sum" << std::endl
      << "[a]to clear the stack and insert the average" << std::endl
      << "[+] [-] [*] [/]   are arithmetic operations" << std::endl
      << "[%] [^] [v] are modulo, exponent and square" << std::endl
      << "[Q]uit." << std::endl;
}

void do_desk_calculator(Stack &numbers)
/*
Pre:  
Post: Reverse polish calculator with string input.
*/
{
   std::string lineInput{""};
   std::string inputNumber{""};
   char prevCharacter;
   bool isOn{true};
   double topOfStack{0};
   double temp{0};

   std::cout << "\nEnter the calculation:" << std::endl;

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
            numbers.push(temp);
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

      if (isOn)
      {
         numbers.top(topOfStack);
         std::cout << topOfStack << std::endl;
      }
      
   }
}

void count_average(Stack &numbers)
/*
Pre:  
Post: Calculates the average of every value in the stack and replaces all of them with value.
*/
{
   double last{0};
   double sum{0};
   int count{0};
   
   if (!check_underflow(numbers, last))
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
Post: Calculates the sum of the two top most values in the stack and replaces them with the sum.
*/
{
   double final{0};
   double penultimate{0};

   if (!check_underflow(numbers, final))
   {
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
Post: Calculates the difference between the two top most values in the stack and replaces them with the 
      difference.
*/
{
   double final{0};
   double penultimate{0};

   if (!check_underflow(numbers, final)) 
   {
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
Post: Multiplies the two top most values in the stack and replaces them with the product. 
*/
{
   double final{0};
   double penultimate{0};

   if (!check_underflow(numbers, final))
   {
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
Post: Calculates the difference between the two top most values in the stack and replaces them 
      with the difference.
*/
{
   double final{0};
   double penultimate{0};
   double remainder{0};

   if (!check_underflow(numbers, final))
   {
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
Post: Calculatest the modulo of the two top most values in the stack and replaces them with
      the modulo.
*/
{
   double final{0};
   double penultimate{0};
   int size{0};

   if (!check_underflow(numbers, final))
   {
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
Post: Calculates the exponent of the two top most values in the stack. The last value in the stack is
      the index and the penultimate value is the base. These are replaced with the result.
*/
{
   double final{0};
   double penultimate{0};

   if (!check_underflow(numbers, final))
   {
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
Post: Calculates the squareroot of the top most value in the stack and replaces it with the result. 
*/
{
   double topmost{0};

   if (!check_underflow(numbers, topmost))
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
Post: Exhanges the two top most values in the stack with each other. 
*/
{
   double final{0};
   double penultimate{0};

   if (!check_underflow(numbers, final))
   {
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
Post: Calculates the sum of all the values in the stack and replaces them with the sum.
*/
{
   double sum{0};
   double final{0};

   if (!check_underflow(numbers, final))
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
Post: Checks whether the stack is empty or not.
*/
{
   if (numbers.top(final) == underflow)
   {
      std::cout << "Stack empty" << std::endl;
      return true;
   }

   return false;      
}