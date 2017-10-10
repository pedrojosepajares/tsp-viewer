#include "AlgoritmoSA.h"

SA::SA():HeuristicaTSP(){
    this->nombre_heuristica = "Enfriamiento simulado";
    vector<double> parametros;


    // Se leen los parámetros desde el fichero de configuración
    // y se ha leído el número correcto de parámetros
    if (this->leeFicheroConfiguracion(QApplication::applicationDirPath().toStdString()+"\\ficheros config\\sa.conf",parametros) && parametros.size() == 4){
        this->mi = parametros[0];
        this->sigma = parametros[1];
        this->max_vecinos = parametros[2];
        this->alpha = parametros[3];
    }

    // Si no se ha podido leer, se toman parámetros por defecto
    else{
        this->mi = 0.1;
        this->sigma = 0.1;
        this->max_vecinos = 100;
        this->alpha = 0.8;
    }
}

int SA::getCosteConIntercambio(Solucion solucion, int pos_1, int pos_2){
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

void SA::intercambia(vector<int> &v, int pos_1, int pos_2){
    int aux = v[pos_1];
    v[pos_1] = v[pos_2];
    v[pos_2] = aux;
}

Solucion SA::generaVecino(Solucion solucion, int pos1, int pos2, int coste_vecino){
    vector<int> ruta = solucion.getRuta();

    // Se intercambian las dos posiciones en la ruta de solucion
    this->intercambia(ruta, pos1, pos2);

    // Se devuelve el vecino con el nuevo coste
    return Solucion(ruta, coste_vecino);
}


vector<Solucion> SA::resolverCP(CriterioParada *criterio_parada, VentanaEspera *ventana_espera, int identificador_barra_progreso){
    VecinoMasCercano algoritmo_vmc;
    CriterioParada cp_vmc(60,0,1);
    int pos1, pos2, coste_vecino;

    Solucion mejor_solucion;
    Solucion vecino, solucion_candidata;
    vector<Solucion> mejores_soluciones;

    double temperatura, temperatura_inicial;


    //Número actual de vecinos generados
    int n_vecinos;

    // Número máximo de soluciones que pueden ser aceptadas en una iteración y número actual de soluciones
    // aceptadas
    int max_exitos = 0.1*(this->max_vecinos);
    int n_exitos = 1;

    // Mejora de la mejor_solucion con respecto al vecino
    int mejora_coste;

    // Si max_exitos es cero se pone a uno
    if (max_exitos == 0){
        max_exitos++;
    }

    // Se conecta con la ventana de espera indicando la barra de progreso que le corresponde
    this->conectaVentanaEspera(ventana_espera, identificador_barra_progreso);
    // Se pone la bandera de cancelación de ejecución a false
    this->ejecucion_cancelada = false;

    // Se calcula usando vmc
    algoritmo_vmc.setDistanciasCiudades(this->distancias_ciudades);
    mejor_solucion = algoritmo_vmc.resolverCP(&cp_vmc).back();
    criterio_parada->incrementaEvaluaciones();

    // Se calcula la temperatura inicial y final de forma que sean dependientes del problema
    temperatura = temperatura_inicial = (mi / -log(sigma)) * mejor_solucion.getCoste();

    // Mientras se sigan aceptando soluciones y no se cumpla el criterio de parada
    // El parámetro k se utiliza para la reducción de temperatura
    for (int k=1; n_exitos != 0 && !criterio_parada->cumplido(); k++){
        n_exitos = 0;
        // Se establece la solución candidata como la mejor solución
        solucion_candidata = mejor_solucion;

        // Mientras no se hayan generado max_vecinos y no se hayan alcanzado el máximo número
        // de éxitos
        for (n_vecinos = 0; n_exitos < max_exitos; n_vecinos++){

            // Se generan dos posiciones aleatorias distintas para realizar un intercambio
            pos1 = rand()%this->numero_ciudades;
            pos2 = rand()%this->numero_ciudades;
            while (pos1 == pos2){
                pos2 = rand()%this->numero_ciudades;
            }

            // Se calcula el coste del vecino calculado
            coste_vecino = this->getCosteConIntercambio(solucion_candidata, pos1, pos2);
            criterio_parada->incrementaEvaluaciones();

            //vecino = this->generaVecino(solucion_candidata);
            mejora_coste = coste_vecino - solucion_candidata.getCoste();

            // Si el vecino es mejor se acepta, también si es peor y de forma aleatoria
            // se decide aceptarlo
            if (mejora_coste < 0  || this->uniforme() <= exp(-mejora_coste/(k*temperatura))){
                solucion_candidata = this->generaVecino(solucion_candidata, pos1, pos2, coste_vecino);
                n_exitos++;
            }
        }

        // Se añade la solución si se ha mejorado
        if (mejores_soluciones.empty() || solucion_candidata < mejor_solucion){
            mejor_solucion = solucion_candidata;
            mejor_solucion.setTiempo(criterio_parada->getTiempo());
            mejor_solucion.setEvaluacion(criterio_parada->getEvaluaciones());
            mejor_solucion.setIteracion(criterio_parada->getIteraciones());
            mejores_soluciones.push_back(mejor_solucion);
        }

        // Enfriaminto de la temperatura según el criterio de Cauchy
        temperatura = alpha * temperatura;

        criterio_parada->incrementaIteraciones();
        // Se envía a la ventana de espera el nuevo valor del progreso
        emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);
    }

    emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);
    return mejores_soluciones;
}
