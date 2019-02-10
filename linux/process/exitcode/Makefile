all:
	gcc -o example example.c
	gcc -o exitcode exitcode.c
	gcc -o signalex signal.c
	gcc -o traceit traceit.c
	gcc -o coredump coredump.c -Wno-div-by-zero

clean:
	rm -f example exitcode signalex traceit coredump
