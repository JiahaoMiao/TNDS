LIBS := `root-config --libs`
CXXFLAGS = -g -Wall --pedantic -std=c++11 `root-config --cflags`
CLASS = ../posizione.o ../particella.o ../campoVettoriale.o ../puntoMateriale.o ../format.o
DIR = -I ../ -I ../../

esercizio5.0: esercizio5.0.o $(CLASS) 
	g++ -o $@ esercizio5.0.o $(CXXFLAGS) $(CLASS) 
esercizio5.0.o:esercizio5.0.cpp
	g++ -c -o $@  esercizio5.0.cpp $(CXXFLAGS) $(DIR)
esercizio5.3: esercizio5.3.o $(CLASS) 
	g++ -o $@ esercizio5.3.o $(CXXFLAGS) $(CLASS) 
esercizio5.3.o:esercizio5.3.cpp 
	g++ -c -o $@ esercizio5.3.cpp $(CXXFLAGS)  $(DIR)
esercizio5.4: esercizio5.4.o $(CLASS) 
	g++ -o $@ esercizio5.4.o $(CXXFLAGS) $(CLASS) 
esercizio5.4.o:esercizio5.4.cpp 
	g++ -c -o $@ esercizio5.4.cpp $(CXXFLAGS)  $(DIR)
esercizio5.5: esercizio5.5.o $(CLASS) 
	g++ -o $@ esercizio5.5.o $(CXXFLAGS) $(CLASS) 
esercizio5.5.o:esercizio5.5.cpp 
	g++ -c -o $@ esercizio5.5.cpp $(CXXFLAGS)  $(DIR)

clean:
	rm -f *.o 
cleanall: clean
	rm -f esercizio5.0 esercizio5.1 esercizio5.2 esercizio5.3


esercizio5.1: esercizio5.1.o $(CLASS) 
	g++ -o $@ esercizio5.1.o $(CXXFLAGS) $(CLASS) 
esercizio5.1.o:esercizio5.1.cpp
	g++ -c -o $@ esercizio5.1.cpp $(CXXFLAGS)
esercizio5.2: esercizio5.2.o $(CLASS) 
	g++ -o $@ esercizio5.0.o $(CXXFLAGS) $(CLASS) 
esercizio5.2.o:esercizio5.2.cpp
	g++ -c -o $@ esercizio5.0.cpp $(CXXFLAGS)