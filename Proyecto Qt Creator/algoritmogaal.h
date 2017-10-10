#ifndef ALGORITMOGAAL_H
#define ALGORITMOGAAL_H

#include <algoritmoga.h>

class GAAL : public GA {
public:
    GAAL();

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de GA dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada = 0, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);
};

#endif // ALGORITMOGAAL_H
