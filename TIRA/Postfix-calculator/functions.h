#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "stack.h"
#include <iostream>
#include <cctype>
#include <cmath>

char get_command();
bool do_command(char command, Stack &numbers);
void introduction();
void instructions();

#endif