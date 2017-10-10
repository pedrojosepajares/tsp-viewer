#ifndef VECINOMASCERCANO_H
#define VECINOMASCERCANO_H

#include "heuristicatsp.h"
#include "solucion.h"

/**
 * @brief Algoritmo Vecino más cercano. Resuelve un problema TSP utilizando una heurística basada en seleccionar como sigueinte ciudad a visitar la más cercana a la última visitada.
 */
class VecinoMasCercano :  public HeuristicaTSP
{
public:
    /**
     * @brief Constructor por defecto.
     */
    VecinoMasCercano();

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de Vecino más cercano dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada = 0, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);
};

#endif // VECINOMASCERCANO_H
