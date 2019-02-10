#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>

#define log_info(...)  do { printf("info : " __VA_ARGS__); putchar('\n'); } while(0);
#define log_error(...) do { printf("error: " __VA_ARGS__); putchar('\n'); } while(0);

int main(void)
{
        long orax;
        pid_t pid;

        pid = fork();
        if (pid < 0) {
                log_error("fork failed, %s.", strerror(errno));
                exit(EXIT_FAILURE); /* 1 */
        } else if (pid == 0){
                ptrace(PTRACE_TRACEME, 0, NULL, NULL);
                execlp("/usr/bin/ls", "ls", NULL);
                exit(EXIT_SUCCESS);
        }

        log_info("current pid %d, child pid %d.", getpid(), pid);
        wait(NULL);
        orax = ptrace(PTRACE_PEEKUSER, pid, 8 * ORIG_RAX, NULL);
        log_info("child execve() returned with %ld, expect %d.\n", orax, SYS_execve);
        ptrace(PTRACE_CONT, pid, NULL, NULL);

        return 0;
}
