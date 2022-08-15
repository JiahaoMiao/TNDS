#include <cstdlib>
#include <vector>
#include <cmath>
#include <cassert>

#include "fmtlib.h"
#include "puntoMateriale.h"
#include "campoVettoriale.h"
#include "gplot++.h"

bool are_close(double calculated,double expected, double epsilon =1e-7){
    return fabs(calculated-expected)<epsilon;
}

void test_coulomb_law(void) {
  // 0.5 µC charge with no mass (irrelevant for the electric field)
  PuntoMateriale particella{1.0, 5e-7, 5, 3, -2, };
  Posizione p{-2, 4, 1};
  
  CampoVettoriale V{particella.CampoElettrico(p)};
  fmt::print("F_e= ({},{},{})\n",V.getFx(),V.getFy(),V.getFz());
  
  assert(are_close(V.getFx(), -69.41150052142065));
  assert(are_close(V.getFy(), 9.915928645917235));
  assert(are_close(V.getFz(), 29.747785937751708));
}

int main(int argc,char*argv[]){
    if(argc<3){
        fmt::print("Usage:{} <numero cariche n> <raggio r_0>\n",argv[0]);
        exit(1);
    }
    const double e{1.60217653e-19};
    //const double me{9.1093826e-31};
    const double mp{1.67262171e-27};
    
    int n{atoi(argv[1])};
    double r_0{atof(argv[2])};

    //test_coulomb_law();
    //fmt::print("Test passato!\n");

    std::vector<PuntoMateriale> v; //vettore di n punti materiali
    std::vector<double> v_x,v_y,v_z;

    for(int i=0;i<n;i++){
        v_x.push_back(r_0*cos(2*i*M_PI/n));
        v_y.push_back(r_0*sin(2*i*M_PI/n));
        //fmt::print("{:.5e} {:.5e}\n",v_x[i]/r_0,v_y[i]/r_0);
        v_z.push_back(0.);
        PuntoMateriale P{mp,e*pow(-1,i),v_x[i],v_y[i],v_z[i]};
        v.push_back(P);
    }

    std::vector<double> d_vec; //vettore della distanza dal centro (0,0,0) da cui si vuole misurare il campo elettrico
    std::vector<double> E_vec; //Modulo del campo

    const double delta = 1e-10;

    for(double dist= delta;dist <= 1000*delta;dist+=10*delta){
        d_vec.push_back(dist*1e9);
        //calcolo campo elettrico
        Posizione pos{dist*1e9,0.,0.};
        CampoVettoriale E{pos,0.,0.,0.};

        for(int i=0;i<n;i++){   
        E += v[i].CampoElettrico(pos);        
        }
        double e_field= E.Modulo();
        E_vec.push_back(e_field);
        //fmt::print("{:.5e} {:.5e}\n",dist,e_field);
    }

    Gnuplot plt{};
    plt.redirect_to_png("esercizio5.4.png");
    plt.multiplot(2,1);

    plt.set_xlabel("x");
    plt.set_ylabel("y");
    plt.set_zrange(-5,5);
    plt.plot3d(v_x,v_y,v_z,"n-cariche",Gnuplot::LineStyle::POINTS);
    plt.show();


    plt.set_logscale(Gnuplot::AxisScale::LOGXY);
    plt.set_xlabel("Distance[nm]");
    plt.set_ylabel("Electric field [N/C]");

    plt.plot(d_vec,E_vec);

    plt.show();

   
    return 0;
}