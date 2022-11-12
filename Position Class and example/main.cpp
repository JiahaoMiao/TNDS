#include <cstdlib>
#include <vector>
#include <cmath>
#include <cassert>

#include "PuntoMateriale.h"
#include "Position.hpp"
#include "CampoVettoriale.h"

#include "TApplication.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TAxis.h"

int main(){

	TApplication app{"app",0,0};
	TCanvas c{"GOCE","GOCE"};
	TGraph graph;

	//Dati
	const double rT{6373e3}; //m
	const double mT{5.9726e24}; //kg
	const double d{3000}; //kg/m^3
	double V{4*M_PI*1000*1000*1000/3}; //m^3
	double mcatena{d*V}; //kg
	double r_0{rT+1000};//Posizione delle sfere-montagne
	PuntoMateriale T{mT,0.,0.,0.,0.}; //Terra
	std::vector<PuntoMateriale> catena;

	for(int i{};i<100;i++){ //Costruisco il vettore che contiene la catena montuosa
		Spherical pos{r_0 , 2000*static_cast<double>(i+1000)/rT, 0.};
		PuntoMateriale appo{mcatena,0,&pos};
		catena.push_back(appo);
	}

	const double dist{rT+250000}; //Distanza del satellite dal centro della terra

	
	for(double theta{}; theta <= 2*M_PI;theta += static_cast<double>(10000)/dist){
			
		Spherical pos{dist,theta,0.};
		CampoVettoriale g{T.CampoGravitazionale(&pos)};
		double appo = g.Modulo();
	
		for(size_t i=0;i<catena.size();i++){   
		g += catena[i].CampoGravitazionale(&pos);        
		}
		double e_field= (g.Modulo()-appo)/appo;//calcolo il delta dg/g
	
		graph.AddPoint(theta, e_field);

	}

	c.cd();
	graph.GetXaxis()->SetTitle("Angle [rad]");
	graph.GetYaxis()->SetTitle("gravitational field [N/kg]");
	graph.GetXaxis()->SetLimits(0.,2*M_PI);
	graph.GetYaxis()->SetLimits(0.,1.5e-7);
	graph.Draw("ALP");

	app.Run();

	return 0;
}