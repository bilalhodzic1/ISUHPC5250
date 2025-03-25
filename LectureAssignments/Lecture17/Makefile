CC  = gcc
FFLAGS = -O3 -Wall -std=c99 -fopenmp
OBJECTS = main.o \
					matrix.o \
					make_output_vector.o \
					fill_random_vector.o
LFLAGS = -lgomp

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
	@echo " matrix.o"
	@echo " make_output_vector.o"
	@echo " fill_random_vector.o"
