CFLAGS =  -Wall -D_GNU_SOURCE
LDFLAGS =	-pthread

PROCS = atomics.c

all: ${PROCS}

%.o: %.c
	gcc ${CFLAGS} -o $@ $< -c

clean:
	rm -rf ${PROCS} *.o
