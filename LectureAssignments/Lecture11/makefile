CC  = gcc
FFLAGS = -O3 -Wall
OBJECTS = main.o \
					delete_list.o \
					generate_list.o \
					get_key.o \
					get_num_of_nodes.o \
					print.o \
					search_list.o
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
	@echo " delete_list.o"
	@echo " generate_list.o"
	@echo " get_key.o"
	@echo " get_num_of_nodes.o"
	@echo " print.o"
	@echo " search_list.o"
