#ifndef HEURISTICATSP_H
#define HEURISTICATSP_H

#include <solucion.h>
#include <ventanaespera.h>
#include <QObject>
#include <QVector>
#include <ctime>
#include <fstream>
#include <iostream>

/**
 * @brief Se utiliza para medir el tiempo.
 */
class ContadorTiempo
{
private:

    /**
     * @brief Indica si el contador se encuentra midiendo tiempo.
     */
    bool activado;

    /**
     * @brief Valor inicial del tiempo.
     */
    time_t inicio;

    /**
     * @brief Intervalo de tiempo entre que se inicia el contador y se detiene.
     */
    double tiempo_contado;

    /**
     * @brief Convierte time_t a segundos.
     * @param Tiempo a convertir.
     * @return Segundos.
     */
    inline double segundos(time_t tiempo){return tiempo/(double)CLOCKS_PER_SEC;};


public:
    /**
     * @brief Construtor por defecto.
     */
    ContadorTiempo();

    /**
     * @brief Inicia el contador de tiempo.
     */
    void iniciar();

    /**
     * @brief Detiene el contador de tiempo.
     * @return Intervalo de tiempo transcurrido desde que se inció el contador.
     */
    double parar();

    /**
     * @brief Calcula el tiempo transcurrido hasta ahora desde que se inició el contador.
     * @return Intervalo de tiempo transcurrido desde que se inció el contador.
     */
    double getTiempo();

    /**
     * @brief Informa si el contador está activa
     * @return Verdadero si el contador está activado y false en otro caso.
     */
    inline bool estaActivado(){return this->activado;};

};

/**
 * @brief Establece tres criterios distintos en base a los cuales se puede detener un algoritmo.
 */
class CriterioParada{

private:
    /**
     * @brief Criterio tiempo.
     */
    double tiempo_objetivo;

    /**
     * @brief Evaluaciones de la función trascurridas.
     */
    double evaluaciones;

    /**
     * @brief Criterio evaluaciones.
     */
    double evaluaciones_objetivo;

    /**
     * @brief Iteraciones del algoritmo trascurridas.
     */
    double iteraciones;

    /**
     * @brief Criterio iteraciones.
     */
    double iteraciones_objetivo;

    /**
     * @brief Informa si tiempo es criterio de parada
     */
    bool tiempo_es_cp;

    /**
     * @brief Informa si evaluaciones de la función objetivo es criterio de parada
     */
    bool evaluaciones_es_cp;

    /**
     * @brief Informa si iteraciones del algoritmo es criterio de parada
     */
    bool iteraciones_es_cp;

    /**
     * @brief Se utiliza para medir el criterio tiempo.
     */
    ContadorTiempo contador;

public:
    /**
     * @brief Contructor por parámetros.
     * @param tiempo_objetivo Criterio de parada tiempo.
     * @param evaluaciones_objetivo Criterio de para número de evaluaciones de la función objetivo.
     * @param iteraciones_objetivo Criterio de parada iteraciones de la función objetivo.
     */
    CriterioParada(double tiempo_objetivo, double evaluaciones_objetivo, double iteraciones_objetivo);

    /**
     * @brief Activa el contador de tiempo.
     */
    void iniciaTiempo();

    /**
     * @brief Incrementa el número de evaluaciones actual.
     */
    inline void incrementaEvaluaciones(){this->evaluaciones++;};

    /**
     * @brief Incrementa el número de evaluaciones de la función objetivo actual.
     * @param incremento Valor en el que se incrementan las evluaciones.
     */
    inline void incrementaEvaluaciones(int incremento){this->evaluaciones+=incremento;};

    /**
     * @brief Incrementa el número de iteraciones del algoritmo actual.
     */
    inline void incrementaIteraciones(){this->iteraciones++;};

    /**
     * @brief Informa si se han cumplido todas las condiciones de parada.
     * @return Verdadero en caso de que se hayan todas las condiciones de parada.
     */
    bool cumplidosTodos();

    /**
     * @brief Informa si se ha cumplido alguna condición de parada.
     * @return Verdadero en caso de que se haya cumplido alguna condición de parada.
     */
    bool cumplido();

    /**
     * @brief Calcula el porcentaje de avance del criterio de parada.
     * @return Porcentaje de avance del criterio de parada cuyo porcentaje de avance sea mayor.
     */
    int porcentaje();

    /**
     * @brief Consultor de tiempo.
     * @return Tiempo transcurrido.
     */
    inline double getTiempo(){return this->contador.getTiempo();};

    /**
     * @brief Consultor de las evaluaciones de la función objetivo.
     * @return Evaluaciones de la función objetivo transcurridas.
     */
    inline int getEvaluaciones(){return this->evaluaciones;};

    /**
     * @brief Consultor de las iteraciones del algoritmo.
     * @return Iteraciones del algoritmo transcurridas.
     */
    inline int getIteraciones(){return this->iteraciones;};

};

/**
 * @brief Clase general que ofrece funcionalidades para resolver problemas TSP.
 */
class HeuristicaTSP : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Constructor por defecto.
     */
    HeuristicaTSP();

    /**
     * @brief Constructor por parámetros.
     * @param distancias_ciudades Matriz de distancias entre las ciudades.
     */
    HeuristicaTSP(vector<vector<int> > distancias_ciudades);

    // Inicializa la matriz de distancias y el número de ciudades en la clase
    /**
     * @brief Inicializa estructuras de datos de la clase
     * @param distancias_ciudades  Matriz de distancias entre las ciudades.
     */
    void setDistanciasCiudades(vector<vector<int> > distancias_ciudades);

    // Conecta la clase del algoritmo con la ventana de espera asociada, indicando qué barra de progreso se corresponde con
    // el progreso de ejecución del algoritmo
    /**
     * @brief Conecta la clase con la barra de progreso asociada en la Ventana de Espera.
     * @param ventana_espera Ventana de espera donde se muestra el progreso de los algoritmos.
     * @param id_barra_progreso Barra de progreso asociada a la ejecución del algoritmo.
     */
    void conectaVentanaEspera(VentanaEspera* ventana_espera = 0, int id_barra_progreso = -1);

    /**
     * @brief Consultor del nombre del algoritmo.
     * @return Nombre del algoritmo.
     */
    inline string getNombreAlgoritmo(){return this->nombre_heuristica;};

    /**
     * @brief Mejora localmente una solución utilizando una mejora local de tipo 2-OPT.
     * @param solucion Solución a mejorar.
     */
    void mejoraLocal(Solucion& solucion);

protected:
    /**
     * @brief Matriz de distancias entre ciudades.
     */
    vector<vector<int> > distancias_ciudades;

    /**
     * @brief Nombre del algoritmo.
     */
    string nombre_heuristica;

    /**
     * @brief Número de ciudades del problema.
     */
    int numero_ciudades;

    /**
     * @brief Bandera que indica si se debe detener la ejecución del algoritmo.
     */
    bool ejecucion_cancelada;

    // En una solucion, realiza el intercambio que más mejore el coste. Devuelve verdadero si
    // se ha realizado algún intercambio, falso en otro caso
    /**
     * @brief Realiza el intercambio entre dos ciudades de un recorrido en una solución. Este intercambio es el que produce una mejoría mayor en el coste.
     * @param solucion Solución a realizar el mejor intercambio.
     * @return Verdadero si se ha realizado el intercambio.
     */
    bool realizaMejorIntercambio(Solucion& solucion);

    /**
     * @brief Calcula el coste de una solución en caso de que se intercambiaran las dos posiciones indicadas de su recorrido.
     * @param solucion Solución a intercambiar posicones del recorrido.
     * @param coste Coste de la solución sin intercambiar.
     * @param pos_1 Posición
     * @param pos_2 Posición
     * @return Coste de la solución en el caso que se intercambiaran las ciudades en pos_1 y pos_2 del recorrido.
     */
    int getCosteConIntercambio(vector<int> solucion, int coste, int pos_1, int pos_2);

    /**
     * @brief Intercambia dos posiciones en un vector de enteros.
     * @param v Vector.
     * @param pos_1 Posición.
     * @param pos_2 Posición.
     */
    void intercambia(vector<int> &v, int pos_1, int pos_2);

    /**
     * @brief Calcula el coste de una ruta.
     * @param ruta Ruta a calcular el coste.
     * @return Coste de la ruta.
     */
    int getCoste(const vector<int> ruta);

    /**
     * @brief Genera un número de enteros aleatorios.
     * @param n Número de enteros aleatorios a generar.
     * @param max Máximo valor de los enteros generado, con cero como mínimo.
     * @return Vector con los enteros generados.
     */
    vector<int> generaAleatoriosDistintos(int n, int max);

    /**
     * @brief Genera una solución aleatoria.
     * @return Solución aleatoria.
     */
    Solucion generaSolucionAleatoria();

    /**
     * @brief Lee un fichero de configuración de algoritmo desde el sistema de ficheros.
     * @param ruta Ruta del fichero de configuración.
     * @param parametros_algoritmo Parámetros leídos desde el fichero.
     * @return Verdadero si la lectura se ha realizado correctamente.
     */
    bool leeFicheroConfiguracion(string ruta, vector<double>& parametros_algoritmo);

    // Devuelve un entero del 0 al 100 indicando el porcentaje de ejecución del algoritmo
    inline int calculaProgresoAlgoritmo(int iteracion_actual, int total_iteraciones){
        return ((double)(iteracion_actual+1)/(double)total_iteraciones)*100;};


    string vectorToString(vector<int> vector);
    string vectorVisitadasToString(vector<bool> vector);

signals:
    // Indica que se ha producido un incremento en el proceso de ejecución del algoritmo
    void incrementoProgresoAlgoritmo(int nuevo_progreso, int id_barra_progreso);

public slots:
    // Pone a verdadero la bandera que indica que se debe cancelar la ejecución del algoritmo
    inline void ejecucionCancelada(){this->ejecucion_cancelada = true;};

};

#endif // HEURISTICATSP_H
