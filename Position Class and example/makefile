CXXFLAGS = -g -Wall --pedantic -std=c++11

ROOT := `root-config --libs` `root-config --cflags`
LIBS := Position.o Particella.o CampoVettoriale.o PuntoMateriale.o 


main:main.o $(LIBS)
	g++ -o $@ $< $(ERR) $(LIBS) $(ROOT)

main.o:main.cpp 
	g++ -c $< $(INC) $(ERR) $(ROOT)

Position.o: Position.cpp Position.hpp
	g++ -c $< $(CXXFLAGS)
particella.o:particella.cpp particella.h 
	g++ -c $< $(CXXFLAGS)
campoVettoriale.o:campoVettoriale.cpp campoVettoriale.h
	g++ -c $< $(CXXFLAGS)
puntoMateriale.o:puntoMateriale.cpp puntoMateriale.h
	g++ -c $< $(CXXFLAGS)

	
clean:
	rm -f *.o 
