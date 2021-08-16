AUFGABE3: Aufgabe3.o our_numerics.o
	gcc -Wall -Ofast -flto  Aufgabe3.o our_numerics.o -lm -o AUFGABE3
	
	
Aufgabe3.o: Aufgabe3.c ../our_numerics.h
	gcc -Wall -Ofast -flto  -I.. -c Aufgabe3.c

our_numerics.o: ../our_numerics.h ../our_numerics.c
	gcc -Wall -Ofast -flto -c ../our_numerics.c 
