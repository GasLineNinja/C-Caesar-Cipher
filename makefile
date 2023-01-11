a.out: main.o caesar.o
	gcc *.o

main.o: caesar.h main.c
	gcc -c main.c

caesar.o: caesar.h caesar.c
	gcc -c caesar.c

clean:
	rm a.out    
	rm *.o