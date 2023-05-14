ndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// This function displays the prompt and gets the user's input.
void prompt_and_get_input(void);

// This function parses the user's input and executes the command.
void parse_and_execute_command(void);

// This is the main loop of the program. It calls the `prompt_and_get_input()` and `parse_and_execute_command()` functions repeatedly until the user types "exit".
int main(void);

// This function parses the user's input and returns an array of strings containing the arguments.
char** parse_arguments(char* line);

#endif // SHELL_H