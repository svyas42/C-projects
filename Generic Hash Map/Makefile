CFLAGS += -Wall -std=c99 -g
LDLIBS +=

.PHONY: all clean
all: driver

driver: map.o value.o input.o driver.o

driver.o: driver.c map.h value.h input.h
map.o: map.c map.h
value.o: value.c value.h
input.o: input.c input.h

clean:
	rm -f *.o driver *.gcda *.gcno *.gcov
