CC  = gcc
FFLAGS = -O3 -Wall
OBJECTS = main.o \
					delete_stack.o \
					display_options.o \
					display_stack.o \
					get_stack_size.o \
					option.o \
					peek.o \
					pop.o \
					push.o 
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
	@echo " delete_stack.o" 
	@echo	" display_options.o" 
	@echo	" display_stack.o" 
	@echo	" get_stack_size.o" 
	@echo	" option.o" 
	@echo	" peek.o" 
	@echo	" pop.o" 
	@echo	" push.o" 
