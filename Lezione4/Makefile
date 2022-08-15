LIBS := `root-config --libs`
CXXFLAGS = -g -Wall --pedantic -std=c++11 `root-config --cflags`


esercizio4.0: esercizio4.0.cpp Library.hpp
	g++ -o $@ esercizio4.0.cpp $(CXXFLAGS) 
esercizio4.0`: esercizio4.0`.cpp 
	g++ -o $@ esercizio4.0`.cpp $(CXXFLAGS) $(LIBS)
esercizio4.1:esercizio4.1.cpp 
	g++ -o $@ esercizio4.1.cpp $(CXXFLAGS) $(LIBS)
esercizio4.2:esercizio4.2.cpp 
	g++ -o $@ esercizio4.2.cpp $(CXXFLAGS) $(LIBS)
esercizio4.3:esercizio4.3.cpp comune.hpp funzioni_comune.hpp 
	g++ -o $@ esercizio4.3.cpp $(CXXFLAGS) $(LIBS)
clean:
	rm -f *.o 
cleanall: clean
	rm -f esercizio4.0 esercizio4.1 esercizio4.2 esercizio4.3