#pragma once

#include <iostream>
#include <fstream>
#include <cstring>
#include <random> 
#include "Vettore.h"

Vettore Read(int,const char*);

double CalcolaMedia(const Vettore&);
double CalcolaVarianza(const Vettore&);
double CalcolaMediana(Vettore);

void Print(const Vettore&);
void Print(const Vettore&, const char*);

//========================
//Sorting algorithms
//========================
void selection_sort(Vettore&);
void merge(Vettore& a,int low,int mid,int high);
void merge_sort(Vettore& a,int low,int high);
void quicksort(Vettore& v, unsigned int left_bound,unsigned int right_bound);