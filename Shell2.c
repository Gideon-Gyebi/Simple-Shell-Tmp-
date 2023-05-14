
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Betty style
// 1. All function prototypes should be declared before they are used.
// 2. All variables should be declared as close to their use as possible.
// 3. All code should be indented using four spaces.
// 4. There should be no trailing whitespace at the end of lines.
// 5. All lines should be limited to a maximum of 80 characters.

// gcc -Wall -Werror -Wextra -pedantic -std=gnu89
// 1. -Wall: Enable all warnings.
// 2. -Werror: Treat all warnings as errors.
// 3. -Wextra: Enable extra warnings.
// 4. -pedantic: Enable all the mandatory diagnostics listed in the C standard.
// 5. -std=gnu89: Use the GNU C standard.

void prompt_and_get_input(void) {
  // Display the prompt.
  write(1, ">>> ", 4);

  // Get the user's input.
  char *line = NULL;
  size_t size = 0;
  if (getline(&line, &size, stdin) == -1) {
    if (feof(stdin)) {
      exit(0);
    } else {
      perror("getline");
      exit(1);
    }
  }
}

// This function parses the user's input and executes the command.
void parse_and_execute_command(void) {
  // Parse the user's input.
  char *command = strtok(line, " ");
  if (command == NULL) {
    return;
  }

  // If the user typed "exit", exit the program.
  if (strcmp(command, "exit") == 0) {
    exit(0);
  }

  // If the user typed a command that is not in the PATH, print an error message.
  if (command[0] != '/') {
    printf("./shell: No such file or directory\n");
    return;
  }

  // Fork a child process.
  pid_t pid = fork();
  if (pid == 0) {
    // In the child process, execute the command.
    char** arguments = parse_arguments(line);
    execvp(arguments[0], arguments);
    perror(command);
    exit(1);
  } else if (pid < 0) {
    // In the parent process, print an error message and exit.
    perror("fork");
    exit(1);
  }

  // In the parent process, wait for the child process to exit.
  wait(&status);
}

// This is the main loop of the program. It calls the `prompt_and_get_input()` and `parse_and_execute_command()` functions repeatedly until the user types "exit".
int main(void) {
  while (1) {
    // Prompt the user for input and parse it.
    prompt_and_get_input();
    parse_and_execute_command();
  }

  return 0;
}

// This function parses the user's input and returns an array of strings containing the arguments.
char** parse_arguments(char* line) {
  // Create an array to store the arguments.
  char** arguments = malloc(sizeof(char*) * 10);
  int argument_count = 0;

  // Parse the line into arguments.
  char* token = strtok(line, " ");
  while (token != NULL) {
    arguments[argument_count] = token;
    argument_count++;
    token = strtok(NULL, " ");
  }

  // Return the array of arguments.
  return arguments;
}