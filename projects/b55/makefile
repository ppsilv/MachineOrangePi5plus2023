b55 : b55.o utils.o
	gcc -o b55 b55.o utils.o

all: clean b55


main.o : b55.c b55.h utils.c utils.h
	gcc -c b55.c

util.o : utils.c utils.h
	gcc -c utils.c

clean :
	rm b55 b55.o

wclean :
	del b55 b55.o
