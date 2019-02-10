#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#define log_info(...)  do { printf("info : " __VA_ARGS__); putchar('\n'); } while(0);
#define log_error(...) do { printf("error: " __VA_ARGS__); putchar('\n'); } while(0);

#define REPO_PATH "/tmp/examples/linux/process/exitcode"

int main(void)
{
        int status;
        pid_t pid;
        //char *argv[] = {(char *)"/bin/bash", (char *)"-c", (char *)"exit 1", NULL};
        //char *argv[] = {(char *)REPO_PATH "/exitcode", (char *)"1", NULL};
        //char *argv[] = {(char *)REPO_PATH "/coredump", NULL};
        char *argv[] = {(char *)"/usr/bin/sleep", (char *)"10000", NULL};
        //char *argv[] = {(char *)REPO_PATH "/signalex", NULL};

        pid = fork();
        if (pid < 0) {
                log_error("fork failed, %s.", strerror(errno));
                exit(EXIT_FAILURE); /* 1 */
        } else if (pid == 0) { /* child */
                ptrace(PTRACE_TRACEME, 0, NULL, NULL);
                if (execvp(argv[0], argv) < 0) {
                        log_error("execl failed, %s.", strerror(errno));
                        return 0;
                }
        }

        if (waitpid(pid, &status, WUNTRACED) < 0) {
                log_error("waitpid error, %s.", strerror(errno));
                return 0;
        }
        log_info("process #%d exit with %d.", pid, status);
        if (WIFEXITED(status)) {
                log_info("normal termination, exit status = %d.", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
                log_info("abnormal termination, signal number = %d%s.",
                        WTERMSIG(status), WCOREDUMP(status) ? " (core file generated)" : "");
        } else if (WIFSTOPPED(status)) {
                log_info("child stopped, signal number = %d.", WSTOPSIG(status));
        }

        exit(0);
}
