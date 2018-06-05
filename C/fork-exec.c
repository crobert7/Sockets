#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn (char* program, char** arg_list)
{
	pid_t child_pid;
	child_pid = fork ();
	if (child_pid != 0) /* This is the parent process. */
		return child_pid;
	else {
		/* Now execute PROGRAM, searching for it in the path. */
		execvp (program, arg_list);
		/* The execvp function returns only if an error occurs. */
		fprintf (stderr, "an error occurred in execvp\n");
		abort ();
	}
}

int main ()
{
	/* The argument list to pass to the "ls" command. */
	char* arg_list[] = {
		"ls", /* argv[0], the name of the program. */
		"-l",
		"/",
		NULL /* The argument list must end with a NULL. */
	};
	/* Spawn a child process running the "ls" command. Ignore the
	returned child process ID. */
	spawn ("ls", arg_list);
	printf ("done with main program\n");
	return 0;
}

