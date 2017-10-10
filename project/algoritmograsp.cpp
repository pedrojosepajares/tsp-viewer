#include "AlgoritmoGRASP.h"

GRASP::GRASP():HeuristicaTSP(){
    this->nombre_heuristica = "Greedy aleatorizado";

    vector<double> parametros;


    // Se leen los parámetros desde el fichero de configuración
    // y se ha leído el número correcto de parámetros
    if (this->leeFicheroConfiguracion(QApplication::applicationDirPath().toStdString()+"\\ficheros config\\grasp.conf",parametros) && parametros.size() == 1){
        this->tam_lrc = parametros[0];
    }

    // Si no se ha podido leer, se toman parámetros por defecto
    else{
        this->tam_lrc = 3;
    }

}

GRASP::GRASP(vector<vector<int> > distancias_ciudades):HeuristicaTSP(distancias_ciudades){
    this->nombre_heuristica = "GRASP";
    this->tam_lrc = 3;

    // Se reinicia la semilla aleatoria
    time_t t;
    srand((unsigned)time(&t));
}

vector<int> GRASP::generaRutaGreedy(){
    vector<int> ruta;
    vector<bool> ciudades_visitadas;
    int distancia_candidata, mejor_distancia;
    int primera_no_visitada;
    int mejor_ciudad;


    // Se inicializa a false el vector de ciudades_visitadas
    for (int i=0; i<this->numero_ciudades; i++){
        ciudades_visitadas.push_back(false);
    }

    // La ciudad inicial del recorrido se calcula de forma aleatoria
    ruta.push_back(rand()%this->numero_ciudades);
    ciudades_visitadas[ruta[0]] = true;

    // De entre las ciudades no recorridas, se añade a la ruta la más cercana
    // a la última ciudad visitada
    for (int i=1; i<this->numero_ciudades; i++){
        // Se busca la primera ciudad no visitada y se almacena la distancia
        // a la última ciudad del recorrido
        mejor_distancia = -1;
        for (unsigned int j=0; j<ciudades_visitadas.size() && mejor_distancia == -1; j++){
            if(ciudades_visitadas[j]==false){
                mejor_distancia = this->distancias_ciudades[ruta[ruta.size()-1]][j];
                primera_no_visitada = j;
                mejor_ciudad = primera_no_visitada;
            }
        }

        // Se buscan el resto de ciudades no visitadas a partir de la primera no visitada
        // y se comprueba si la distancia a la última ciudad de la ruta es menor que la
        // mejor. Si ese es el caso, se sustituyen
        for(unsigned int j=primera_no_visitada+1; j<ciudades_visitadas.size(); j++){
            //Si la ciudad no ha sido visitada
            if (ciudades_visitadas[j] == false){
                // Si  la ciudad j es mejor que mejor_ciudad
                distancia_candidata = this->distancias_ciudades[ruta[ruta.size()-1]][j];
                if (distancia_candidata < mejor_distancia){
                    mejor_distancia = this->distancias_ciudades[ruta[ruta.size()-1]][j];
                    mejor_ciudad = j;
                }
            }
        }

        // Se añade a la ruta la mejor ciudad y se actualiza el vector de ciudades_visitadas
        ruta.push_back(mejor_ciudad);
        ciudades_visitadas[mejor_ciudad] = true;
    }

    return ruta;
}

vector<int> GRASP::generaLRC(vector<bool>& ciudades_visistadas, int ultima_ciudad){

    // Vectores de distancias a la ultima ciudad
    vector<CiudadDistancia> distancias;
    CiudadDistancia distancia_auxiliar;

    // Lista que se devolverá
    vector<int> lrc;

    // Se inicaiza el vector de distancias
    for (int i=0; i<this->numero_ciudades; i++){
        // Si la ciudad no ha sido visitada
        if (!ciudades_visistadas[i]){
            distancia_auxiliar.ciudad = i;
            distancia_auxiliar.distancia = this->distancias_ciudades[ultima_ciudad][i];
            distancias.push_back(distancia_auxiliar);
        }
    }

    // Se ordena el vector de distancias
    sort(distancias.begin(), distancias.end(), CiudadDistancia::menorQue);

    // Se van agreganado elementos hasta que no quedan más o se llene lrc
    for (vector<CiudadDistancia>::iterator it = distancias.begin(); it!=distancias.end() && (int)lrc.size() < this->tam_lrc ; it++){

        lrc.push_back((*it).ciudad);
    }

    return lrc;
}

Solucion GRASP::generaSolucionGreedy(){
    vector<int> lrc;
    vector<int> ruta;
    vector<bool> ciudades_visitadas;
    int ciudad_aleatoria;

    // Se inicializa el vector de ciudades visitadas
    for (int i=0; i<this->numero_ciudades; i++){
        ciudades_visitadas.push_back(false);
    }

    // Se añade una primera ciudad aleatoria a la solución
    ciudad_aleatoria = rand()%this->numero_ciudades;
    ciudades_visitadas[ciudad_aleatoria] = true;
    ruta.push_back(ciudad_aleatoria);

    // Para cada ciudad añadida a la solución
    for (int i=1; i<this->numero_ciudades; i++){

        // Se genera la lista reducida de candidatos;
        lrc = this->generaLRC(ciudades_visitadas, ruta[ruta.size()-1]);

        // Se inserta una ciudad aleatoria de la LRC en la solucion
        ciudad_aleatoria = lrc[rand()%lrc.size()];
        ciudades_visitadas[ciudad_aleatoria] = true;
        ruta.push_back(ciudad_aleatoria);
    }

    return Solucion(ruta, this->getCoste(ruta));
}

vector<Solucion> GRASP::resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera, int identificador_barra_progreso){
    vector<Solucion> soluciones;
    Solucion solucion;

    // Se conecta con la ventana de espera indicando la barra de progreso que le corresponde
    this->conectaVentanaEspera(ventana_espera, identificador_barra_progreso);
    // Se pone la bandera de cancelación de ejecución a false
    this->ejecucion_cancelada = false;

    // Mientras no se cumpla el criterio de o la ejecución no haya sido cancelada
    while(!criterio_parada->cumplido() && !this->ejecucion_cancelada){

        // Se genera un solución greedy
        solucion = this->generaSolucionGreedy();
        // Se incrementa el número de evaluaciones
        criterio_parada->incrementaEvaluaciones();
        // Se aplica una mejora local
        this->mejoraLocal(solucion);
        // Se incrementa el número de evaluaciones
        criterio_parada->incrementaEvaluaciones();

        // Si el vector de soluciones está vacío o la solución encontada es mejor que la última almacenada
        if (soluciones.empty() || soluciones.back() > solucion){
            solucion.setTiempo(criterio_parada->getTiempo());
            solucion.setEvaluacion(criterio_parada->getEvaluaciones());
            solucion.setIteracion(criterio_parada->getIteraciones());
            soluciones.push_back(solucion);
        }

        criterio_parada->incrementaIteraciones();

        // Se envía a la ventana de espera el nuevo valor del progreso
        emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);
    }
    emit incrementoProgresoAlgoritmo(criterio_parada->porcentaje(),identificador_barra_progreso);
    return soluciones;
}
