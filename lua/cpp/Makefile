EXEC=basic

all: ${EXEC}

basic: basic.cpp
	g++ -o $@ $< -llua -Wall

clean:
	@rm -f ${EXEC}
