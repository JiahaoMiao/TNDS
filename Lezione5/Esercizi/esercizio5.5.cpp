#include <cstdlib>
#include <vector>
#include <cmath>
#include <cassert>

#include "fmtlib.h"
#include "puntoMateriale.h"
#include "posizione.h"
#include "campoVettoriale.h"
#include "gplot++.h"

int main(int argc,char* argv[]){

    const double rT{6373e3}; //m
    const double mT{5.9726e24}; //kg
    const double d{3000}; //kg/m^3
    double V{4*M_PI*1000*1000*1000/3}; //m^3
    double mcatena{d*V}; //kg
    double r_0{rT+1000}; 
    PuntoMateriale T{mT,0.,0.,0.,0.}; //Terra
    std::vector<PuntoMateriale> catena;
    std::vector<double> v_x,v_y,v_z;


    for(int i{};i<100;i++){ //Costruisco il vettore che contiene la catena montuosa
        v_x.push_back(0.);
        v_y.push_back(r_0*cos(2000*(double)(i+1000)/rT));
        v_z.push_back(r_0*sin(2000*(double)(i+1000)/rT));
        
        PuntoMateriale appo{mcatena,0,v_x[i],v_y[i],v_z[i]};
        catena.push_back(appo);
    }

    std::vector<double> d_phi; //Angolo x
    std::vector<double> g_vec; //Campo y

    const double dist{rT+250000};

    for(double phi= 0; phi <= 2*M_PI;phi +=(double)10000/dist){
        d_phi.push_back(phi);
        //calcolo campo elettrico
        Posizione pos{0.,dist*cos(phi),dist*sin(phi)};
        CampoVettoriale g{T.CampoGravitazionale(pos)};
        double appo = g.Modulo();

        for(size_t i=0;i<catena.size();i++){   
        g += catena[i].CampoGravitazionale(pos);        
        }
        double e_field= (g.Modulo()-appo)/appo;//calcolo il delta dg/g
        g_vec.push_back(e_field);
        //fmt::print("{:.5e} {:.5e}\n",dist,e_field);
    }

    Gnuplot plt{};
    plt.redirect_to_png("esercizio5.5.png");

    plt.multiplot(2,1);
    plt.set_xlabel("x");
    plt.set_ylabel("y");
    //plt.set_xrange(-1,1);
    plt.plot3d(v_x,v_y,v_z,"catena montuosa",Gnuplot::LineStyle::POINTS);
    plt.show();

    plt.set_xlabel("Angle[rad]");
    plt.set_ylabel("gravitational field [N/kg]");
    plt.set_xrange(0,2*M_PI);
    plt.set_yrange(0,1.5e-7);
    plt.plot(d_phi,g_vec);
    plt.show();

    return 0;
}