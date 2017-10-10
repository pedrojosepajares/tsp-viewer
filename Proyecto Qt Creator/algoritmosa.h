#ifndef ALGORITMOSA_H
#define ALGORITMOSA_H

#include <heuristicatsp.h>
#include <solucion.h>
#include <cmath>
#include <algoritmovecinomascercano.h>

/**
 * @brief Algoritmo SA. Resuelve un problema TSP utilizando una heurística basada en enfriamiento simulado.
 */
class SA : public HeuristicaTSP{

public:
    /**
     * @brief Constructor por defecto.
     */
    SA();

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de SA dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);

protected:
    /**
     * @brief Parámentro para el cálculo de la temperatura inicial
     */
    double mi;

    /**
     * @brief Parámentro para el cálculo de la temperatura inicial
     */
    double sigma;

    /**
     * @brief Parámentro de enfriamiento.
     */
    double alpha;

    /**
     * @brief Número máximo de vecino que se pueden generar en una iteración
     */
    int max_vecinos;

    /**
     * @brief Intercambia dos posiciones en un vector de enteros.
     * @param v Vector de enteros a intercambiar las posiciones.
     * @param pos_1 Posición a intercambiar.
     * @param pos_2 Posición a intercambiar.
     */
    void intercambia(vector<int>& v, int pos_1, int pos_2);

    // Devuelve el nuevo coste de solución cuando se intercambian las ciudades en las posiciones pos1 y pos2
    /**
     * @brief Calcula el coste de una solución cuando se intercambian las posciones de dos ciudades en su recorrido.
     * @param solucion Solución a calcular el coste.
     * @param pos_1 Posición a intercambiar.
     * @param pos_2 Posición a intercambiar.
     * @return Coste al realizar el intercambio de las ciudades en pos_1 y pos_2 en el recorrido de solucion.
     */
    int getCosteConIntercambio(Solucion solucion, int pos_1, int pos_2);

    // Genera el vecino de solución con coste coste_vecino intercambiando las ciudades en las posiciones dadas
    /**
     * @brief Genera un vecino a una solución con un coste calculado previamente intercambiando dos ciudades de su recorrido
     * @param solucion Solución a partir de la cual se genera el vecino.
     * @param pos1 Posición a intercambiar
     * @param pos2 Posición a intercambiar.
     * @param coste_vecino Coste precalculado del vecino.
     * @return Solución vecina.
     */
    Solucion generaVecino(Solucion solucion, int pos1, int pos2, int coste_vecino);

    /**
     * @brief Genera un valor aleatorio uniforme entre cero y uno.
     * @return Valor aleatorio uniforme.
     */
    inline double uniforme(){return rand()/(double)RAND_MAX;};
};

#endif // ALGORITMOSA_H
