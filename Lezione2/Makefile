CXXFLAGS = -g -Wall --pedantic -std=c++11

main: main.o Vettore.o funzioni.o
	g++ -o $@ main.o Vettore.o funzioni.o $(CXXFLAGS)
main.o: main.cpp funzioni.h
	g++ -c -o $@ main.cpp $(CXXFLAGS)
test: test.p Vettore.o
	g++ -o $@ test.o Vettore.o $(CXXFLAGS)
test.o: test.cpp Vettore.h
	g++ -c -o $@ test.cpp $(CXXFLAGS)
funzioni.o: funzioni.cpp funzioni.h
	g++ -c -o $@ funzioni.cpp $(CXXFLAGS)
Vettore.o: Vettore.cpp Vettore.h
	g++ -c -o $@ Vettore.cpp $(CXXFLAGS)
clean:
	rm -f *.o
cleanall: clean
	rm -f main