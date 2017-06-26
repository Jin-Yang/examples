CFLAGS =-g -Wall
LDFLAGS =
PROCS = const_pointer

all: ${PROCS}

#misc: misc.o

%: %.o
	gcc ${LDFLAGS} -o $@ $<
%.o: %.c
	gcc ${CFLAGS} -o $@ $< -c
clean:
	rm -rf ${PROCS} ${TRACE} *.o
