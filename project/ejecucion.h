#ifndef EJECUCION_H
#define EJECUCION_H

#include <vector>
#include <solucion.h>
#include <string>
#include <heuristicatsp.h>

/**
 * @brief Almacena el resultado de una ejecución de un algoritmo heurístico y el criterio de parada utilizado.
 */
struct Ejecucion{
    /**
     * @brief Vector con las mejores soluciones que el algoritmo ha ido contruyendo durante el proceso de ejecución.
     */
    vector<Solucion> soluciones;

    /**
     * @brief Criterio de parada utilizado para detener la ejecución del algoritmo.
     */
    CriterioParada* criterio_parada;

    /**
     * @brief Entero que define al algoritmo ejecutado. Se utiliza en la Ventana Principal.
     */
    int id_algoritmo;

    /**
     * @brief Nombre del algoritmo ejecutado.
     */
    string nombre_algoritmo;
};

#endif // EJECUCION_H
