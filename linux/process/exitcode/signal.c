#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigroutine(int signo)
{
        fprintf(stdout, "got signal %d.\n", signo);
        exit(1);
}

int main(void)
{
        signal(SIGTERM, sigroutine);
        while (1)
                sleep(10);
        return 0;
}
