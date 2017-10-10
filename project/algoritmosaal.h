#ifndef ALGORITMOSAAL_H
#define ALGORITMOSAAL_H

#include <algoritmosa.h>

class SAAL : public SA
{
public:
    SAAL();

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de SA dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* criterio_parada, VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);

};

#endif // ALGORITMOSAAL_H
