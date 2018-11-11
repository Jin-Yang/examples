#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define err_sys(fmt, arg...) \
do { \
printf(fmt, ##arg);\
printf("\nerrno:%d %s\n", errno, strerror(errno));\
exit(EXIT_FAILURE);\
} while (0)


int main()
{
int fd, fd2, val;
pid_t pid;

#ifdef _O_CLOEXEC
	fd = open("foobar.txt", O_RDWR | O_CREAT | O_CLOEXEC, 0600);
#else
	fd = open("foobar.txt", O_RDWR | O_CREAT, 0600);
#endif


#ifdef _DUP
if ((fd2 = dup(fd)) < 0)
err_sys("dup error");
if (write(fd2, "123", 3) < 0)
err_sys("write error");
#endif

#ifdef _FCNTL_CLOEXEC
if ((val = fcntl(fd, F_GETFD)) < 0)
err_sys("fcntl(F_GETFD) error");

val |= FD_CLOEXEC;
if (fcntl(fd, F_SETFD, val) < 0)
err_sys("fcntl( F_SETFD) error");
#endif

#ifndef _FORK
if (execl("/bin/sleep", "sleep", "10000", (void*)0) < 0)
err_sys("execl error");
#else
	switch ((pid = fork())) {
		case -1:
err_sys("fork error");
case 0:
sleep(10000);
break;
default:
sleep(10000);
break;
}
#endif

return 0;
}
