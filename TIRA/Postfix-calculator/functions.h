#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "stack.h"
#include <iostream>
#include <cctype>
#include <cmath>
#include <cstring>
#include <string>

char get_command();
bool do_command(char command, Stack &numbers);
void do_desk_calculator(Stack &numbers);
void introduction();
void instructions();
void count_average(Stack &numbers);
void count_sum(Stack &numbers);
void sum(Stack &numbers);
void minus(Stack &numbers);
void multiply(Stack &numbers);
void divide(Stack &numbers);
void modulo(Stack &numbers);
void exponentation(Stack &numbers);
void square(Stack &numbers);
void exhange(Stack &numbers);

#endif