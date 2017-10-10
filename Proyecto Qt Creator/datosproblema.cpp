#include "DatosProblema.h"
DatosProblema::DatosProblema(){
    this->nombre_problema = "NULO";
    this->numero_ciudades = -1;
    this->distancia_optima = -1;
}

void DatosProblema::leeFichero(string nombre_fichero){

    // En el caso que la clase contenga datos se eliminan
    if (this->numero_ciudades != -1){
        this->limpia();
    }

    // Declaración de variables:
    string cabecera;
    double x,y;
    string identificador_ciudad;
    vector<double> punto;

    // Inicia la lectura del archivo indicado por nombre_archivo. Si no existe se produce un error de ejecución:
    ifstream archivo(nombre_fichero.c_str());

    // Se lee el nombre del problema:
    archivo >> cabecera;
    archivo >> this->nombre_problema;

    // Dimensión del problema
    do{
        archivo >> cabecera;
    }while(cabecera != "DIMENSION:");

    archivo >> this->numero_ciudades;


    // Distancia óptima
    do{
        archivo >> cabecera;
    }while(cabecera != "OPTIMUM:" && cabecera != "NODE_COORD_SECTION");
    // Si se ha encontrado distancia óptima
    if (cabecera == "OPTIMUM:"){
        archivo >> this->distancia_optima;
    }
    // En otro caso
    else{
        this->distancia_optima = -1;
    }

    // Posiciones de cada ciudad
    do{
        archivo >> cabecera;
    }while(cabecera != "1");

    archivo >> x;
    archivo >> y;
    punto.push_back(x);
    punto.push_back(y);
    this->posiciones_ciudades.push_back(punto);
    punto.clear();

    // Lee las coordenadas de las ciudades:
    for (int i = 1; i < this->numero_ciudades; i++){
        archivo >> identificador_ciudad;
        archivo >> x;
        archivo >> y;
        punto.push_back(x);
        punto.push_back(y);
        this->posiciones_ciudades.push_back(punto);
        punto.clear();
    }

    // Se genera la matriz de distancias entre ciudades
    this->generaMatrizDistancias();
}

int DatosProblema::calculaDistancia(int ciudad_1, int ciudad_2){
    int x1 = this->posiciones_ciudades[ciudad_1][0], y1 = this->posiciones_ciudades[ciudad_1][1];
    int x2 = this->posiciones_ciudades[ciudad_2][0], y2 = this->posiciones_ciudades[ciudad_2][1];
    return nearbyint(sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)));
}

void DatosProblema::generaMatrizDistancias(){
    // Se reserva espacio es la matriz para poder acceder a todas las componentes
    for (int i=0; i<this->numero_ciudades; i++){
        this->distancias_ciudades.push_back(vector<int>());
        this->distancias_ciudades.back().resize(this->numero_ciudades);
    }

    // Como la matriz es simétrica, solo se calcula la mitad superior:
    for (int i = 0; i < this->numero_ciudades; i++){
        for (int j = i+1; j < this->numero_ciudades; j++){
            this->distancias_ciudades[i][j] = this->calculaDistancia(i,j);
            this->distancias_ciudades[j][i] = this->distancias_ciudades[i][j];
        }
        this->distancias_ciudades[i][i] = 0;
    }
}

void DatosProblema::limpia(){
    this->nombre_problema.clear();
    this->numero_ciudades = -1;
    this->posiciones_ciudades.clear();
    this->distancias_ciudades.clear();
    this->distancia_optima = -1;
}

