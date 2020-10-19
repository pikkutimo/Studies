#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include "utilities.h"
#include "queue.h"

char get_command();
bool do_command(char command, Extended_queue &numbers);
void introduction();
void help();
void print_queue(Extended_queue);

#endif