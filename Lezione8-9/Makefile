LIBS:= `root-config --libs` `root-config --cflags`
CXXFLAGS = -g -Wall --pedantic -std=c++11
DIR = -I ../ -I ../../

provaAlgebra.o:provaAlgebra.cpp vectorOperations.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR)
provaAlgebra:provaAlgebra.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) 

esercizio8.0.o:esercizio8.0.cpp
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS)
esercizio8.0:esercizio8.0.o ../format.o
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) && ./$@

Pendolo.o:Pendolo.cpp funzioneVettorialeBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS)
Pendolo:Pendolo.o ../format.o 
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) && ./$@

Oscillatore_Armonico_Forzato.o:Oscillatore_Armonico_Forzato.cpp funzioneVettorialeBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS)
Oscillatore_Armonico_Forzato:Oscillatore_Armonico_Forzato.o ../format.o 
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) 

Risonanza.o:Risonanza.cpp funzioneVettorialeBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS)
Risonanza:Risonanza.o ../format.o 
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) && ./$@

Gravitazione.o:Gravitazione.cpp funzioneVettorialeBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS)
Gravitazione:Gravitazione.o ../format.o 
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) && ./$@

Elettromagnetismo.o:Elettromagnetismo.cpp funzioneVettorialeBase.h
	g++ -c -o $@ $< $(CXXFLAGS) $(DIR) $(LIBS)
Elettromagnetismo:Elettromagnetismo.o ../format.o 
	g++ -o $@ $^ $(CXXFLAGS) $(DIR) $(LIBS) && ./$@

clean:
	rm *.o
cleanall:
	rm provaAlgebra Pendolo Oscillatore_Armonico_Forzato Risonanza 
