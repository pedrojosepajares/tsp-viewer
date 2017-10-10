#include "AlgoritmoVecinoMasCercano.h"

VecinoMasCercano::VecinoMasCercano():HeuristicaTSP(){this->nombre_heuristica = "Vecino más cercano";}

vector<Solucion> VecinoMasCercano::resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera, int identificador_barra_progreso){
    vector<Solucion> mejores_soluciones;
    Solucion solucion;
    vector<int> ruta;
    vector<bool> visitadas;
    int coste = 0;
    int mejor_distancia, mejor_ciudad;

    // Se conecta con la ventana de espera indicando la barra de progreso que le corresponde
    this->conectaVentanaEspera(ventana_espera, identificador_barra_progreso);
    // Se pone la bandera de cancelación de ejecución a false
    this->ejecucion_cancelada = false;

    // Para cada una de las posibles ciudades por las que puede empezar la ruta
    for (int inicio=0; inicio<this->numero_ciudades && !criterio_parada->cumplido() && !this->ejecucion_cancelada; inicio++){

        // Se completa el vector de ciudades visitadas
        for (int j=0; j<this->numero_ciudades; j++){
            if (j!=inicio){
                visitadas.push_back(false);
            }
            else{
                visitadas.push_back(true);
            }
        }

        // Se añade la ciudad inicial a la ruta
        ruta.push_back(inicio);

        // Para cada espacio que queda por completar en la ruta
        for (int espacio=1; espacio<this->numero_ciudades; espacio++ ){

            // Se marca la distancia como no asignada
            mejor_distancia = -1;

            // Se busca la ciudad cuya distancia es menor a la última ciudad añadida a la ruta
            for (int ciudad=0; ciudad<this->numero_ciudades; ciudad++){
                // Si la ciudad todavía no ha sido visitada
                if (!visitadas[ciudad]){
                    // Si la distancia entre ciudad y la última ciudad recorrida es mejor
                    // o todavía no ha sido asignada
                    if (mejor_distancia == -1 || this->distancias_ciudades[ruta.back()][ciudad] < mejor_distancia){
                        mejor_distancia = this->distancias_ciudades[ruta.back()][ciudad];
                        mejor_ciudad = ciudad;
                    }
                }
            }

            // Se actualiza el coste
            coste += this->distancias_ciudades[ruta.back()][mejor_ciudad];

            // Se añade la mejor ciudad a la ruta
            ruta.push_back(mejor_ciudad);
            // Se actualizan las ciudades visitadas
            visitadas[mejor_ciudad] = true;

        }

        // Se añade la sulución al vector de soluciones en el caso de que esté vacío o sea mejor
        // que la anterior
        solucion = Solucion(ruta, coste);

        criterio_parada->incrementaEvaluaciones();

        if (mejores_soluciones.empty() || mejores_soluciones.back() > solucion){
            solucion.setTiempo(criterio_parada->getTiempo());
            solucion.setIteracion(criterio_parada->getIteraciones());
            solucion.setEvaluacion(criterio_parada->getEvaluaciones());
            mejores_soluciones.push_back(solucion);
        }


        // Se limpian las estructuras
        ruta.clear();
        visitadas.clear();
        coste = 0;

        criterio_parada->incrementaIteraciones();

        // Se envía a la ventana de espera el nuevo valor del progreso
        emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);
    }

    emit incrementoProgresoAlgoritmo(100, identificador_barra_progreso);
    return mejores_soluciones;
}

