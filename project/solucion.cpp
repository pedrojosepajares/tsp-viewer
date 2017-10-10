#include "solucion.h"

Solucion::Solucion(){
    this->coste = -1;
    this->iteracion = -1;
    this->evaluacion = -1;
    this->tiempo = -1;
}

Solucion::Solucion(vector<int> ruta, int coste){
    this->ruta = ruta;
    this->coste = coste;
    this->iteracion = -1;
    this->evaluacion = -1;
    this->tiempo = -1;
}

bool Solucion::operator <(Solucion otra_solucion){
    if (this->coste < otra_solucion.coste){return true;}
    else{return false;}
}

bool Solucion::operator >(Solucion otra_solucion){
    if (this->coste > otra_solucion.coste){return true;}
    else{return false;}
}

bool Solucion::operator ==(Solucion otra_solucion){
    if (this->ruta == otra_solucion.ruta){return true;}
    else{return false;}
}

Solucion Solucion::operator =(Solucion otra_solucion){
    this->ruta = otra_solucion.ruta;
    this->coste = otra_solucion.coste;
    this->iteracion = otra_solucion.iteracion;
    this->evaluacion = otra_solucion.evaluacion;
    this->tiempo = otra_solucion.tiempo;
    return *this;
}

string Solucion::toString(){
    stringstream ss;
    ss << "{S: ";
    ss << "[";
    for (unsigned int i=0; i<this->ruta.size(); i++){
        ss << this->ruta[i];
        if (i != this->ruta.size()-1){
            ss << ", ";
        }
    }
    ss << "] C: ";
    ss << this->coste;
    ss << "}";
    return ss.str();
}
