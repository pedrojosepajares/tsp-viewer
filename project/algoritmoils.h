#ifndef ALGORITMOILS_H
#define ALGORITMOILS_H

#include <heuristicatsp.h>
#include <solucion.h>
#include <algoritmovecinomascercano.h>
#include <algoritmograsp.h>
#include <stdlib.h>
#include <algorithm>

#include <time.h>

/**
 * @brief Algoritmo ILS. Resuelve un problema TSP utilizando una heurística basada en una búsqueda local iterativa.
 */
class ILS : public HeuristicaTSP{

public:
    /**
     * @brief Constructor por defecto.
     */
    ILS();

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de ILS dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada = 0, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);

protected:
    // Número de individuos de la población
    /**
     * @brief Número de individuos de la población.
     */
    int mi;

    /**
     * @brief Número de hijos que se generan mediante mutación.
     */
    int lambda;

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
     * @brief Calcula el coste de una solución si se intercambian las posiciones de dos ciudades durante el recorrido.
     * @param solucion Solución a la cual se le intercambiarán dos ciudades
     * @param pos_1 Posición de la primera ciudad en la solución.
     * @param pos_2 Posición de la segunda ciudad en la solución.
     * @return Coste de solucion al intercambiar la ciudades en pos_1 y pos_2
     */
    int getCosteConIntercambio(Solucion solucion, int pos_1, int pos_2);

    /**
     * @brief Intercambia dos elementos en un vector.
     * @param v Vector de enteros.
     * @param pos_1 Posición a intercambiar.
     * @param pos_2 Posición a intercambiar.
     */
    void intercambia(vector<int>& v, int pos_1, int pos_2);

    /**
     * @brief Muta una solución intercambiando dos ciudades aleatorias en su recorrido.
     * @param solucion Solución a mutar.
     */
    void realizaMutacion(Solucion& solucion);

};

#endif // ALGORITMOILS_H
