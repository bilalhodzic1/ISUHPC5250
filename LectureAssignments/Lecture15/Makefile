CC  = gcc
FFLAGS = -O3 -Wall
OBJECTS = main.o \
					FindZero.o \
					GetShift.o \
					Hessenberg.o \
					matrix.o \
					QRA.o \
					QRdecomp.o \
					trimatrix.o 
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
	@echo " FindZero.o"
	@echo " GetShift.o"
	@echo " Hessenberg.o"
	@echo " matrix.o"
	@echo " QRA.o"
	@echo " QRdecomp.o"
	@echo " trimatrix.o"
