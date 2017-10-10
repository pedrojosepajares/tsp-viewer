#include "AlgoritmoACO.h"

MapaFeromonas::MapaFeromonas(vector<vector<int> >* distancias, double porcentaje_evaporacion){
    vector<double> vector_auxiliar;

    this->distancias = distancias;
    this->rho = porcentaje_evaporacion;



    // Se reserva el espacio para la matriz de feromonas
    this->feromonas.resize(this->distancias->size());
    for (unsigned int i=0; i<this->feromonas.size(); i++){
        this->feromonas.at(i).resize(this->distancias->size());
    }
    // Como la matriz es simétrica, solo se calcula la mitad superior:
    for (unsigned int i = 0; i < this->distancias->size(); i++){
        for (unsigned int j = i+1; j < this->distancias->size(); j++){
            this->feromonas[i][j] = 1.0 / this->distancias->at(i).at(j);
            this->feromonas[j][i] = this->feromonas[i][j];
        }
        this->feromonas[i][i] = 0;
    }
}

void MapaFeromonas::actualizar(vector<Solucion>* hormigas){
    // Arcos
    int r,s;

    // Incremento de la feromona
    double incremento;

    // Se evaporan feromonas de todo el mapa según el parámentro de evaporación
    for (unsigned int i=0; i<this->feromonas.size(); i++){
        for (unsigned j=0; j<this->feromonas.size(); j++){
            this->feromonas[i][j] *= (1-this->rho);

            // El valor de las feromonas siempre debe superar un valor umbral
            if (this->feromonas[i][j] < 1E-10 && i != j){
                this->feromonas[i][j] = 1E-10;
            }
        }
    }

    // Se añade un aporte de feromonas en los arcos que han sido visitados
    // Para cada hormiga
    for (unsigned int h=0; h<hormigas->size(); h++){
        // Para cada arco de la solución
        for (unsigned int i=0; i<hormigas->at(h).getRuta().size(); i++){
            r = hormigas->at(h).getRuta()[i];
            s = hormigas->at(h).getRuta()[(i+1)%hormigas->at(0).getRuta().size()];
            incremento = 1.0 / hormigas->at(h).getCoste();
            // Se añade a las feromonas
            this->feromonas[r][s] += incremento;
            this->feromonas[s][r] = this->feromonas[r][s];

        }
    }
}

MapaProbabilidades::MapaProbabilidades(double alpha, double beta){
    this->alpha = alpha;
    this->beta = beta;
}

void MapaProbabilidades::actualizar(MapaFeromonas* mapa_feromonas, vector<vector<int> >* distancias){
    // Si el mapa de probabiliades se encuentra vacío se reserva memoria para alojarlo
    if (this->probabilidades.empty()){
        this->probabilidades.resize(distancias->size());
        for (unsigned int i=0; i<this->probabilidades.size(); i++){
            this->probabilidades.at(i).resize(distancias->size());
        }
    }

    // Se completa la tabla
    // Como la matriz es simétrica, solo se calcula la mitad superior:
    for (unsigned int i = 0; i < distancias->size(); i++){
        for (unsigned int j = i+1; j < distancias->size(); j++){
            this->probabilidades[i][j] = pow(mapa_feromonas->at(i,j), this->alpha) * pow(1.0 / distancias->at(i).at(j), this->beta);
            this->probabilidades[j][i] = this->probabilidades[i][j];
        }
        this->probabilidades[i][i] = -1;
    }

}

double MapaProbabilidades::at(int r, int s, vector<bool>* visitadas){
    double suma = 0;

    // Para cada ciudad no visitada
    for (unsigned int u=0; u<visitadas->size(); u++){
        if (!visitadas->at(u)){
            suma += this->probabilidades[r][u];
        }
    }
    return this->probabilidades[r][s] / suma;
}

int MapaProbabilidades::siguienteCiudad(int ultima_visitada, vector<bool>* visitadas){
    // Vector con las ciuades restantes por visitar
    vector<int> ciudades_restantes;

    // Vector que contiene las probabilidades de ser visitada de cada ciudad en el vector de
    // ciudades_restantes
    vector<double> probabilidades_ciudades_restantes;

    // Suma de todas las probabilidades. Se utiliza para hacer el cálculo de la ciudade elegida
    double probabilidad_total = 0;

    double probabilidad_aleatoria;

    int indice_ciudad_elegida = -1;


    // Se completa el vector de ciudades restantes y de probabilidades_ciuades_restantes
    for (unsigned int i=0; i<visitadas->size(); i++){
        if (!visitadas->at(i)){
            ciudades_restantes.push_back(i);
            probabilidades_ciudades_restantes.push_back(this->at(ultima_visitada, i, visitadas));
            probabilidad_total += probabilidades_ciudades_restantes.back();
        }
    }

    // Se ha el cálculo de la probabilidad aleatoria distinta de uno
    probabilidad_aleatoria = (rand() / static_cast<float>(RAND_MAX));
    while (probabilidad_aleatoria == 1){
        probabilidad_aleatoria = (rand() / static_cast<float>(RAND_MAX));

    }

    // Se calcula la ciudad elegida
    for (unsigned int i=0; i<ciudades_restantes.size() && indice_ciudad_elegida == -1; i++){
        probabilidad_aleatoria -= probabilidades_ciudades_restantes[i];

        if (probabilidad_aleatoria <= 0){
            indice_ciudad_elegida = ciudades_restantes[i];
        }
    }
    return indice_ciudad_elegida;
}

ACO::ACO():HeuristicaTSP(){
    bool alpha_correcto = false;
    bool beta_correcto = false;
    bool n_hormigas_correcto = false;
    vector<double> parametros;

    this->nombre_heuristica = "Algoritmo basado en colonias de hormigas";

    // Parámetros por defecto
    this->alpha = 0.6;
    this->beta = 0.4;
    this->n_hormigas = 10;


    // Se leen los parámetros desde el fichero de configuración
    // y se ha leído el número correcto de parámetros
    if (this->leeFicheroConfiguracion(QApplication::applicationDirPath().toStdString() + "\\ficheros config\\aco.conf",parametros) && parametros.size() == 3){
        // alpha y bea tienen que estar en el intervalo [0,1] y alpha+beta = 1
        alpha_correcto = parametros[0] >= 0;
        beta_correcto = parametros[1] >= 0;
        n_hormigas_correcto = parametros[2] > 0;

        // Si todos los parametros son correctos
        if (alpha_correcto && beta_correcto && n_hormigas_correcto){
            this->alpha = parametros[0];
            this->beta = parametros[1];
            this->n_hormigas = parametros[2];
        }
    }
}

Solucion ACO::getMejorSolucion(vector<Solucion> poblacion){
    vector<Solucion> poblacion_ordenada(poblacion);
    sort(poblacion_ordenada.begin(), poblacion_ordenada.end(), Solucion::menorQue);
    return poblacion_ordenada.front();
}

vector<Solucion> ACO::resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera, int identificador_barra_progreso){
    // Se genera un nuevo mapa de feromonas y se inicializan los valores iniciales como
    // 1 / d[i][j]
    MapaFeromonas mapa_feromonas(&(this->distancias_ciudades), 0.01);

    // Se genera el mapa de probabilidades
    MapaProbabilidades mapa_probabilidades(this->alpha, this->beta);

    // Vector de soluciones que se devolverán
    vector<Solucion> mejores_soluciones;

    // Hormigas
    vector<Solucion> hormigas;

    // Ciudades visitadas por cada hormiga;
    vector<vector<bool> > ciudades_visitadas;
    ciudades_visitadas.resize(this->n_hormigas);
    for (unsigned int i=0; i<ciudades_visitadas.size(); i++){
        ciudades_visitadas[i].resize(this->numero_ciudades);
    }

    // Vector auxiliar para hacer los cálculos de las rutas
    vector<int> ruta_aux;

    // Siguiente ciudad que será visitada
    int siguiente_ciudad;

    // Se conecta con la ventana de espera indicando la barra de progreso que le corresponde
    this->conectaVentanaEspera(ventana_espera, identificador_barra_progreso);
    // Se pone la bandera de cancelación de ejecución a false
    this->ejecucion_cancelada = false;

    // Mientras no se cumpla el criterio de parada y mientras no se haya cancelado la ejecución
    while(!criterio_parada->cumplido() && !this->ejecucion_cancelada){

        // Se actualiza el mapa de probabilidades
        mapa_probabilidades.actualizar(&mapa_feromonas, &(this->distancias_ciudades));

        // Se marcan todas las ciudades a no visitadas
        for (unsigned int i=0; i<ciudades_visitadas.size(); i++){
            for (unsigned int j=0; j<ciudades_visitadas[0].size(); j++){
                ciudades_visitadas[i][j] = false;
            }
        }

        // Para cada hormiga
        for (int i=0; i<this->n_hormigas; i++){
            // Cada hormiga recorre una primera ciudad aleatoria
            // Se calcula la ciudad aleatoria
            ruta_aux.push_back(rand()%this->numero_ciudades);
            // Se actualizan las ciudades visitadas
            ciudades_visitadas[i][ruta_aux.back()] = true;

            // Cada hormiga completa su recorrido
            for (int pos = 1; pos<this->numero_ciudades; pos++){
                // Se calcula la siguiente ciudad en base a su probabilidad de ser visitada con
                // respecto a la última ciudad visitada
                siguiente_ciudad = mapa_probabilidades.siguienteCiudad(ruta_aux.back(), &ciudades_visitadas[i]);

                // Se actualizan las ciudades visitadas con la nueva ciudad
                ciudades_visitadas[i][siguiente_ciudad] = true;

                // Se añade la nueva ciudad a la ruta
                ruta_aux.push_back(siguiente_ciudad);
            }

            // Se añade la solución a la hormiga con su coste
            hormigas.push_back(Solucion(ruta_aux, this->getCoste(ruta_aux)));

            // Se le aplica una mejora local
            mejoraLocal(hormigas.back());

            // Se limpia la ruta para la siguiente hormiga
            ruta_aux.clear();
        }

        // Se ordenan por el coste de la solución las hormigas
        sort(hormigas.begin(), hormigas.end(), Solucion::menorQue);



        // Se actualizan las feromonas utlizando la mejor hormiga
        vector<Solucion> mejores_hormigas(hormigas.begin(), hormigas.begin()+(this->n_hormigas/2));
        mapa_feromonas.actualizar(&mejores_hormigas);

        // Incremento de n_hormigas del número de evaluaciones en el criterio de parada
        criterio_parada->incrementaEvaluaciones(this->n_hormigas);



        // Incremento de las iteraciones
        criterio_parada->incrementaIteraciones();

        // Si está vacío el vector de mejores soluciones o la solución encontrada es mejor que la anterior
        if(mejores_soluciones.empty() || hormigas.front() < mejores_soluciones.back()){

            // Se añaden los valores relacionados con el criterio de parada a la hormiga
            hormigas.front().setTiempo(criterio_parada->getTiempo());
            hormigas.front().setIteracion(criterio_parada->getIteraciones());
            hormigas.front().setEvaluacion(criterio_parada->getEvaluaciones());

            // Se añade la que tiene un menor coste al vector de mejores soluciones
            mejores_soluciones.push_back(hormigas.front());
        }

        // Se limpian las soluciones de las hormigas
        hormigas.clear();

        // Se envía a la ventana de espera el nuevo valor del progreso
        emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);

    }
    emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);
    return mejores_soluciones;
}

