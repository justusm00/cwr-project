all:
	+$(MAKE) -C Aufgabe_2
	+$(MAKE) -C Aufgabe_3
	
	
run:
	$(MAKE) -C Aufgabe_2 run
	$(MAKE) -C Aufgabe_3 run	

clean:
	$(MAKE) -C Aufgabe_2 clean
	$(MAKE) -C Aufgabe_3 clean
