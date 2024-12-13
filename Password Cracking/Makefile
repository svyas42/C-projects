.PHONY: clean

crack: md5.o password.o crack.o block.o magic.o
	gcc md5.o password.o crack.o block.o magic.o -o crack

unitTest: md5.o password.o block.o unitTest.o magic.o
	gcc md5.o password.o block.o unitTest.o magic.o -o unitTest

crack.o: crack.c md5.h password.h
	gcc -Wall -std=c99 -c crack.c

block.o: block.c block.h magic.h
	gcc -Wall -std=c99 -c block.c

md5.o: md5.c md5.h block.h magic.h
	gcc -Wall -std=c99 -c md5.c

password.o: password.c password.h magic.h block.h md5.h
	gcc -Wall -std=c99 -c password.c


magic.o: magic.c magic.h
	gcc -Wall -std=c99 -c magic.c

unitTest.o: unitTest.c magic.h block.h md5.h password.h
	gcc -Wall -std=c99 -c unitTest.c

clean:
	rm -f *.o crack unitTest
