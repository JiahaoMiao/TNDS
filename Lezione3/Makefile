CXXFLAGS = -g -Wall --pedantic -std=c++11

esercizio3.0: esercizio3.0.cpp Vettore.hpp funzioni.hpp
	g++ -o $@ esercizio3.0.cpp $(CXXFLAGS)
esercizio3.1:esercizio3.1.cpp funzioniSTL.hpp
	g++ -o $@ esercizio3.1.cpp $(CXXFLAGS)
esercizio3.2:esercizio3.2.cpp funzioniSTL.hpp
	g++ -o $@ esercizio3.2.cpp $(CXXFLAGS)
clean:
	rm -f *.o 
cleanall: clean
	rm -f esercizio3.0 esercizio3.1 esercizio3.2