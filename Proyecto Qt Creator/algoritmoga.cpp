#include "AlgoritmoGA.h"

GA::GA():HeuristicaTSP(){
    this->nombre_heuristica = "Algoritmo genético";

    vector<double> parametros;


    // Se leen los parámetros desde el fichero de configuración
    // y se ha leído el número correcto de parámetros
    if (this->leeFicheroConfiguracion(QApplication::applicationDirPath().toStdString()+"\\ficheros config\\ga.conf",parametros) && parametros.size() >= 6){
        this->probabilidad_mutacion = parametros[0];
        this->numero_individuos_poblacion = parametros[1];
        this->numero_candidatos_torneo = parametros[2];
        this->tiempo_grasp = parametros[3];
        this->evaluaciones_grasp = parametros[4];
        this->iteraciones_grasp = parametros[5];
    }

    // Si no se ha podido leer, se toman parámetros por defecto
    else{
        this->probabilidad_mutacion = 0.1;
        this->numero_individuos_poblacion = 8;
        this->numero_candidatos_torneo = 2;
        this->tiempo_grasp = 0;
        this->evaluaciones_grasp = 20;
        this->iteraciones_grasp = 0;
    }
}

vector<Solucion> GA::generaPoblacionGRASP(){
    GRASP algoritmo_grasp(this->distancias_ciudades);
    vector<Solucion> poblacion;
    CriterioParada* cp_grasp;

    for(int i=0; i<this->numero_individuos_poblacion; i++){
        cp_grasp = new CriterioParada(this->tiempo_grasp, this->evaluaciones_grasp, this->iteraciones_grasp);
        poblacion.push_back(algoritmo_grasp.resolverCP(cp_grasp).back());
        delete cp_grasp;
    }
    return poblacion;
}
vector<Solucion>::iterator GA::seleccionaPorTorneo(vector<Solucion>& poblacion){
    // Se generan las posiciones de competidores
    vector<int> aleatorios_distintos = this->generaAleatoriosDistintos(this->numero_candidatos_torneo, this->numero_individuos_poblacion);
    vector<Solucion>::iterator mejor_solucion = poblacion.begin()+ aleatorios_distintos[0];

    vector<Solucion>::iterator solucion_candidata;

    for (int i=1; i<this->numero_candidatos_torneo; i++){
        solucion_candidata = poblacion.begin() + aleatorios_distintos[i];

        if (*solucion_candidata < *mejor_solucion){
            mejor_solucion = solucion_candidata;
        }
    }
    return mejor_solucion;
}

Solucion GA::realizaCruce(Solucion padre_1, Solucion padre_2){
    vector<int> ruta_hijo;
    vector<int> ruta_padre_1 = padre_1.getRuta();
    vector<int> ruta_padre_2 = padre_2.getRuta();
    vector<bool> ciudades_visitadas_hijo;
    int inicio_cadena = rand()%this->numero_ciudades;
    int tam_cadena = (rand()%(this->numero_ciudades-1))+1;
    int pos_en_padre_2 =-1;


    // Se inicializa el vector de ciudades visitadas en el hijo
    for (int i=0; i<this->numero_ciudades; i++){
        ciudades_visitadas_hijo.push_back(false);
    }


    // Se selecciona una cadena desde una posicion y tamaño aleatorios y se incluye en el hijo
    for (int i=0; i<tam_cadena; i++){
        ruta_hijo.push_back(ruta_padre_1[(inicio_cadena+i)%this->numero_ciudades]);
        ciudades_visitadas_hijo[ruta_hijo.back()] = true;
    }



    // Se busca en padre_2 el último elemento de ruta_hijo
    for (int i=0; i<this->numero_ciudades && pos_en_padre_2 == -1; i++){
        if (ruta_padre_2[i] == ruta_hijo.back()){
            pos_en_padre_2 = i;
        }
    }



    // Se completa ruta_hijo con los elementos de padre_2 ignorando los que ya existen
    for (unsigned int i=0; (int)i<this->numero_ciudades && (int)ruta_hijo.size()<this->numero_ciudades; i++){
        if (!ciudades_visitadas_hijo[ruta_padre_2[(pos_en_padre_2+i)%this->numero_ciudades]]){
            ruta_hijo.push_back(ruta_padre_2[(pos_en_padre_2+i)%this->numero_ciudades]);
        }
    }

    return Solucion(ruta_hijo,this->getCoste(ruta_hijo));

}

int GA::getCosteConIntercambio(Solucion solucion, int pos_1, int pos_2){
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

void GA::intercambia(vector<int> &v, int pos_1, int pos_2){
    int aux = v[pos_1];
    v[pos_1] = v[pos_2];
    v[pos_2] = aux;
}

void GA::realizaMutacion(Solucion &individuo){
    vector<int> nueva_ruta = individuo.getRuta();
    int i = rand() % this->numero_ciudades;
    int j = (i + (1 + rand() % (this->numero_ciudades-1))) % this->numero_ciudades; // j != i
    int nuevo_coste = this->getCosteConIntercambio(individuo,i,j);
    this->intercambia(nueva_ruta,i,j);
    individuo = Solucion(nueva_ruta, nuevo_coste);
}

Solucion GA::getMejorIndividuoPoblacion(vector<Solucion> poblacion){
    vector<Solucion> poblacion_ordenada(poblacion);
    sort(poblacion_ordenada.begin(), poblacion_ordenada.end(), Solucion::menorQue);
    return poblacion_ordenada.front();
}

int GA::getIndicePeorIndividuoPoblacion(vector<Solucion> poblacion){
    int indice = -1;
    int peor_coste;

    for (int i=0; i<this->numero_individuos_poblacion; i++){
        if(poblacion[i].getCoste() > peor_coste || indice == -1){
            indice = i;
            peor_coste = poblacion[i].getCoste();
        }
    }
    return indice;
}

int GA::similitud(Solucion s1, Solucion s2){
    int similitud = 0;
    bool encontrada;
    int posicion_s2;
    // Para cada arco de s1
    for (int i=0; i<this->numero_ciudades; i++){

        encontrada = false;
        // Se localiza la ciudad en s2
        for (int j=0; j<this->numero_ciudades && !encontrada; j++){
            if (s1.getRuta()[i] == s2.getRuta()[j]){
                encontrada = true;
                posicion_s2 = j;
            }
        }

        // Se comprueba si están conectadas
        // Por delante
        if (s1.getRuta()[i] == s2.getRuta()[(posicion_s2+1)%this->numero_ciudades]){
            similitud++;
        }

        // Por detrás
        else if (s1.getRuta()[i] == s2.getRuta()[((posicion_s2-1)+this->numero_ciudades)%this->numero_ciudades]){
            similitud++;
        }
    }

    return similitud;
}

vector<Solucion> GA::resolverCP(CriterioParada *criterio_parada, VentanaEspera *ventana_espera, int identificador_barra_progreso){
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

    // Generación de la población inicial. Se generan individuos mediante GRASP
    poblacion_actual = this->generaPoblacionGRASP();


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
