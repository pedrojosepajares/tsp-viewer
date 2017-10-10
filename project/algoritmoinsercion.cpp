#include "AlgoritmoInsercion.h"

Insercion::Insercion():HeuristicaTSP(){this->nombre_heuristica = "Inserción";}


int Insercion::getCosteAlRealizarInsercion(const vector<int> ruta, const int ciudad, const int posicion_insercion){
    int nuevo_coste = this->getCoste(ruta);
    int ciudad_desplazada = ruta[posicion_insercion];
    int ciudad_anterior = ruta[(posicion_insercion+ruta.size()-1)%ruta.size()];


    nuevo_coste -= this->distancias_ciudades[ciudad_anterior][ciudad_desplazada];
    nuevo_coste += this->distancias_ciudades[ciudad_anterior][ciudad];
    nuevo_coste += this->distancias_ciudades[ciudad][ciudad_desplazada];

    return nuevo_coste;
}

vector<Solucion> Insercion::resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera, int identificador_barra_progreso){
    Solucion solucion_candidata;
    vector<Solucion> mejores_soluciones;
    vector<int> ruta;
    vector<bool> visitadas;
    int mejor_ciudad, mejor_posicion, coste_candidato ,mejor_coste;

    // Se conecta con la ventana de espera indicando la barra de progreso que le corresponde
    this->conectaVentanaEspera(ventana_espera, identificador_barra_progreso);
    // Se pone la bandera de cancelación de ejecución a false
    this->ejecucion_cancelada = false;

        // Para cada ciudad
        for (int i=0; i<this->numero_ciudades && !criterio_parada->cumplido() && !this->ejecucion_cancelada ; i++ ){
            // Se completa el vector de ciudades visitadas
            for (int j=0; j<this->numero_ciudades; j++){
                if (j!=i){
                    visitadas.push_back(false);
                }
                else{
                    visitadas.push_back(true);
                }
            }

            // Se inicia la ruta en la ciudad i
            ruta.push_back(i);
            // Para cada uno de las posiciones que quedarían por llenar
            for (int espacio = 1; espacio<this->numero_ciudades; espacio++){
                // Se reinicia el mejor coste
                mejor_coste = -1;

                // Para cada posible ciudad que se puede insertar
                for (int ciudad=0; ciudad<this->numero_ciudades; ciudad++){
                    // Si la ciudad no ha sido visitada aún
                    if(!visitadas[ciudad]){
                        // Para cada posición que podría ocupar la ciudad
                        for (unsigned int pos=0; pos<ruta.size(); pos++){

                            // Se calcula el coste de insertar ciudad en pos dentro de ruta
                            coste_candidato = this->getCosteAlRealizarInsercion(ruta, ciudad, pos);

                            //Si el coste calculado es mejor que el mejor coste o el mejor coste no ha sido
                            // inicializado
                            if(coste_candidato < mejor_coste || mejor_coste == -1){
                                mejor_coste = coste_candidato;
                                mejor_ciudad = ciudad;
                                mejor_posicion = pos;
                            }
                        }
                    }
                }

                // Se inserta la mejor ciudad en la mejor posicion dentro de la ruta
                ruta.insert(ruta.begin()+mejor_posicion,mejor_ciudad);

                // Se marca la ciudad como visitada
                visitadas[mejor_ciudad] = true;

            }

            // Se genera la nueva solución
            solucion_candidata = Solucion(ruta, mejor_coste);
            // Se limpia la ruta
            ruta.clear();
            // Se limpia el vector de ciudades visitadas
            visitadas.clear();

            criterio_parada->incrementaEvaluaciones();

            // Si la solución candidata es mejor que la mejor solución se sustituye
            if (mejores_soluciones.empty() || solucion_candidata < mejores_soluciones.back()){
                solucion_candidata.setTiempo(criterio_parada->getTiempo());
                solucion_candidata.setEvaluacion(criterio_parada->getEvaluaciones());
                solucion_candidata.setIteracion(criterio_parada->getIteraciones());
                mejores_soluciones.push_back(solucion_candidata);
            }

            criterio_parada->incrementaIteraciones();

            // Se envía a la ventana de espera el nuevo valor del progreso
            emit incrementoProgresoAlgoritmo((criterio_parada->getIteraciones()/(float)this->numero_ciudades)*100.0,identificador_barra_progreso);
        }

    emit incrementoProgresoAlgoritmo(100.0,identificador_barra_progreso);
    return mejores_soluciones;
}

