#include "algoritmosaal.h"

SAAL::SAAL():SA(){
    this->nombre_heuristica = "Enfriaminto simulado con inicialización aleatoria";
}

vector<Solucion> SAAL::resolverCP(CriterioParada *criterio_parada, VentanaEspera *ventana_espera, int identificador_barra_progreso){
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

    mejor_solucion = this->generaSolucionAleatoria();
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
