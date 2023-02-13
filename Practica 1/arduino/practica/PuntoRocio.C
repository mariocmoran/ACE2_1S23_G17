#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    double RH;          // humedad relativa
    double PT;           // Punto de rocio
    double T;            // Temperatura
//    double PS;           // PRESION DE VAPOR SATURADO; se busca en tabla en kPa
 //   double Pv;           // PRESION DE VAPOR; resultado en kPa

    RH = 54;

    T = 28;


    
    double potencia = 1.00000/8.00000;  //Para simular una raiz octava; NO SE CAMBIA
    double octava;

    double Inoctava = RH/100;

    octava = pow(Inoctava, potencia);


    PT = octava*(112+(0.9*T))+(0.1*T)-112;


    cout << "EL PUNTO DE ROCIO ES: " << PT  << " °C td   ";



/*    if ((T >= 0.00) && (T < 4.00)){
        PS = 0.61;
    }else if((T >= 5.00) && (T < 9.00)){
        PS = 0.87;
    }
    else if((T >= 10.00) && (T < 14.00)){
        PS = 1.23;
    }
    else if((T >= 15.00) && (T < 19.00)){
        PS = 1.70;
    }
    else if((T >= 20.00) && (T < 24.00)){
        PS = 2.33;
    }
    else if((T >= 25.00) && (T < 29.00)){
        PS = 3.17;
    }
    else if((T >= 30.00) && (T < 34.00)){
        PS = 4.24;
    }
    else if((T >= 35.00) && (T < 39.00)){
        PS = 5.62;
    }
    else if((T >= 40.00) && (T < 44.00)){
        PS = 7.38;
    }
    else if((T >= 45.00) && (T < 49.00)){
        PS = 9.59;
    }
    else if((T >= 50.00) && (T < 54.00)){
        PS = 12.35;
    }

    Pv = (RH*PS)/100;*/


}
