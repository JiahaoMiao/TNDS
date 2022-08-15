#pragma once

#include <iostream>
#include <fstream>
#include "Vettore.h"

Vettore Read(int,const char*);

double CalcolaMedia(const Vettore&);
double CalcolaVarianza(const Vettore&);
double CalcolaMediana(Vettore);

void Print(const Vettore&);
void Print(const Vettore&, const char*);

void selection_sort(Vettore&);