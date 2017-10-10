#ifndef ALGORITMOGRASP_H
#define ALGORITMOGRASP_H

#include <heuristicatsp.h>
#include <solucion.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Pareja compuesta por una ciudad y una distancia.
 */
struct CiudadDistancia{
    int ciudad;
    double distancia;

    /**
     * @brief Operador. Se utiliza en la ordenación de vectores de CiudadDistancia.
     * @param cd1 Primera ciudad.
     * @param cd2 Segunda ciudad.
     * @return Verdadero si cd1 < cd2 y falso en otro caso.
     */
    static bool menorQue(CiudadDistancia cd1, CiudadDistancia cd2){return cd1.distancia < cd2.distancia;};
};

/**
 * @brief Algoritmo GRASP. Resuelve un problema TSP utilizando una heurística basada en trayectorias múltiples.
 */
class GRASP : public HeuristicaTSP{

public:
    /**
     * @brief Constructor por defecto.
     */
    GRASP();

    /**
     * @brief Constructor por parámetros.
     * @param distancias_ciudades Matriz de distancias entre cada pareja de ciudades.
     */
    GRASP(vector<vector<int> > distancias_ciudades);

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de GRASP dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);

protected:
    /**
     * @brief Tamaño máximo de la lista de candidatos.
     */
    int tam_lrc;

    /**
     * @brief Genera un recorrido utilizando un algoritmo voraz.
     * @return Vector de enteros que simbolizan las ciudades recorridas.
     */
    vector<int> generaRutaGreedy();

    /**
     * @brief Genera una solución utilizando un algoritmo voraz
     * @return Solución generada.
     */
    Solucion generaSolucionGreedy();

    /**
     * @brief Genera una lista reducidad de candidatos. Cada candidate es una posible ciudad a recorrer.
     * @param ciudades_visitadas Vector de ciudades visitadas actualmente.
     * @param ultima_ciudad Última ciudad visitada.
     * @return Vector de enteros compuesto por las ciudades candidatas seleccionadas.
     */
    vector<int> generaLRC(vector<bool>& ciudades_visitadas, int ultima_ciudad);
};

#endif // ALGORITMOGRASP_H
