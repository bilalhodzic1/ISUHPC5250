#!/bin/bash

# Check if a directory argument is provided
if [ -z "$1" ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Assign directory argument to a variable
dir="$1"

# Check if the directory exists, create it if necessary
if [ ! -d "$dir" ]; then
    mkdir -p "$dir"
fi

# Define Makefile path
makefile_path="$dir/Makefile"

# Generate the Makefile
echo "Generating Makefile in $makefile_path"

cat > "$makefile_path" <<'EOL'
CC  = gcc
FFLAGS = -Wall -std=c99 -fopenmp
OBJECTS = main.o \
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
EOL

# Confirm completion
echo "Makefile created successfully."
