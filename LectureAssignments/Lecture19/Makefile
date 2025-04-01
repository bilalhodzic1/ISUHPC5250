CC  = gcc
FFLAGS = -Wall -std=c99 -fopenmp
OBJECTS = main.o \
					fill_random_vector.o \
					matrix.o

LFLAGS = -lgomp -lm

.PHONY : clean help


main.exe : $(OBJECTS)
	$(CC) $(LFLAGS) $(OBJECTS) -o main.exe 

%.o : %.c
	$(CC) $(FFLAGS) -c $<

clean:
	rm -f $(OBJECTS) main.exe

help:
	@echo " Valid targets :"
	@echo " main.exe"
	@echo " fill_random_vector.o"
	@echo " matrix.o"
