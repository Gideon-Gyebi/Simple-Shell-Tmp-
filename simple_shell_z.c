#include "shell.h"

/**
 * main - Interactive shell doing the folllowing
 * print prompt, get command and execute.
 * Return: 1 if interactive mode, 0 otherwise
 */

int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char *args[MAX_COMMAND_LENGTH];
	char *token;
	int status;
	int i = 0;
	pid_t pid = fork();

	while (1)
	{
		printf("$ ");
		fflush(stdout);
		/* Read command from user input */
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			break;
		}

		/* Parse command into arguments */
		token = strtok(command, " \n");
		while (token != NULL)
		{
			args[i++] = token;

			token = strtok(NULL, " \n");
		}
		args[i] = NULL;

		/* Execute command */		
		if (pid == -1)
		{
			perror("fork");

			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			/* Child process */
			execvp(args[0], args);
			perror("execvp");
			_exit(EXIT_FAILURE);
		} else
		{
			/* Parent process */
			waitpid(pid, &status, 0);
		}
	}
	return (0);
}
