#ifndef ALGORITMOGA_H
#define ALGORITMOGA_H

#include <heuristicatsp.h>
#include <solucion.h>
#include <ventanaespera.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <algoritmograsp.h>

/**
 * @brief Algoritmo GA. Resuelve un problema TSP utilizando una heurística basada en un algoritmo genético.
 */

class GA : public HeuristicaTSP{

public:
    /**
     * @brief Constructor por defecto.
     */
    GA();
    // Resuelve TSP usando un algoritmo genético

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de GA dentro de la Ventana de Espera.
     * @param ini_aleatoria Si la variable es verdadera la inicialización de la población es aleatoria, en otro caso las inicialización se lleva acabo utilizando un algoritmo GRASP.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada = 0, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);

protected:

    /**
     * @brief Probabilidad de que un individuo de la población mute.
     */
    double probabilidad_mutacion;

    /**
     * @brief Número de individuos que conforman la población.
     */
    int numero_individuos_poblacion;

    /**
     * @brief Número de individuos seleccionados de la población para someter a torneo.
     */
    int numero_candidatos_torneo;

    /**
     * @brief Criterio de parada para el algoritmo GRASP inicializador de la población.
     */
    double tiempo_grasp;

    /**
     * @brief Criterio de parada para el algoritmo GRASP inicializador de la población.
     */
    int evaluaciones_grasp;

    /**
     * @brief Criterio de parada para el algoritmo GRASP inicializador de la población.
     */
    int iteraciones_grasp;

    /**
     * @brief Genera una población de individuos utilizando un algoritmo GRASP.
     * @return  Población.
     */
    vector<Solucion> generaPoblacionGRASP();

    /**
     * @brief Selecciona por torneo un individuo de la población.
     * @param poblacion Población de individuos.
     * @return Iterador al individuo de la población seleccionado.
     */
    vector<Solucion>::iterator seleccionaPorTorneo(vector<Solucion>& poblacion);


    /**
     * @brief Aplica un operador de cruce OX a dos individuos.
     * @param padre_1 Padre.
     * @param padre_2 Padre.
     * @return Descendiente.
     */
    Solucion realizaCruce(Solucion padre_1, Solucion padre_2);


    /**
     * @brief Muta un individuo intercambiando dos ciudades aleatorias de su recorrido.
     * @param individuo Individuo a mutar.
     */
    void realizaMutacion(Solucion& individuo);

    /**
     * @brief Calcula el coste de una solución en la que se intercambian dos posiciones.
     * @param solucion Solución a calcular el coste realizando el intercambio.
     * @param pos_1 Posición que se intermcabia.
     * @param pos_2 Posición que se intermcabia.
     * @return Coste de realizar el intercambio entre las dos posiciones.
     */
    int getCosteConIntercambio(Solucion solucion, int pos_1, int pos_2);


    /**
     * @brief Intercambia dos posiciones en una ruta de ciudades.
     * @param v Ruta de ciudades.
     * @param pos_1 Posición que se intermcabia.
     * @param pos_2 Posición que se intermcabia.
     */
    void intercambia(vector<int>& v, int pos_1, int pos_2);


    /**
     * @brief Calcula el número de arcos, es decir, mismas ciudades que se visitan de forma consecutiva, entre dos soluciones.
     * @param s1 Solución.
     * @param s2 Solución.
     * @return Número de arcos que comparten s1 u s2.
     */
    int similitud(Solucion s1, Solucion s2);

    /**
     * @brief Calcula el mejor individuo de una población
     * @param poblacion Población de individuos.
     * @return Mejor individuo.
     */
    Solucion getMejorIndividuoPoblacion(vector<Solucion> poblacion);


    /**
     * @brief Calcula la posición que ocupa dentro de la población el peor individuo.
     * @param poblacion Población de individuos.
     * @return Posición que ocupa el peor individuo en la población.
     */
    int getIndicePeorIndividuoPoblacion(vector<Solucion> poblacion);
};


#endif // ALGORITMOGA_H
