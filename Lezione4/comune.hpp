
#ifndef _comune_h_
#define _comune_h_

#include <iostream>
#include <string>
#include <vector>

//using namespace std;

class comune {

 public :

  // costruttori

  comune( ) { m_nome = "none";}  ; 

  comune( std::string regione , std::string provincia , std::string nome,  std::vector<double> average , std::vector<double> actual ) {  
    m_nome = nome;
    m_regione = regione;
    m_provincia = provincia ;
    if ( average.size() != actual.size() ) exit(-999);
    m_average = average ;
    m_actual  = actual  ; 
    for ( size_t k = 0 ; k < average.size() ; k++ ) {
      m_avetot+= m_average[k] ;
      m_actualtot += m_actual[k] ;
    };
  } ;

  double getRatio() const { return m_actualtot / m_avetot ; } ;
  std::string getNome( ) const {return m_nome ;};
  std::string getProvincia( ) const {return m_provincia ;};
  std::string getRegione( ) const {return m_regione ;};
  std::vector<double> GetAveVector() const { return m_average ;} ;
  std::vector<double> GetActVector() const { return m_actual ;} ;
  double GetAve() const {  return m_avetot; } ;
  double GetAct() const {  return m_actualtot; } ;

  void PrintAve() { for ( size_t i = 0 ; i < m_average.size() ; i++ ) std::cout << m_average[i] << " " << '\n';  } ;
  void PrintActual() { for ( size_t i = 0 ; i < m_actual.size() ; i++ ) std::cout << m_actual[i] << " " << '\n';  } ;

 private :

  std::string m_nome ; 
  std::string m_regione;
  std::string m_provincia;

  std::vector<double> m_average ;
  std::vector<double> m_actual  ;

  double m_avetot = 0 ;
  double m_actualtot = 0;
    
};

#endif
