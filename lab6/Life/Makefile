playlife: lifefunc.o playlife.o
	gcc lifefunc.o playlife.o -o playlife

lifefunc.o: lifefunc.c lifefunc.h
	gcc -c lifefunc.c -o lifefunc.o

playlife.o: playlife.c lifefunc.h
	gcc -c playlife.c -o playlife.o

clean:
	rm -f *.o playlife

