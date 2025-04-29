CC  = gcc
FFLAGS = -O3 -Wall
OBJECTS = main.o \
		  split_string.o \
		  read_games.o

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
	@echo " split_strings.o"
	@echo " read_games.o"
