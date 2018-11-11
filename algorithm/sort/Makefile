CFLAGS =-g -Wall
LDFLAGS =
PROCS = heap

all: ${PROCS}

%: %.o
	gcc ${LDFLAGS} -o $@ $<
%.o: %.c
	gcc ${CFLAGS} -o $@ $< -c
clean:
	rm -rf ${PROCS} ${TRACE} *.o
