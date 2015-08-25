all: LinearProbing.h QuadraticProbing.h DoubleHash.h MyExceptions.h Driver.o Utility.o
	g++ -ansi -Wall LinearProbing.h QuadraticProbing.h DoubleHash.h Driver.o Utility.o -o Driver.out

Utility.o: Utility.cpp
	g++ -ansi -Wall -c Utility.cpp

Driver.o: Driver.cpp
	g++ -ansi -Wall -c Driver.cpp

run:
	./Driver.out $(FILE) $(N) $(INTERVAL) $(M) $(R)

clean:
	rm -rf *.o
	rm -f *.out
	rm -f *~*.h.gch *#[
