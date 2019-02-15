jc: jc.c token.o stack.o
	clang -g -o jc jc.c token.c stack.c -Wall
token.o: token.h token.c
	clang -c token.c
stack.o: stack.h stack.c
	clang -c stack.c
clean:
	rm jc *.o