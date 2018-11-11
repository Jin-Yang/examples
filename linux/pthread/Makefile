CFLAGS  = -Wall -D_GNU_SOURCE -O2
LDFLAGS = -pthread

PROCS = atomics

all: ${PROCS}

%.o: %.c
	gcc ${CFLAGS} -o $@ $< -c

clean:
	rm -rf ${PROCS} *.o
