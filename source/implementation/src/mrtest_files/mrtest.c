#include "mrtest.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

_MR_FunctionVectorType* _MR_global_function_vector = NULL;

static int _MR_NumLen(size_t n) {
	int i = 1;
	while (n >= 10) {
		++i;
		n /= 10;
	}
	return i;
}

static void _MR_PrintSign(int num_digits, const char* color) {
	printf("%s", color);
	for (int i = 0; i < num_digits; ++i) {
		printf("=");
	}
	printf(_MR_RESET_COLOR "\n");
}

static void _MR_PrintSuccessMessage(size_t num_testcases) {
	int num_digits = _MR_NumLen(num_testcases);

	printf(_MR_GREEN_BOLD "=========================================");
	_MR_PrintSign(num_digits, _MR_GREEN_BOLD);
	printf(_MR_GREEN_BOLD "=======" _MR_RESET_COLOR
	" Passed [%lu] total TestCases " 
	_MR_GREEN_BOLD "=======" _MR_RESET_COLOR "\n", num_testcases);
	printf(_MR_GREEN_BOLD "=========================================");
	_MR_PrintSign(num_digits, _MR_GREEN_BOLD);
}

static void _MR_PrintFailMessage(size_t num_testcases, size_t num_failed) {
	size_t num_signs = _MR_NumLen(num_testcases) + _MR_NumLen(num_failed);

	printf(_MR_RED_BOLD "===============================================");
	_MR_PrintSign(num_signs, _MR_RED_BOLD);

	printf(_MR_RED_BOLD "=======" _MR_RESET_COLOR
		" Failed [%lu] of [%lu] total TestCases "
		_MR_RED_BOLD "=======" _MR_RESET_COLOR "\n", num_failed, num_testcases);

	printf(_MR_RED_BOLD "===============================================");
	_MR_PrintSign(num_signs, _MR_RED_BOLD);
}

void _MR_PrintEndMessage(size_t num_testcases, size_t num_failed) {
	printf("\n");
	if (num_failed == 0) {
		_MR_PrintSuccessMessage(num_testcases);
	} else {
		_MR_PrintFailMessage(num_testcases, num_failed);
	}
	printf("\n");
}

/* Return true if tag should be executed */
int _MR_ShouldExecuteTag(int argc, char *argv[], char *tag)
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

static const char* _MR_GetSignalName(int signal) {
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

	if (signal > (int)(sizeof(signals) / sizeof(signals[0]))
		|| signals[signal] == NULL) {
		// String literals have static storage duration
		return "???";
	}

	return signals[signal];
}

int _MR_ExecuteTestCase(_MR_FunctionType* it) {
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
			it->name, _MR_GetSignalName(WTERMSIG(status)));
		return -1;
	}

	return 0;
}
