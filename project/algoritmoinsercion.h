#ifndef ALGORITMOINSERCION_H
#define ALGORITMOINSERCION_H

#include <heuristicatsp.h>
#include <solucion.h>

/**
 * @brief Algoritmo Inserción. Resuelve un problema TSP utilizando una heurística basada en la búsqueda de la mejor inserción de una ciudad en el recorrido.
 */
class Insercion : public HeuristicaTSP
{
public:
    /**
     * @brief Constructor por defecto.
     */
    Insercion();

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de Inserción dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada = 0, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);


protected:
    /**
     * @brief Calcula el incremento de coste que se produciría al inserta una ciudad en una determinada posición de la ruta.
     * @param ruta Ruta a la que se calcula el coste de inserción.
     * @param ciudad Ciudad que se inserta.
     * @param posicion_insercion Posición de la ruta en la que se inserta la ciudad.
     * @return Nuevo coste de la ruta el realizar la inserción de ciudad en posicion_insercion.
     */
    int getCosteAlRealizarInsercion(const vector<int> ruta, const int ciudad, const int posicion_insercion);


};

#endif // ALGORITMOINSERCION_H
