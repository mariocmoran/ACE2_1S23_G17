#include <iostream>

using namespace std;

int main()
{
    double RH;          // humedad relativa
    double AH;           // humedad absoluta; densidad de vapor de agua
    double T;            // Temperatura
    double DS;           // DENSIDAD DE VAPOR SATURADO; se busca en tabla

    RH = 60;

    T = 25;

    if ((T >= 0.00) && (T < 4.00)){
        DS = 0.004847;
    }else if((T >= 5.00) && (T < 9.00)){
        DS = 0.006796;
    }
    else if((T >= 10.00) && (T < 14.00)){
        DS = 0.009401;
    }
    else if((T >= 15.00) && (T < 19.00)){
        DS = 0.01283;
    }
    else if((T >= 20.00) && (T < 24.00)){
        DS = 0.01730;
    }
    else if((T >= 25.00) && (T < 29.00)){
        DS = 0.02305;
    }
    else if((T >= 30.00) && (T < 34.00)){
        DS = 0.03038;
    }
    else if((T >= 35.00) && (T < 39.00)){
        DS = 0.03964;
    }

    AH = (RH*DS)/100;

    cout << "LA HUMEDAD ABSOLUTA ES: " << AH  << " kg/m3";
    
    

}