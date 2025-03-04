CC  = gcc
FFLAGS = -O3 -Wall
OBJECTS = main.o \
					matrix.o \
					least_squares.o \
					generate_points.o
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
	@echo " least_squares.o"
	@echo " generate_points.o"
