CXXFLAGS = -g -Wall --pedantic -std=c++11 `root-config --cflags`

posizione.o:posizione.cpp posizione.h
	g++ -c -o $@  posizione.cpp $(CXXFLAGS)
posizioneS.o:posizioneS.cpp posizione.h
	g++ -c -o $@  posizioneS.cpp $(CXXFLAGS)
particella.o:particella.cpp particella.h 
	g++ -c -o $@  particella.cpp $(CXXFLAGS)
campoVettoriale.o:campoVettoriale.cpp campoVettoriale.h
	g++ -c -o $@  campoVettoriale.cpp $(CXXFLAGS)
puntoMateriale.o:puntoMateriale.cpp puntoMateriale.h
	g++ -c -o $@  puntoMateriale.cpp $(CXXFLAGS)
	
clean:
	rm -f *.o 
cleanall: clean
	rm -f *.o 

