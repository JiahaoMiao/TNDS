#include <cmath>

#include "randomGen.h"
#include "esperimentoPrisma.h"
#include "fmtlib.h"
#include <fstream>

#include "TApplication.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TAxis.h"
#include "TCanvas.h"
#include "TGraph.h"



// ======================================================================================================================
// Questa funzione aggiorna il coefficiente di correlazione R dato il passo i-esimo, x_i,y_i,le varie medie per reference
// ======================================================================================================================
double new_corr(int i,double x,double y,double& mean_x,double& mean_y,double& mean_xy,double& mean_x2,double& mean_y2,double& sigma_x,double& sigma_y);

double new_corr(int i,double x,double y,double& mean_x,double& mean_y,double& mean_xy,double& mean_x2,double& mean_y2,double& sigma_x,double& sigma_y){
    
    mean_x= static_cast<double>(i)/static_cast<double>(i+1)*mean_x+1.0/static_cast<double>(i+1)*x;
    mean_y= static_cast<double>(i)/static_cast<double>(i+1)*mean_y+1.0/static_cast<double>(i+1)*y;
    mean_xy= static_cast<double>(i)/static_cast<double>(i+1)*mean_xy+1.0/static_cast<double>(i+1)*(x*y);
    mean_x2= static_cast<double>(i)/static_cast<double>(i+1)*mean_x2+1.0/static_cast<double>(i+1)*(x*x);
    mean_y2= static_cast<double>(i)/static_cast<double>(i+1)*mean_y2+1.0/static_cast<double>(i+1)*(y*y);

    sigma_x = sqrt(mean_x2-mean_x*mean_x);
    sigma_y = sqrt(mean_y2-mean_y*mean_y);

    return (mean_xy-mean_x*mean_y)/(sigma_x*sigma_y); 
}

int main(){
    TApplication app{"app",0,0};
    TCanvas c1{"Theta","Esperimento Prisma",1600,900};
    c1.Divide(3,1);
    TCanvas c2{"Delta","Esperimento Prisma",1600,900};
    c2.Divide(3,1);
    TCanvas c3{"Indici di Rifrazioni","Esperimento Prisma",1600,900};
    c3.Divide(3,1);
    TCanvas c4{"Parametri di Cauchy","Esperimento Prisma",1600,900};
    c4.Divide(3,1);
    

    //Parametri Esperimento
    
    const double A{2.7};
    const double B{6e4};//nm^2
    double lambda_1{579.1};//nm
    double lambda_2{404.7};//nm
    double alpha{M_PI/3.}; //60 gradi
    double sigma{0.3e-3};// rad
    double theta_0{M_PI_2};//rad

    EsperimentoPrisma Prism{A,B,alpha,lambda_1,lambda_2,sigma,theta_0};
    Prism.Esergui();//Eseguo una volta per avere i valori di theta1,theta2 input
    Prism.Analizza();
    //fmt::print("Amis= {}\nBmis={}\nth0mis={}\nth1mis={}\nth2mis={}\n",Prism.getAmis(),Prism.getBmis(),Prism.getTh0mis(),Prism.getTh1mis(),Prism.getTh2mis());
    
    double sigmaD{4.1e-4};
    double sigmaN{2.1e-4};
    double sigmaA{1.2e-3};
    double sigmaB{233};
    //Istrogrammi misure di theta_1 e theta_2
    
    TH1F th0hist{"Distribuzione theta_0","Distribuzione theta_0",100,Prism.getTh0()-3*sigma,Prism.getTh0()+3*sigma};
    TH1F th1hist{"Distribuzione theta_1","Distribuzione theta_1",100,Prism.getTh1()-3*sigma,Prism.getTh1()+3*sigma};
    TH1F th2hist{"Distribuzione theta_2","Distribuzione theta_2",100,Prism.getTh2()-3*sigma,Prism.getTh2()+3*sigma};
     
    TH1F d1hist{"Distribuzione di delta_1","Distribuzione di delta_1",100,Prism.getDm1()-3*sigmaD,Prism.getDm1()+3*sigmaD};
    TH1F d2hist{"Distribuzione di delta_2","Distribuzione di delta_2",100,Prism.getDm2()-3*sigmaD,Prism.getDm2()+3*sigmaD};
    TH2F dcorr{"Residui 2D","Residui 2D",100,3*sigmaD,3*sigmaD,100,3*sigmaD,3*sigmaD};
    
    TH1F n1hist{"Distribuzione di n_1","Distribuzione di n_1",100,Prism.getN1()-3*sigmaN,Prism.getN1()+3*sigmaN};
    TH1F n2hist{"Distribuzione di n_2","Distribuzione di n_2",100,Prism.getN2()-3*sigmaN,Prism.getN2()+3*sigmaN};
    TH2F ncorr{"Residui n_1,2","Residui n_1,2",100,3*sigmaN,3*sigmaN,100,3*sigmaN,3*sigmaN};
    
    TH1F Ahist{"Distribuzione di A","Distribuzione di A",100,Prism.getA()-3*sigmaA,Prism.getA()+3*sigmaA};
    TH1F Bhist{"Distribuzione di B","Distribuzione di B",100,Prism.getB()-3*sigmaB,Prism.getB()+3*sigmaB};
    TH2F ABcorr{"Residui A e B","Residui A e B",100,3*sigmaA,3*sigmaA,100,3*sigmaB,3*sigmaB};
    
    th0hist.StatOverflows(true);
    th1hist.StatOverflows(true);
    th2hist.StatOverflows(true);
    d1hist.StatOverflows(true);
    d2hist.StatOverflows(true);
    dcorr.StatOverflows(true);
    n1hist.StatOverflows(true);
    n2hist.StatOverflows(true);
    ncorr.StatOverflows(true);
    Ahist.StatOverflows(true);
    Bhist.StatOverflows(true);
    ABcorr.StatOverflows(true);
    
    int tot{10000};
    double r_d,mean_d1{},mean_d2{},mean_d1d2{},mean_d12{},mean_d22{},sigma_d1{},sigma_d2{};
    double r_n,mean_n1{},mean_n2{},mean_n1n2{},mean_n12{},mean_n22{},sigma_n1{},sigma_n2{};
    double r_AB,mean_A{},mean_B{},mean_AB{},mean_A2{},mean_B2{},sigma_A{},sigma_B{};

    for(int i{};i<tot;i++){//Faccio tot volte l'esperimento
        Prism.Esergui();
        Prism.Analizza();
        
        th0hist.Fill(Prism.getTh0mis());
        th1hist.Fill(Prism.getTh1mis());
        th2hist.Fill(Prism.getTh2mis());

        d1hist.Fill(Prism.getDm1mis());
        d2hist.Fill(Prism.getDm2mis());
        dcorr.Fill(Prism.getDm1()-Prism.getDm1mis(),Prism.getDm2()-Prism.getDm2mis());

        n1hist.Fill(Prism.getN1mis());
        n2hist.Fill(Prism.getN2mis());
        ncorr.Fill(Prism.getN1()-Prism.getN1mis(),Prism.getN2()-Prism.getN2mis());
        
        Ahist.Fill(Prism.getAmis());
        Bhist.Fill(Prism.getBmis());
        ABcorr.Fill(Prism.getA()-Prism.getAmis(),Prism.getB()-Prism.getBmis());

        r_d = new_corr(i,Prism.getDm1mis(),Prism.getDm2mis(),mean_d1,mean_d2,mean_d1d2,mean_d12,mean_d22,sigma_d1,sigma_d2);
        r_n = new_corr(i,Prism.getN1mis(),Prism.getN2mis(),mean_n1,mean_n2,mean_n1n2,mean_n12,mean_n22,sigma_n1,sigma_n2);
        r_AB = new_corr(i,Prism.getAmis(),Prism.getBmis(),mean_A,mean_B,mean_AB,mean_A2,mean_B2,sigma_A,sigma_B);
    }
    //std::ofstream out{"Analisi dati Prisma.dat"};

    fmt::print("theta_0={} rad(arbitrario),\ntheta_1={} rad,\ntheta_2={} rad,\nsigma(theta)={} rad\n\n",th0hist.GetMean(),th1hist.GetMean(),th2hist.GetMean(),th0hist.GetRMS());
    fmt::print("d1={} rad,\nd2={} rad,\nsigma(d1)={} rad,\nsigma(d2)={} rad,\nrho(d1,d2)= {}\n\n",mean_d1,mean_d2,sigma_d1,sigma_d2,r_d);
    fmt::print("n1={},\nn2={},\nsigma(n1)={},\nsigma(n2)={},\nrho(n1,n2)= {}\n\n",mean_n1,mean_n2,sigma_n1,sigma_n2,r_n);
    fmt::print("A={},\nB={} nm^2,\nsigma(A)={},\nsigma(B)={} nm^2,\nrho(A,B)= {}\n",mean_A,mean_B,sigma_A,sigma_B,r_AB);

    /*
    c1.cd(1);
    th0hist.GetXaxis()->SetTitle("[rad]");
    th0hist.GetYaxis()->SetTitle("N");
    th0hist.Draw();

    c1.cd(2);
    th1hist.GetXaxis()->SetTitle("[rad]");
    th1hist.GetYaxis()->SetTitle("N");
    th1hist.Draw();

    c1.cd(3);
    th2hist.GetXaxis()->SetTitle("[rad]");
    th2hist.GetYaxis()->SetTitle("N");
    th2hist.Draw();

    c2.cd(1);
    d1hist.GetXaxis()->SetTitle("[rad]");
    d1hist.GetYaxis()->SetTitle("N");
    d1hist.Draw();

    c2.cd(2);
    d2hist.GetXaxis()->SetTitle("[rad]");
    d2hist.GetYaxis()->SetTitle("N");
    d2hist.Draw();

    c2.cd(3);
    dcorr.GetXaxis()->SetTitle("[rad]");
    dcorr.GetYaxis()->SetTitle("[rad]");
    dcorr.Draw();

    c3.cd(1);
    n1hist.GetXaxis()->SetTitle("n");
    n1hist.GetYaxis()->SetTitle("N");
    n1hist.Draw();

    c3.cd(2);
    n2hist.GetXaxis()->SetTitle("n");
    n2hist.GetYaxis()->SetTitle("N");
    n2hist.Draw();

    c3.cd(3);
    ncorr.GetXaxis()->SetTitle("n");
    ncorr.GetYaxis()->SetTitle("n");
    ncorr.Draw();
    
    c4.cd(1);
    Ahist.GetXaxis()->SetTitle("A");
    Ahist.GetYaxis()->SetTitle("N");
    Ahist.Draw();

    c4.cd(2);
    Bhist.GetXaxis()->SetTitle("B [nm^2]");
    Bhist.GetYaxis()->SetTitle("N");
    Bhist.Draw();

    c4.cd(3);
    ABcorr.GetXaxis()->SetTitle("A");
    ABcorr.GetYaxis()->SetTitle("B [nm^2]");
    ABcorr.Draw();

    c1.Print("Theta.png");
    c2.Print("Delta.png");
    c3.Print("Indici di Rifrazione.png");
    c4.Print("Parametri di Cauchy.png");
    app.Run();
    */
    return 0;
}