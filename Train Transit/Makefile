.PHONY: clean

transit: numbers.o map.o transit.o
	gcc numbers.o map.o transit.o -o transit

transit.o: transit.c numbers.h map.h
	gcc -Wall -std=c99 -g -c transit.c

numbers.o: numbers.c numbers.h
	gcc -Wall -std=c99 -g -c numbers.c
	
map.o: map.c map.h numbers.h
	gcc -Wall -std=c99 -g -c map.c

clean:
	rm -f *.o transit
