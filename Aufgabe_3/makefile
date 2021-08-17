A3: A3.o our_numerics.o
	gcc -Wall -Ofast -flto  A3.o our_numerics.o -lm -o A3
	
	
A3.o: A3.c ../our_numerics.h
	gcc -Wall -Ofast -flto  -I.. -c A3.c

our_numerics.o: ../our_numerics.h ../our_numerics.c
	gcc -Wall -Ofast -flto -c ../our_numerics.c 
