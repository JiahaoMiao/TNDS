ROOT:= `root-config --libs` `root-config --cflags`
CXXFLAGS := -g -Wall --pedantic 
LIBS := format.o
INC := -I ../

light:light.o $(LIBS)
	g++ -o $@ $^ $(CXXFLAGS) $(ROOT) $(INC)
light.o:light.cpp 
	g++ -c $< $(CXXFLAGS) $(ROOT) 
format.o:format.cc fmtlib.h
	g++ -c $<
