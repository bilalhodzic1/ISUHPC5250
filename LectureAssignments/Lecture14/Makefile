CC  = gcc
FFLAGS = -O3 -Wall
OBJECTS = main.o \
					matrix.o \
					power_iteration.o \
					inverse_power_iteration.o \
					rayleigh_quotient_iteration.o \
					fill_random_vector.o \
					normalize_vector.o \
					transpose_vector.o
LFLAGS = 

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
	@echo " power_iteration.o"
	@echo " inverse_power_iteration.o"
	@echo " rayleigh_quotient_iteration.o"
	@echo " fill_random_vector.o"
	@echo " normalize_vector.o"
	@echo " transpose_vector.o"
