main : quad_area.o quad_perimeter.o main.o compute_angles.o point_functions.o
	gcc quad_area.o quad_perimeter.o main.o compute_angles.o point_functions.o -o main

quad_area.o: quad_area.c
	gcc -c quad_area.c

quad_perimeter.o : quad_perimeter.c
	gcc -c quad_perimeter.c

main.o: main.c
	gcc -c main.c

compute_angles.o : compute_angles.c
	gcc -c compute_angles.c

point_functions.o : point_functions.c
	gcc -c point_functions.c

clean:
	rm point_functions.o
	rm main.o
	rm main
	rm quad_perimeter.o
	rm quad_area.o
	rm compute_angles.o
