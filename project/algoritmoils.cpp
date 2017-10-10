#include "AlgoritmoILS.h"

ILS::ILS():HeuristicaTSP(){
    this->nombre_heuristica = "Búsqueda local iterativa";

    vector<double> parametros;

    // Se leen los parámetros desde el fichero de configuración
    // y se ha leído el número correcto de parámetros
    if (this->leeFicheroConfiguracion(QApplication::applicationDirPath().toStdString()+"\\ficheros config\\ils.conf",parametros) && parametros.size() >= 5){
        this->mi = parametros[0];
        this->lambda = parametros[1];
        this->tiempo_grasp = parametros[2];
        this->evaluaciones_grasp = parametros[3];
        this->iteraciones_grasp = parametros[4];
    }

    // Si no se ha podido leer, se toman parámetros por defecto
    else{
        this->mi = 5;
        this->lambda = 2*this->mi;
        this->tiempo_grasp = 5;
        this->evaluaciones_grasp = this->iteraciones_grasp = 0;
    }

}

void ILS::intercambia(vector<int> &v, int pos_1, int pos_2){
    int aux = v[pos_1];
    v[pos_1] = v[pos_2];
    v[pos_2] = aux;
}

int ILS::getCosteConIntercambio(Solucion solucion, int pos_1, int pos_2){
    int posible_coste = solucion.getCoste();
    vector<int> ruta = solucion.getRuta();
    int separacion_pos1_pos2 = abs(pos_1-pos_2);

    // Posiciones de las ciudades contiguas a las dos dadas:
    int pos_1_dcha = (pos_1 + 1) % this->numero_ciudades;
    int pos_1_izda = (pos_1 - 1 + this->numero_ciudades)  % this->numero_ciudades;
    int pos_2_dcha = (pos_2 + 1) % this->numero_ciudades;
    int pos_2_izda = (pos_2 - 1 + this->numero_ciudades)  %this->numero_ciudades;

    // Se restan las distancias de los lados que se eliminan (los que tienen como vértices a las ciudades a intercambiar):
    posible_coste -= (this->distancias_ciudades[ruta[pos_1]][ruta[pos_1_izda]]
                + this->distancias_ciudades[ruta[pos_1]][ruta[pos_1_dcha]]
                + this->distancias_ciudades[ruta[pos_2]][ruta[pos_2_izda]]
                + this->distancias_ciudades[ruta[pos_2]][ruta[pos_2_dcha]]);

    // Se suman las distancias de los nuevos lados:
    posible_coste += (this->distancias_ciudades[ruta[pos_1]][ruta[pos_2_izda]]
                + this->distancias_ciudades[ruta[pos_1]][ruta[pos_2_dcha]]
                + this->distancias_ciudades[ruta[pos_2]][ruta[pos_1_izda]]
                + this->distancias_ciudades[ruta[pos_2]][ruta[pos_1_dcha]]);

    /* Si la separación en orden_ciudades de ambas ciudades es 1 (num_visitadas - 1 en caso de ser la primera y la última ciudad)
        se ha restado dos veces la distancia entre ellas y se ha sumado 0 dos veces (la distancia entre una ciudad y ella misma).
        Por ello debemos sumar de nuevo la distancia entre ambas ciudades 2 veces: */
    if (separacion_pos1_pos2 == 1 || separacion_pos1_pos2 == this->numero_ciudades - 1){
        posible_coste += 2*this->distancias_ciudades[ruta[pos_1]][ruta[pos_2]];
    }

    return posible_coste;
}

void ILS::realizaMutacion(Solucion &individuo){
    vector<int> nueva_ruta = individuo.getRuta();
    int i = rand() % this->numero_ciudades;
    int j = (i + (1 + rand() % (this->numero_ciudades-1))) % this->numero_ciudades; // j != i
    int nuevo_coste = this->getCosteConIntercambio(individuo,i,j);
    this->intercambia(nueva_ruta,i,j);
    individuo = Solucion(nueva_ruta, nuevo_coste);
}

vector<Solucion> ILS::resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera, int identificador_barra_progreso){
    GRASP algoritmo_grasp(this->distancias_ciudades);
    CriterioParada* cp_grasp;
    vector<Solucion> poblacion_padres, poblacion_hijos;
    vector<Solucion> soluciones_grasp;
    vector<Solucion> mejores_soluciones;
    Solucion solucion_mutada, mejor_solucion;

    // Se conecta con la ventana de espera indicando la barra de progreso que le corresponde
    this->conectaVentanaEspera(ventana_espera, identificador_barra_progreso);
    // Se pone la bandera de cancelación de ejecución a false
    this->ejecucion_cancelada = false;

    // Se genera una población inicial utlizando el algoritmo grasp, de mi individuos
    for (int i=0; i<this->mi; i++){
        cp_grasp = new CriterioParada(this->tiempo_grasp, this->evaluaciones_grasp, this->iteraciones_grasp);
        soluciones_grasp = algoritmo_grasp.resolverCP(cp_grasp);
        poblacion_padres.push_back(soluciones_grasp.back());
        delete cp_grasp;
    }

    // Mientras no se cumpla el criterio de parada y  no se cancele la ejecuión
    while (!criterio_parada->cumplido() && !this->ejecucion_cancelada){
        // Se generan lambda hijos mediante mutación a partir de la población de padres;
        // Se aplica a cada uno de ellos una búsqueda local
        for (int i=0; i<this->mi; i++){
            for (int j=0; j<this->lambda; j++){
                solucion_mutada = poblacion_padres[i];
                this->realizaMutacion(solucion_mutada);
                this->mejoraLocal(solucion_mutada);
                criterio_parada->incrementaEvaluaciones();
                poblacion_hijos.push_back(solucion_mutada);
            }
        }

        // Se ordenan las soluciones y las mi mejores se convierten en la población de padres
        sort(poblacion_hijos.begin(), poblacion_hijos.end(), Solucion::menorQue);
        poblacion_padres.clear();
        for (int i=0; i<this->mi; i++){
            poblacion_padres.push_back(poblacion_hijos[i]);
        }
        poblacion_hijos.clear();

        // Se añade la mejor solución obtenida hasta ahora si es mejor que la anterior
        mejor_solucion =  poblacion_padres.front();
        if (mejores_soluciones.empty() || mejor_solucion < mejores_soluciones.back()){
            mejor_solucion.setTiempo(criterio_parada->getTiempo());
            mejor_solucion.setEvaluacion(criterio_parada->getEvaluaciones());
            mejor_solucion.setIteracion(criterio_parada->getIteraciones());
            mejores_soluciones.push_back(mejor_solucion);
        }

        criterio_parada->incrementaIteraciones();

        // Se envía a la ventana de espera el nuevo valor del progreso
        emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);

    }
    return mejores_soluciones;
}
