#include <iostream>
#include <cmath>
#include <fstream>
#include <iomanip>

//caricamento da file
double* ReadDataFromFile(const char nomefile[],int *size);
//Procedure si scambio
void ScambiaByValue(double a, double b);
void ScambiaByRef(double &a, double *b);
void ScambiaByPointer(double *a,double *b);
//Algoritmo di ordinameto
void Selection_sort(double* data,int size);
//Calcolo statistico
double CalcolaMedia(double *data,int size);
double CalcolaMediana(double *data,int size);
double CalcolaVarianza(double *data,int size);

void Print(const char*filename,double *data, int size);
void Print(const double*data,int size);
