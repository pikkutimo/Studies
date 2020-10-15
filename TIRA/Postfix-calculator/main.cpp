#include "stack.h"
#include "functions.h"
#include "utilities.h"

int main(int argc, char* argv[])
/*
Post: The program has executed simple arithmetic
      commands entered by the user.
Uses: The class Stack and the functions
      introduction, instructions, do_command, and get_command.
*/
{
      Stack stored_numbers;
      bool prompt{false};

      introduction();
      if (argc > 1 && strcmp(argv[1], "-p") == 0)
      {
           prompt = true;
           instructions(prompt);
           do_desk_calculator(stored_numbers);
      }
      else
      {
            instructions(prompt);
            while (do_command(get_command(), stored_numbers));
      }
            
}
