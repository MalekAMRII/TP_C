CFLAGS = -g -Wall -Wextra -pedantic
CC = gcc

PROGRAMS = tests_ecosys ecosys

.PHONY:	all clean

.SUFFIX: 

all: $(PROGRAMS)

ecosys.o: ecosys.c ecosys.h
	$(CC) -c $(CFLAGS) ecosys.o ecosys.c

main_ecosys.o: main_ecosys.c ecosys.h
	$(CC) -c $(CFLAGS) main_ecosys.o main_ecosys.c

main_tests.o: main_tests.c ecosys.h 
	$(CC) -c $(CFLAGS) main_tests.o main_tests.c

tests_ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^

ecosys: ecosys.o main_tests.o
	$(CC) -o $@ $(CFLAGS) $^


#Ou plus simplement
#%.o:%.c %.h
#	$(CC)  $(GCC_FLAGS) -c  $<


clean:
	rm -f *.o *~ $(PROGRAMS)
