#include "solutore.h"

double segno(double x){
    return (x==0?0.:(x>0?1.:-1.));
}

double derivata(const FunzioneBase &f,double x, double h,int n){
    for(int i{};i<=n;i++)

    //return (f.Eval(x-2*h)-8*f.Eval(x-h)+8*f.Eval(x+h)-f.Eval(x+2*h))/(12*h); //con una incertezza o(h^4)
    
    return (f.Eval(x+4*h)-40*f.Eval(x+2*h)+256*f.Eval(x+h)-256*f.Eval(x-h)+40*f.Eval(x-2*h)-f.Eval(x-4*h))/(360*h); //con una incertezza o(h^5)
}

double derivata(std::function<double(double)>f,double x, double h,int n){
    for(int i{};i<=n;i++)

    //return (f(x-2*h)-8*f(x-h)+8*f(x+h)-f(x+2*h))/(12*h); //con una incertezza o(h^4)
    
    return (f(x+4*h)-40*f(x+2*h)+256*f(x+h)-256*f(x-h)+40*f(x-2*h)-f(x-4*h))/(360*h); //con una incertezza o(h^5)
}

Solutore::~Solutore(){}

bool Solutore::Trovato() const{
    return m_found;
}
double Solutore::Incertezza()const{
    return m_prec;
}

Bisezione::Bisezione():Solutore(){}
Bisezione::Bisezione(double prec):Solutore(prec){}
Bisezione::~Bisezione(){;}

double Bisezione::CercaZeri(double xmin,double xmax,const FunzioneBase& f,double prec,unsigned int nmax){
    m_niterations = 0;
    m_nmax = nmax;
    

    if(xmin<xmax){//controllo che max e min siano corretti
        m_a=xmin;
        m_b=xmax;
    }else{
        m_a=xmax;
        m_b=xmin;
    }

    double fa = f.Eval(m_a);
    double fb = f.Eval(m_b);

    if(segno(fa)*segno(fb)>0){
        m_found = false;
        return std::nan(" "); //Cattive condizioni iniziali, non nelle ipotesi del teorema degli zeri
    }

    while( fabs(m_b-m_a)>prec){
        double c =0.5*(m_a+m_b);
        double fc = f.Eval(c);
        //std::cout<< "fc = " << std::setprecision(14) << fc << "\n";
        if(m_niterations>m_nmax)break; //Per evitare un loop infinito, esco prima di nmax
        m_niterations++;
        if(fc==0){m_found= true; return c;} // ho trovato lo zero esco
        else if(segno(fa)*segno(fc)<=0){m_b=c;fb=fc;} //controllo quale intervallo soddisfa le ipotesi del teorema degli zeri se [a,c]
        else if(segno(fb)*segno(fc)<=0){m_a=c; fa=fc;}// o [c,b]
        else return std::nan(" "); // Se nessuno degli intervalli [a,c] o [c,b] soddisfano il teorema, esco
    }
    //Raggiunto la precisione desiderata esco dal ciclo
    m_prec = 0.5*fabs(m_a-m_b);
    m_found= true;
    return 0.5*(m_a+m_b);   
}

 double Bisezione::CercaZeri(double xmin,double xmax,std::function<double(double)>f ,double prec,unsigned int nmax){
    m_niterations = 0;
    m_nmax = nmax;
    

    if(xmin<xmax){//controllo che max e min siano corretti
        m_a=xmin;
        m_b=xmax;
    }else{
        m_a=xmax;
        m_b=xmin;
    }

    double fa = f(m_a);
    double fb = f(m_b);

    if(segno(fa)*segno(fb)>0){
        m_found = false;
        return std::nan(" "); //Cattive condizioni iniziali, non nelle ipotesi del teorema degli zeri
    }

    while( fabs(m_b-m_a)>prec){
        double c =0.5*(m_a+m_b);
        double fc = f(c);
        //std::cout<< "fc = " << std::setprecision(14) << fc << "\n";
        if(m_niterations>m_nmax)break; //Per evitare un loop infinito, esco prima di nmax
        m_niterations++;
        if(fc==0){m_found= true; return c;} // ho trovato lo zero esco
        else if(segno(fa)*segno(fc)<=0){m_b=c;fb=fc;} //controllo quale intervallo soddisfa le ipotesi del teorema degli zeri se [a,c]
        else if(segno(fb)*segno(fc)<=0){m_a=c; fa=fc;}// o [c,b]
        else return std::nan(" "); // Se nessuno degli intervalli [a,c] o [c,b] soddisfano il teorema, esco
    }
    //Raggiunto la precisione desiderata esco dal ciclo
    m_prec = 0.5*fabs(m_a-m_b);
    m_found= true;
    return 0.5*(m_a+m_b);   
 }

bool Bisezione::Trovato() const{
    return m_found;
}
double Bisezione::Incertezza()const{
    return m_prec;
}


// ===================================
// Secante
// ===================================

Secante::Secante():Solutore(){}
Secante::Secante(double prec):Solutore(prec){}
Secante::~Secante(){;}

double Secante::CercaZeri(double xmin,double xmax,const FunzioneBase& f,double prec,unsigned int nmax){
    m_niterations = 0;
    m_nmax = nmax;
    

    if(xmin<xmax){//controllo che max e min siano corretti
        m_a=xmin;
        m_b=xmax;
    }else{
        m_a=xmax;
        m_b=xmin;
    }

    double fa = f.Eval(m_a);
    double fb = f.Eval(m_b);

    //Cattive condizioni iniziali, non nelle ipotesi del teorema degli zeri
    if(segno(fa)*segno(fb)>0){
        m_found = false;
        return std::nan(" "); 
    }

    while( fabs(m_b-m_a)>prec){
        double c = m_b-(fb*(m_b-m_a)/(fb-fa)); //
        double fc = f.Eval(c);
        //std::cout<< "fc = " << std::setprecision(14) << fc << "\n";
        if(m_niterations>m_nmax)break; //Per evitare un loop infinito, esco prima di nmax
        m_niterations++;
        if(fc==0){m_found= true; return c;} // ho trovato lo zero esco
        //Regula Falsi
        else if(segno(fa)*segno(fc)<=0){m_b=c;fb=fc;} //controllo quale intervallo soddisfa le ipotesi del teorema degli zeri se [a,c]
        else if(segno(fb)*segno(fc)<=0){m_a=c; fa=fc;}// o [c,b]
        else return std::nan(" "); // Se nessuno degli intervalli [a,c] o [c,b] soddisfano il teorema, esco
    }
    //Raggiunto la precisione desiderata esco dal ciclo
    m_prec = 0.5*fabs(m_a-m_b);
    m_found= true;
    return m_b-(fb*(m_b-m_a)/(fb-fa));   
}

double Secante::CercaZeri(double xmin,double xmax,std::function<double(double)>f,double prec,unsigned int nmax){
    m_niterations = 0;
    m_nmax = nmax;
    

    if(xmin<xmax){//controllo che max e min siano corretti
        m_a=xmin;
        m_b=xmax;
    }else{
        m_a=xmax;
        m_b=xmin;
    }

    double fa = f(m_a);
    double fb = f(m_b);

    //Cattive condizioni iniziali, non nelle ipotesi del teorema degli zeri
    if(segno(fa)*segno(fb)>0){
        m_found = false;
        return std::nan(" "); 
    }

    while( fabs(m_b-m_a)>prec){
        double c = m_b-(fb*(m_b-m_a))/(fb-fa); 
        double fc = f(c);
        //std::cout<< "fc = " << std::setprecision(14) << fc << "\n";
        if(m_niterations>m_nmax)break; //Per evitare un loop infinito, esco prima di nmax
        m_niterations++;
        if(fc==0){m_found= true; return c;} // ho trovato lo zero esco
        //Regula Falsi
        else if(segno(fa)*segno(fc)<=0){m_b=c;fb=fc;} //controllo quale intervallo soddisfa le ipotesi del teorema degli zeri se [a,c]
        else if(segno(fb)*segno(fc)<=0){m_a=c; fa=fc;}// o [c,b]
        else return std::nan(" "); // Se nessuno degli intervalli [a,c] o [c,b] soddisfano il teorema, esco
    }
    //Raggiunto la precisione desiderata esco dal ciclo
    m_prec = 0.5*fabs(m_a-m_b);
    m_found= true;
    return m_b-(fb*(m_b-m_a)/(fb-fa));   
}

bool Secante::Trovato() const{
    return m_found;
}
double Secante::Incertezza()const{
    return m_prec;
}


// ===================================
// Metodo di Newton
// ===================================

Newton::Newton():Solutore(){}
Newton::Newton(double prec):Solutore(prec){}
Newton::~Newton(){;}

double Newton::CercaZeri(double xmin,double xmax,const FunzioneBase& f,double prec,unsigned int nmax){
    m_niterations = 0;
    m_nmax = nmax;
    

    if(xmin<xmax){//controllo che max e min siano corretti
        m_a=xmin;
        m_b=xmax;
    }else{
        m_a=xmax;
        m_b=xmin;
    }

    double fa = f.Eval(m_a);
    double fb = f.Eval(m_b);

    //Cattive condizioni iniziali, non nelle ipotesi del teorema degli zeri
    if(segno(fa)*segno(fb)>0){
        m_found = false;
        return std::nan(" "); 
    }

    double c{fabs(m_b+m_a)/2};
    double fc{f.Eval(c)};

    while( fabs(m_b-m_a)>prec){
        c = c-(fc/derivata(f,c)); 
        fc = f.Eval(c);
        //std::cout<< "fc = " << std::setprecision(14) << fc << "\n";
        if(m_niterations>m_nmax)break; //Per evitare un loop infinito, esco prima di nmax
        m_niterations++;
        if(fc==0){m_found= true; return c;} // ho trovato lo zero esco
        //Regula Falsi
        else if(segno(fa)*segno(fc)<=0){m_b=c;fb=fc;} //controllo quale intervallo soddisfa le ipotesi del teorema degli zeri se [a,c]
        else if(segno(fb)*segno(fc)<=0){m_a=c; fa=fc;}// o [c,b]
        else return std::nan(" "); // Se nessuno degli intervalli [a,c] o [c,b] soddisfano il teorema, esco
    }
    //Raggiunto la precisione desiderata esco dal ciclo
    m_prec = 0.5*fabs(m_a-m_b);
    m_found= true;
    return c-(fc/derivata(f,c));   
}

double Newton::CercaZeri(double xmin,double xmax,std::function<double(double)>f,double prec,unsigned int nmax){
    m_niterations = 0;
    m_nmax = nmax;
    

    if(xmin<xmax){//controllo che max e min siano corretti
        m_a=xmin;
        m_b=xmax;
    }else{
        m_a=xmax;
        m_b=xmin;
    }

    double fa = f(m_a);
    double fb = f(m_b);

    //Cattive condizioni iniziali, non nelle ipotesi del teorema degli zeri
    if(segno(fa)*segno(fb)>0){
        m_found = false;
        return std::nan(" "); 
    }
    double c{fabs(m_b+m_a)/2};
    double fc= f(c);

    while( fabs(m_b-m_a)>prec){
        c = c-(fc/derivata(f,c)); 
        fc = f(c);
        //std::cout << "c= " << c << "  fc = " << std::setprecision(14) << fc << "\n";
        if(m_niterations>m_nmax)break; //Per evitare un loop infinito, esco prima di nmax
        m_niterations++;
        if(fc==0){m_found= true; return c;} // ho trovato lo zero esco
        //Regula Falsi
        else if(segno(fa)*segno(fc)<=0){m_b=c; fb=fc;} //controllo quale intervallo soddisfa le ipotesi del teorema degli zeri se [a,c]
        else if(segno(fb)*segno(fc)<=0){m_a=c; fa=fc;}// o [c,b]
        else return std::nan(" "); // Se nessuno degli intervalli [a,c] o [c,b] soddisfano il teorema, esco
    }
    //Raggiunto la precisione desiderata esco dal ciclo
    m_prec = 0.5*fabs(m_a-m_b);
    m_found = true;
    return c-(fc/derivata(f,c));   
}

bool Newton::Trovato() const{
    return m_found;
}
double Newton::Incertezza()const{
    return m_prec;
}