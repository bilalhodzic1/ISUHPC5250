CC  = gcc
FFLAGS = -Wall -std=c99 -fopenmp
OBJECTS = main.o \
					fill_random_vector.o \
					matrix.o \
					two_normalize_vector_fine.o \
					two_normalize_vector_coarse.o \
					max_normalize_vector_fine.o \
					max_normalize_vector_coarse.o

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
	@echo " max_normalize_vector_fine.o"
	@echo " max_normalize_vector_coarse.o"
	@echo " two_normalize_vector_fine.o"
	@echo " two_normalize_vector_coarse.o"
