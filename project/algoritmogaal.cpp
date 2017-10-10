#include "algoritmogaal.h"

GAAL::GAAL():GA()
{
    this->nombre_heuristica = "Algoritmo genético con inicialización aleatoria ";
}

vector<Solucion> GAAL::resolverCP(CriterioParada *criterio_parada, VentanaEspera *ventana_espera, int identificador_barra_progreso){
    vector<Solucion> poblacion_actual;
    vector<Solucion> mejores_individuos;
    vector<Solucion>::iterator padre_1, padre_2;
    Solucion descendiente, mejor_individuo;
    vector<int> posiciones_mutar;
    int numero_mutados = ceil(this->numero_individuos_poblacion * this->probabilidad_mutacion);
    int indice_peor_individuo;

    // Se conecta con la ventana de espera indicando la barra de progreso que le corresponde
    this->conectaVentanaEspera(ventana_espera, identificador_barra_progreso);

    // Se pone la bandera de cancelación de ejecución a false
    this->ejecucion_cancelada = false;

    // Generación de la población inicial aleatoria
    for (int i=0; i<this->numero_individuos_poblacion; i++){
        poblacion_actual.push_back(this->generaSolucionAleatoria());
    }


    // Se incrementa el número de evaluaciones
    for (unsigned int i=0; i<poblacion_actual.size(); i++){
        criterio_parada->incrementaEvaluaciones();
    }


    // Bucle que controla la ejecución del algoritmo
    while (!criterio_parada->cumplido() && !this->ejecucion_cancelada){

        // Se guarda el mejor individuo
        mejor_individuo = this->getMejorIndividuoPoblacion(poblacion_actual);

        // Se selecciona el primer padre
        padre_1 = this->seleccionaPorTorneo(poblacion_actual);

        // Se selecciona al segundo padre
        padre_2 = this->seleccionaPorTorneo(poblacion_actual);

        // Se sustituye el peor individuo de la población por el descendiente, si éste es mejor
        indice_peor_individuo = this->getIndicePeorIndividuoPoblacion(poblacion_actual);

        descendiente = this->realizaCruce((*padre_1), (*padre_2));

        // Se incrementan las evaluaciones
        criterio_parada->incrementaEvaluaciones();

        this->mejoraLocal(descendiente);
        if (this->similitud(descendiente, *padre_1) > this->similitud(descendiente, *padre_2)){
            poblacion_actual.erase(padre_1);
        }
        else{
            poblacion_actual.erase(padre_2);
        }
        poblacion_actual.push_back(descendiente);


        // Mutación
        posiciones_mutar = this->generaAleatoriosDistintos(numero_mutados,this->numero_individuos_poblacion);
        for(int i=0; i<numero_mutados; i++){
            this->realizaMutacion(poblacion_actual[posiciones_mutar[i]]);
            criterio_parada->incrementaEvaluaciones();
        }

        // Se sustituye el peor individuo por el mejor calculado anteriormente
        indice_peor_individuo = this->getIndicePeorIndividuoPoblacion(poblacion_actual);
        poblacion_actual.push_back(mejor_individuo);


        // Se agrega el mejor individuo al vector de mejores individuos si es mejor el último presente o está vacío
        mejor_individuo = this->getMejorIndividuoPoblacion(poblacion_actual);
        if (mejores_individuos.empty() || mejor_individuo < mejores_individuos.back()){
            mejor_individuo.setTiempo(criterio_parada->getTiempo());
            mejor_individuo.setEvaluacion(criterio_parada->getEvaluaciones());
            mejor_individuo.setIteracion(criterio_parada->getIteraciones());
            mejores_individuos.push_back(mejor_individuo);
        }

        // Se incrementa el contador de iteraciones
        criterio_parada->incrementaIteraciones();

        // Se envía a la ventana de espera el nuevo valor del progreso
        emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);

    }
    emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);
    return mejores_individuos;
}
