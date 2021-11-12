#include "mrtest.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

_MR_FunctionVectorType* _MR_global_function_vector = NULL;

static int numLen(size_t n) {
	int i = 1;
	while (n >= 10) {
		++i;
		n /= 10;
	}
	return i;
}

static void printSign(int num_digits) {
	printf(_MR_GREEN_BOLD);
	for (int i = 0; i < num_digits; ++i) {
		printf("=");
	}
	printf(_MR_RESET_COLOR "\n");
}

void printSuccessMessage(size_t num_testcases) {
	int num_digits = numLen(num_testcases);

	printf("\n");
	printf(_MR_GREEN_BOLD "===========================================");
	printSign(num_digits);
	printf(_MR_GREEN_BOLD "=======" _MR_RESET_COLOR
	" Ran [%lu] successful testcases " 
	_MR_GREEN_BOLD "=======" _MR_RESET_COLOR "\n", num_testcases);
	printf(_MR_GREEN_BOLD "===========================================" );
	printSign(num_digits);
	printf("\n");
}

/* Return true if tag should be executed */
int _MR_shouldExecuteTag(int argc, char *argv[], char *tag)
{
	if (argc == 0) {
		return 1;
	}

	for (int i = 0; i < argc; ++i) {
		if (strcmp(tag, argv[i]) == 0) {
			return 1;
		}
	}

	return 0;
}

static const char* _MR_SIGNAL_NAME(int signal) {
	static const char* signals[] = {
		[SIGABRT] = "SIGABRT",
		[SIGALRM] = "SIGALRM",
		[SIGBUS] = "SIGBUS",
		[SIGCHLD] = "SIGCHLD",
		[SIGCONT] = "SIGCONT",
		[SIGFPE] = "SIGFPE",
		[SIGHUP] = "SIGHUP",
		[SIGILL] = "SIGILL",
		[SIGINT] = "SIGINT",
		[SIGIO] = "SIGIO",
		[SIGKILL] = "SIGKILL",
		[SIGPIPE] = "SIGPIPE",
		[SIGPROF] = "SIGPROF",
		[SIGQUIT] = "SIGQUIT",
		[SIGSEGV] = "SIGSEGV",
		[SIGSTOP] = "SIGSTOP",
		[SIGTSTP] = "SIGTSTP",
		[SIGSYS] = "SIGSYS",
		[SIGTERM] = "SIGTERM",
		[SIGTRAP] = "SIGTRAP",
		[SIGTTIN] = "SIGTTIN",
		[SIGTTOU] = "SIGTTOU",
		[SIGURG] = "SIGURG",
		[SIGUSR1] = "SIGUSR1",
		[SIGUSR2] = "SIGUSR2",
		[SIGVTALRM] = "SIGVTALRM",
		[SIGXCPU] = "SIGXCPU",
		[SIGXFSZ] = "SIGXFSZ",
		[SIGWINCH] = "SIGWINCH"
	};

	return signals[signal];
}

int _MR_executeTestCase(_MR_FunctionType* it) {
	pid_t pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		it->function();
		exit(EXIT_SUCCESS);
	}

	int status;
	if (waitpid(pid, &status, 0) == -1) {
		perror("waitpid");
		exit(EXIT_FAILURE);
	}

	// Check exit status
	if (WIFEXITED(status)) {
		if (WEXITSTATUS(status) != 0) {
			return -1;
		}
	} else if (WIFSIGNALED(status)) {
		fprintf(stderr, "%s: CRASH: [" _MR_RED_BOLD "%s" _MR_RESET_COLOR "]\r\n",
			it->name, _MR_SIGNAL_NAME(WTERMSIG(status)));
		return -1;
	}

	return 0;
}
