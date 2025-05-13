CC  = mpicc
FFLAGS = -O3 -Wall -std=c99
OBJECTS = main.o \
		  split_string.o \
		  read_games.o \
		  compute_season_aggregates.o \
		  hashmap.o \
		  compute_player_pers.o \
		  mpi_objects.o \
		  mpi_functions.o \
		  compute_local_player_agg_array.o \
		  compute_player_upers_array.o \
		  get_unadjusted_per.o \
		  adjust_uper_array.o \
		  join_player_aggs_to_map.c

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
	@echo " compute_season_aggregates.o"
	@echo " hashmap.o"
	@echo " compute_player_pers.o"
	@echo " mpi_objects.o"
	@echo " mpi_functions.o"
	@echo " compute_local_player_agg_array.o"
	@echo " compute_player_upers_array.o"
	@echo " get_unadjusted_per.o"
	@echo " adjust_uper_array.o"
	@echo " join_player_aggs_to_map.o"
