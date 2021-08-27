all:
	+$(MAKE) -C Aufgabe_2
	+$(MAKE) -C Aufgabe_3
	
run:
	cd Aufgabe_2 && ./A2 && python3 plotA2.py
	cd Aufgabe_3 && ./A3 && python3 plotA3.py
	

clean:
	cd Aufgabe_2 && echo "Cleaning up ..." && rm -rvf *.o && rm -rvf *.exe && rm -rvf *.txt && rm -rvf *.o 
	cd Aufgabe_3 && rm -rvf *.o  && rm -rvf *.exe  && rm -rvf *.dat
	
	

