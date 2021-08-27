BINARY := A3
OBJECTS = A3.o ../our_numerics.o
HEADER = our_numerics.h

CC     := gcc
CFLAGS := -flto -Ofast -Wall -std=c11
LFLAGS := -lm 





$(BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(LFLAGS) -o $(BINARY)

run: ${BINARY}
	./$<
	python3 plotA3.py

clean:
	@echo "Cleaning up ..."
	@rm -rvf *.o ${BINARY}
	@rm -rvf *.exe ${BINARY}
	@rm -rvf *.csv ${BINARY}
	@rm -rvf *.txt ${BINARY}
	@rm -rvf *.dat ${BINARY}
	
	

