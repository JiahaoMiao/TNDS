#include <cmath>
#include <cassert>
#include <vector>

#include "gplot++.h"
#include "fmtlib.h"
#include "funzioneBase.h"
#include "integrale.h"
#include "timer.hpp"

bool are_close(double calculated,double expected, double epsilon =1e-7){
    return fabs(calculated-expected)<epsilon;
}

void test_midpoint(){
    Seno mysin{};
    MidPoint mp{}; 
 
    assert(are_close(mp.integrate(0, M_PI, mysin, 10), 2.0082484079079745));
    assert(are_close(mp.integrate(0, M_PI, mysin, 100), 2.000082249070986));
    assert(are_close(mp.integrate(M_PI, 0, mysin, 10), -2.0082484079079745));
    assert(are_close(mp.integrate(0, 1, mysin, 10), 0.45988929071851814));
    assert(are_close(mp.integrate(1, 2, mysin, 30), 0.9564934239032155));
}
 
void test_simpson(){
    Seno mysin{};
    Simpson mp{};
    //fmt::print("{}\n",mp.integrate(0, M_PI, mysin, 10));
    assert(are_close(mp.integrate(0, M_PI, mysin, 10), 2.0001095173150043));
    assert(are_close(mp.integrate(0, M_PI, mysin, 100), 2.000000010824504));
    assert(are_close(mp.integrate(M_PI, 0, mysin, 100),-2.000000010824504));
    assert(are_close(mp.integrate(0, 1, mysin, 10), 0.45969794982382056));
    assert(are_close(mp.integrate(1, 2, mysin, 30), 0.9564491489761575));
 
}

void test_trapezoidi(){
    Seno mysin{};
    Trapezoide mp{};
    double appo = mp.integrate(0, M_PI, mysin, 10);
    fmt::print("{} {}\n",appo,mp.getError());
    assert(are_close(mp.integrate(0, M_PI, mysin, 10),  1.9835235375094546));
    assert(are_close(mp.integrate(0, M_PI, mysin, 100), 1.99983550388744364));
    assert(are_close(mp.integrate(M_PI, 0, mysin, 100), -1.99983550388744364));
    assert(are_close(mp.integrate(0, 1, mysin, 10), 0.45931454885797635));
    assert(are_close(mp.integrate(1, 2, mysin, 30), 0.956360580669458));
 
}
 
int main(int argc,char * argv[]){
    //if(argc!=2){
      //  fmt::print("Usage: ./esercuzio7.0 nstep\n");
      //  return 1;
    //}
    //test_midpoint();
    //test_simpson();
    //test_trapezoidi();

    
    double a{};
    double b{M_PI};

    //int nstep{atoi(argv[1])};  

    Seno mysin{};
    MidPoint midpoint{};
    Simpson simpson{}; 
    Trapezoide trapezoide{};
    //Integral* integrator{}; 
 
    //fmt::print("midpoint: {:.12f}\n",midpoint.integrate(b,a,nstep,mysin));
    //fmt::print("Simpson: {:.12f}\n",integrator->integrate(a,b,nstep,mysin));



    std::vector<double> steps{10, 50, 100, 500, 1000};
    std::vector<double> errors(steps.size());

    for (size_t i{}; i < errors.size(); ++i) {
        //errors[i] = fabs(midpoint.integrate(a,b,steps[i],mysin)-2); // Riempire il valore corrispondente
        //errors[i] = 4*fabs(midpoint.integrate(a,b,mysin,steps[i])-midpoint.integrate(a,b,mysin,2*steps[i]))/3; //Secondo ordine
        errors[i] = 16*fabs(midpoint.integrate(a,b,mysin,steps[i])-5*midpoint.integrate(a,b,mysin,2*steps[i])+4*midpoint.integrate(a,b,mysin,4*steps[i]))/45; //Quarto ordine
        //errors[i] = 64*fabs(64*midpoint.integrate(a,b,mysin,8*steps[i])-84*midpoint.integrate(a,b,mysin,4*steps[i])+21*midpoint.integrate(a,b,mysin,2*steps[i])-midpoint.integrate(a,b,mysin,steps[i]))/2835; //Sesto ordine
    }

    double appo = (log(errors[errors.size()-1])-log(errors[0]))/(log(steps[steps.size()-1])-log(steps[0]));
    fmt::print("Midpoint = {}\n",appo);

    Gnuplot plot{};
    const std::string output_file_name{"error.png"};
    plot.redirect_to_png(output_file_name, "800,600");
    plot.set_xlabel("Numero di passi");
    plot.set_ylabel("Errore");
    plot.set_logscale(Gnuplot::AxisScale::LOGXY);
    plot.plot(steps, errors,"midpoint",Gnuplot::LineStyle::LINESPOINTS);
    
    // È sempre bene avvisare l'utente che è stato creato un file e fornirgli il
    // nome.
    std::cout << "Plot salvato nel file " << output_file_name << std::endl;

    for (size_t i{}; i < errors.size(); ++i) {
        //errors[i] = fabs(midpoint.integrate(a,b,steps[i],mysin)-2); // Riempire il valore corrispondente
        errors[i] = 16*fabs(simpson.integrate(a,b,mysin,steps[i])-simpson.integrate(a,b,mysin,2*steps[i]))/15;

    }

    appo = (log(errors[errors.size()-1])-log(errors[0]))/(log(steps[steps.size()-1])-log(steps[0]));
    fmt::print("Simpson = {}\n",appo);

    plot.plot(steps, errors,"Simpson",Gnuplot::LineStyle::LINESPOINTS);
    
    timer t;
    t.start();
    for (size_t i{}; i < errors.size(); ++i) {
        //errors[i] = fabs(midpoint.integrate(a,b,steps[i],mysin)-2); // Riempire il valore corrispondente
        //errors[i] = 4*fabs(trapezoide.integrate(a,b,mysin,steps[i])-trapezoide.integrate(a,b,mysin,2*steps[i]))/3; //Secondo ordine
        errors[i] = 16*fabs(trapezoide.integrate(a,b,mysin,steps[i])-5*trapezoide.integrate(a,b,mysin,2*steps[i])+4*trapezoide.integrate(a,b,mysin,4*steps[i]))/45; //Quarto ordine
        //errors[i] = 64*fabs(64*trapezoide.integrate(a,b,mysin,8*steps[i])-84*trapezoide.integrate(a,b,mysin,4*steps[i])+21*trapezoide.integrate(a,b,mysin,2*steps[i])-trapezoide.integrate(a,b,mysin,steps[i]))/2835; //Sesto ordine
    }

    t.pause();
    t.print();
    appo = (log(errors[errors.size()-3])-log(errors[0]))/(log(steps[steps.size()-3])-log(steps[0]));
    fmt::print("Trapezoide = {}\n",appo);

    plot.plot(steps, errors,"Trapezoide",Gnuplot::LineStyle::LINESPOINTS);
    plot.show();
    
    return 0;
} 