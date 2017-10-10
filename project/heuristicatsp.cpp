#include "heuristicatsp.h"

ContadorTiempo::ContadorTiempo(){
    this->activado = false;
    this->inicio = -1;
    this->tiempo_contado = -1;
}

void ContadorTiempo::iniciar(){
    // Si el contador no se ha iniciado, lo inicia
    if (!this->activado){
        // Se reinicia el tiempo contado hasta ahora
        this->tiempo_contado = 0;

        // Se marca la bandera a true
        this->activado = true;

        // Se inicia la cuenta
        this->inicio = clock();

    }
}

double ContadorTiempo::parar(){
    // Si el contador se ha iniciado, devuelve el valor del tiempo y lo para
    if (this->activado){

        // Se marca la bandera a false
        this->activado = false;

        // Se almacena el tiempo contado hasta ahora
        this->tiempo_contado = this->segundos(clock() - this->inicio);

        // Se devuelve el tiempo en segundos
        return this->tiempo_contado;
    }

    else{
        return -1;
    }
}

double ContadorTiempo::getTiempo(){
    // Si el contador está activado devuelve el tiempo actual
    if (this->activado){
        return this->segundos(clock() - this->inicio);
    }

    // Si no está activado devuelve el último tiempo transcurrido
    else{
        return this->tiempo_contado;
    }
}

CriterioParada::CriterioParada(double tiempo_objetivo, double evaluaciones_objetivo, double iteraciones_objetivo){
    // Se establece el valor inicial para las evaluaciones y las iteraciones
    this->evaluaciones = 0;
    this->iteraciones = 0;

    // Si el tiempo no es un criterio de parada
    if(tiempo_objetivo <= 0){
        this->tiempo_es_cp = false;
    }
    // En otro caso
    else{
        this->tiempo_es_cp = true;
        this->tiempo_objetivo = tiempo_objetivo;
    }

    // Si las evaluaciones no son un criterio de parada
    if(evaluaciones_objetivo <= 0){
        this->evaluaciones_es_cp = false;
    }
    // En otro caso
    else{
        this->evaluaciones_es_cp = true;
        this->evaluaciones_objetivo = evaluaciones_objetivo;
    }

    // Si las iteraciones no son un criterio de parada
    if (iteraciones_objetivo <= 0){
        this->iteraciones_es_cp = false;
    }
    // En otro caso
    else{
        this->iteraciones_es_cp = true;
        this->iteraciones_objetivo = iteraciones_objetivo;
    }
}

bool CriterioParada::cumplidosTodos(){
    bool tiempo_cumplido, evaluaciones_cumplido, iteraciones_cumplido;
    bool valor_final;

    // Los criterios que no se contemplan se asumen que han sido cumplidos
    tiempo_cumplido = !this->tiempo_es_cp;
    evaluaciones_cumplido = !this->evaluaciones_es_cp;
    iteraciones_cumplido = !this->iteraciones_es_cp;

    // Para cada criterio, si se contempla (es falso actualmente) y se ha cumplido,
    // se establece a verdadero
    if (!tiempo_cumplido && this->contador.getTiempo() >= this->tiempo_objetivo){
        tiempo_cumplido = true;
    }

    if (!evaluaciones_cumplido && this->evaluaciones >= this->evaluaciones_objetivo){
        evaluaciones_cumplido = true;
    }

    if (!iteraciones_cumplido && this->iteraciones >= this->iteraciones_objetivo){
        iteraciones_cumplido = true;
    }

    // Se calcula el valor que se va a devolver
    valor_final = tiempo_cumplido && evaluaciones_cumplido && iteraciones_cumplido;

    // Si se va a devolver verdadero, con lo que se terminaría el bucle de ejecución del algoritmo,
    // se para el contador de tiempo
    if (valor_final){
        contador.parar();
    }

    return valor_final;
}

bool CriterioParada::cumplido(){
    bool finaliza = true;

    // Si hay algún criterio de parada
    if (this->tiempo_es_cp || this->evaluaciones_es_cp || this->iteraciones_es_cp){

        // Se considera que no ha se cumplido ninguna condición de parada
        finaliza = false;

        // Si no ha sido iniciado el contador, lo inicia
        if (!this->contador.estaActivado()){
            this->contador.iniciar();
        }
        // Si está iniciado comprueba si se ha alcanzado el tiempo objetico
        else if (this->contador.getTiempo() >= this->tiempo_objetivo && this->tiempo_es_cp){
            finaliza = true;
            this->contador.parar();
        }


        // Si el criterio son las evaluaciones
        if (this->evaluaciones_es_cp){
            if (this->evaluaciones >= this->evaluaciones_objetivo){
                finaliza = true;
            }
        }

        // Si el criterio son las iteraciones
        if (this->iteraciones_es_cp){
            if (this->iteraciones >= this->iteraciones_objetivo){
                finaliza = true;
            }
        }
    }
    return finaliza;
}

int CriterioParada::porcentaje(){
    vector<int> porcentajes;

    if (this->tiempo_es_cp){
        porcentajes.push_back((this->contador.getTiempo()/this->tiempo_objetivo)*100);
    }

    if (this->evaluaciones_es_cp){
        porcentajes.push_back((this->evaluaciones/this->evaluaciones_objetivo)*100);
    }

    if (this->iteraciones_es_cp){
        porcentajes.push_back((this->iteraciones/this->iteraciones_objetivo)*100);
    }

    // Si el vector no está vacío
    if (!porcentajes.empty()){
        // Se ordena el vector
        sort(porcentajes.begin(), porcentajes.end());

        // Se devuelve el mayor y se trunca a 100
        if (porcentajes.back() <= 100){
            return porcentajes.back();
        }
        else{
            return 100;
        }
    }

    // Si el vector está vació se devuelve -1
    else{
        return -1;
    }
}

HeuristicaTSP::HeuristicaTSP(){
    this->numero_ciudades = 0;

    // Se reinicia la semilla aleatoria
    time_t t;
    srand((unsigned)time(&t));
}

HeuristicaTSP::HeuristicaTSP(vector<vector<int> > distancias_ciudades){
    this->distancias_ciudades = distancias_ciudades;
    this->numero_ciudades = this->distancias_ciudades.size();

    // Se reinicia la semilla aleatoria
    time_t t;
    srand((unsigned)time(&t));
}

void HeuristicaTSP::setDistanciasCiudades(vector<vector<int> > distancias_ciudades){
    this->distancias_ciudades = distancias_ciudades;
    this->numero_ciudades = this->distancias_ciudades.size();
}

int HeuristicaTSP::getCoste(const vector<int> ruta){
    int coste = 0;
    int ciudad_actual, ciudad_siguiente;
    for (unsigned int i=0; i<ruta.size(); i++){
        ciudad_actual = ruta[i];
        ciudad_siguiente = ruta[(i+1)%ruta.size()];
        coste+=this->distancias_ciudades[ciudad_actual][ciudad_siguiente];
    }
    return coste;
}

void HeuristicaTSP::conectaVentanaEspera(VentanaEspera *ventana_espera, int id_barra_progreso){
    // Si ventana_espera apunta a alguna ventana de espera
    if (ventana_espera){
        connect(this, SIGNAL(incrementoProgresoAlgoritmo(int,int)), ventana_espera, SLOT(actualizaBarraProgreso(int, int)));
    }
}

string HeuristicaTSP::vectorToString(vector<int> vector){
    stringstream ss;
    ss << "[";
    for (unsigned int i=0; i<vector.size(); i++){
        ss << vector[i];
        if (i != vector.size()-1){
            ss << ", ";
        }
    }
    ss << "]";
    return ss.str();
}

string HeuristicaTSP::vectorVisitadasToString(vector<bool> vector){
    stringstream ss;
    ss << "{";
    for (unsigned int i=0; i<vector.size(); i++){
        if (vector[i]){
            ss << "V";
        }
        else{
            ss << "-";
        }
        if (i != vector.size()-1){
            ss << " ";
        }
    }
    ss << "}";
    return ss.str();
}

void HeuristicaTSP::intercambia(vector<int> &v, int pos_1, int pos_2){
    int aux = v[pos_1];
    v[pos_1] = v[pos_2];
    v[pos_2] = aux;
}

bool HeuristicaTSP::realizaMejorIntercambio(Solucion &solucion){
    bool intercambio_realizado = false;
    int coste_primera_solucion = solucion.getCoste();
    int mejor_coste = coste_primera_solucion;
    int coste_candidato;
    int pos_mejor_1, pos_mejor_2;
    vector<int> ruta_solucion;

    // Para cada posible pareja de ciudades
    for (int i=0; i<this->numero_ciudades; i++){
        for (int j=i+1; j<this->numero_ciudades; j++){
                coste_candidato = this->getCosteConIntercambio(solucion.getRuta(),coste_primera_solucion,i,j);

                // Si realizando el intercambio mejora el coste de la solución
                if (coste_candidato < mejor_coste){
                    mejor_coste = coste_candidato;
                    pos_mejor_1 = i;
                    pos_mejor_2 = j;
                    intercambio_realizado = true;
                }
        }
    }

    // Si se ha encontrado un cambio que mejore la solución
    if(intercambio_realizado){
        // Se realiza el intercambio sobre la solución
        ruta_solucion = solucion.getRuta();
        this->intercambia(ruta_solucion, pos_mejor_1, pos_mejor_2);
        solucion.setRuta(ruta_solucion);
        solucion.setCoste(mejor_coste);
    }

    // Se informa sobre si se ha realizado el cambio o no
    return intercambio_realizado;
}

int HeuristicaTSP::getCosteConIntercambio(vector<int> solucion, int coste, int pos_1, int pos_2){
    int posible_coste = coste;
    int separacion_pos1_pos2 = abs(pos_1-pos_2);

    // Posiciones de las ciudades contiguas a las dos dadas:
    int pos_1_dcha = (pos_1 + 1) % this->numero_ciudades;
    int pos_1_izda = (pos_1 - 1 + this->numero_ciudades)  % this->numero_ciudades;
    int pos_2_dcha = (pos_2 + 1) % this->numero_ciudades;
    int pos_2_izda = (pos_2 - 1 + this->numero_ciudades)  %this->numero_ciudades;

    // Se restan las distancias de los lados que se eliminan (los que tienen como vértices a las ciudades a intercambiar):
    posible_coste -= (this->distancias_ciudades[solucion[pos_1]][solucion[pos_1_izda]]
                + this->distancias_ciudades[solucion[pos_1]][solucion[pos_1_dcha]]
                + this->distancias_ciudades[solucion[pos_2]][solucion[pos_2_izda]]
                + this->distancias_ciudades[solucion[pos_2]][solucion[pos_2_dcha]]);

    // Se suman las distancias de los nuevos lados:
    posible_coste += (this->distancias_ciudades[solucion[pos_1]][solucion[pos_2_izda]]
                + this->distancias_ciudades[solucion[pos_1]][solucion[pos_2_dcha]]
                + this->distancias_ciudades[solucion[pos_2]][solucion[pos_1_izda]]
                + this->distancias_ciudades[solucion[pos_2]][solucion[pos_1_dcha]]);

    /* Si la separación en orden_ciudades de ambas ciudades es 1 (num_visitadas - 1 en caso de ser la primera y la última ciudad)
        se ha restado dos veces la distancia entre ellas y se ha sumado 0 dos veces (la distancia entre una ciudad y ella misma).
        Por ello debemos sumar de nuevo la distancia entre ambas ciudades 2 veces: */
    if (separacion_pos1_pos2 == 1 || separacion_pos1_pos2 == this->numero_ciudades - 1){
        posible_coste += 2*this->distancias_ciudades[solucion[pos_1]][solucion[pos_2]];
    }

    return posible_coste;
}

void HeuristicaTSP::mejoraLocal(Solucion &solucion){
    bool intercambio_realizado = true;

    // Mientras se pueda realizar un intercambio de ciudades en la ruta que mejore el coste
    // se realiza
    while(intercambio_realizado){
        intercambio_realizado = this->realizaMejorIntercambio(solucion);
    }
}

vector<int> HeuristicaTSP::generaAleatoriosDistintos(int n, int max){
    vector <int> aleatorios_distintos;
    vector <int> secuencia;
    int aleatorio;

    // Se completa el vetor con los valores 0 .. max
    for (int i=0; i<max; i++){
        secuencia.push_back(i);
    }

    for (int i=0; i<n; i++){
        aleatorio = rand()%(max-i);
        aleatorios_distintos.push_back(secuencia[aleatorio]);
        secuencia.erase(secuencia.begin()+aleatorio);
    }

    return aleatorios_distintos;
}

bool HeuristicaTSP::leeFicheroConfiguracion(string ruta, vector<double>& parametros_algoritmo){
    bool lectura_correcta = true;

    // Línea leída del fichero de configuración
    string linea;
    // Se abre el fichero
    std::ifstream fichero(ruta.c_str());

    if (fichero.is_open()){
        // Mientras no se llegue al final del fichero
        while(!fichero.eof()){
            getline(fichero, linea);
            // Si la línea empieza por ";", se entiende que es un comentario. En caso contrario
            // se añade al vector de parámetros
            if (linea.at(0) != ';'){
                parametros_algoritmo.push_back(atof(linea.c_str()));
            }
        }
    }

    else{
        lectura_correcta = false;
    }

    // Se cierra el fichero de configuración
    fichero.close();

    return lectura_correcta;
}

Solucion HeuristicaTSP::generaSolucionAleatoria(){
    vector<int> ruta = this->generaAleatoriosDistintos(this->numero_ciudades, this->numero_ciudades);
    Solucion sol(ruta, 0);
    return Solucion(ruta, this->getCoste(ruta));
}
