#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "stack.h"
#include <iostream>
#include <cctype>

char get_command();
bool do_command(char command, Stack &numbers);
void introduction();
void instructions();

#endif