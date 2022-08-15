#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "TGraphErrors.h"
#include "TApplication.h"
#include "TGraph.h"
#include "TAxis.h"
#include <string>

using namespace std;

// implementazione di una classe posizione

class Posizione {

public:
  
  Posizione() { m_x = 0 ; m_y = 0 ; m_z = 0; } ;

  Posizione( double x, double y, double z ) { m_x = x; m_y=y ; m_z=z ; } ;
 
  friend std::istream& operator>>(std::istream& is , Posizione& p ) {
    string temp;    
    std::getline(is, temp, ',' );
    p.m_x = std::stod(temp);
    std::getline(is, temp, ',' );
    p.m_y = std::stod(temp);
    std::getline(is, temp, '\n' );
    p.m_z = std::stod(temp);   
    return is;
  };


  double getDistance() const { return sqrt( m_x*m_x + m_y * m_y + m_z * m_z ) ;  } ;
  
  double GetX() const { return m_x ; } ;
  double GetY() const { return m_y ; } ;
  double GetZ() const { return m_z ; } ;

  double getDistance ( Posizione p ) const {     
    double dx = p.GetX() - m_x ;
    double dy = p.GetY() - m_y ;
    double dz = p.GetZ() - m_z ;
    return sqrt(  dx*dx + dy*dy + dz*dz ) ;  
  } ;
  
  bool operator< ( const Posizione & b ) const { return ( getDistance() > b.getDistance() ); } ;
  
  void printPositions() { cout << "Posizione : x = " << m_x << " y = " << m_y << " z = " << m_z << endl; }; 
  
private:

  double m_x, m_y, m_z ;

};

// algoritmo di riordinamento dei vettore di punti

template <typename T> void findBestPath( T start , T end ) {
  
  Posizione ref ( 0, 0,0 );
  for ( auto it = start ; it != end ; it++ ) {
    sort( it , end , [&] (Posizione i , Posizione j ) { return i.getDistance(ref) < j.getDistance(ref) ; }  ) ;
    ref = *it ;
  }
}

// main

int main() {

  TApplication app("myapp",0,0);
  
  ifstream f ( "data_points.dat") ;
  vector<Posizione> vp;
  
  Posizione p ;
  while ( f.good() ) { 
    f>>p ;
    vp.push_back( p );
  }

  for ( auto it = vp.begin() ; it != vp.end() ; it++ ) it->printPositions() ;

  findBestPath<vector<Posizione>::iterator>( vp.begin() , vp.end() ) ;
  
  for ( auto it = vp.begin() ; it != vp.end() ; it++ ) it->printPositions() ;

  TGraph mygraph;
  mygraph.SetPoint(0, 0,0  );
  int counter = 1;
  for ( auto it = vp.begin() ; it != vp.end() ; it++ ) {    
    mygraph.SetPoint(counter, (*it).GetX(), (*it).GetY() );
    counter++;
  }

  mygraph.GetXaxis()->SetLimits(-10,10);
  mygraph.SetMinimum(-10);
  mygraph.SetMaximum(10);
  mygraph.GetXaxis()->SetTitle("X");
  mygraph.GetYaxis()->SetTitle("Y");
  mygraph.SetTitle("Percorso");
  mygraph.SetMarkerStyle(21);
  mygraph.SetMarkerSize(1);
  mygraph.SetLineColor(6);
  mygraph.Draw("ALP");

  app.Run();

}