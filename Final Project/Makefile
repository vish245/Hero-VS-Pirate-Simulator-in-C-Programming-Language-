LIBS = -lpthread

fp:	main.o deque.o fight.o fighters.o
	gcc -o fp main.o deque.o fight.o fighters.o $(LIBS)


main.o:		main.c defs.h
		gcc -c main.c

deque.o:	deque.c defs.h
		gcc -c deque.c

fight.o:	fight.c defs.h
		gcc -c fight.c

fighters.o:	fighters.c defs.h
		gcc -c fighters.c

clean:
	rm -f fp main.o deque.o fight.o fighters.o
