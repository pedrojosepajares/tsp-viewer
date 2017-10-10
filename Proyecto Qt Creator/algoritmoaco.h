#ifndef ALGORITMOACO_H
#define ALGORITMOACO_H


#include <heuristicatsp.h>
#include <solucion.h>
#include <time.h>
#include <stdlib.h>
#include <algorithm>
#include <cmath>

/**
 * @brief Almacena, permite consultar y actualiza los valores de feromonas producidos por las hormigas mientras recorren las ciudades.
 *
 *
 */

class MapaFeromonas{
public:

    /**
     * @brief Constructor por parámetros.
     * @param distancias Matriz de enteros cuyos elementos son las distancias entre ciudades.
     * @param porcentaje_evaporacion Tanto por cierto de feromonas que se evaporan durante la actualización de las feromonas.
     */
    MapaFeromonas(vector<vector<int> >* distancias, double porcentaje_evaporacion);

    /**
     * @brief Consulta el valor que ocupa una posición en la matriz de feromonas.
     * @param i Fila.
     * @param j Columna.
     * @return Valor de feromonas en la posición i, j.
     */
    inline double at(int i, int j){return this->feromonas[i][j];};

    /**
     * @brief Modifica los valores de la matriz de feromonas en función de las ciudades recorridas por las hormigas.
     * @param hormigas Vector de hormigas con recorridos completos.
     */
    void actualizar(vector<Solucion>* hormigas);

protected:
    /**
     * @brief Matriz donde se almacenan los valores actuales de las feromonas.
     */
    vector<vector<double> > feromonas;

    /**
     * @brief Matriz de distancias entre ciudades.
     */
    vector<vector<int> >* distancias;

    /**
     * @brief Tanto por uno en el que se evaporan las feromonas tras cada iteración del algoritmo.
     */
    double rho;

};

/**
 * @brief Almacena, permite consultar y agiliza operaciones relacionadas con la probabilidad de que una hormiga visite una determinada ciudad.
 */

class MapaProbabilidades{
public:

    // . Los valores alpha y beta indican la importancia de la
    // información memorística y heurística respectivamente
    /**
     * @brief Constructor por parámetros
     * @param alpha Porcentaje de importancia de la información memorística
     * @param beta Porcentaje de importancia de la información heurística
     */
    MapaProbabilidades(double alpha, double beta);

    // Función que actualiza los valores del mapa
    /**
     * @brief Actualiza la matriz de probabilidades.
     * @param mapa_feromonas Matriz de rastros de feromonas dejados por las hormigas al recorrer las ciudades.
     * @param distancias Matriz de distancias entre ciudades.
     */
    void actualizar(MapaFeromonas* mapa_feromonas, vector<vector<int> >* distancias);


    /**
     * @brief Consulta la probabilidad de que la hormiga avance a una ciudad considerando la útima visitada.
     * @param r Última ciudad visitada.
     * @param s Siguiente ciudad hacia la que la hormiga se mueve.
     * @param visitadas Vector de ciudades visitadas actualmente.
     * @return Probabilidad de que la hormiga se mueva a la ciudad s siendo r la última ciudad visitada.
     */
    double at(int r,int s, vector<bool>* visitadas);

    // Calcula una siguiente ciudad basada en las probabilidades individuales de cada ciudad
    // no visitada
    /**
     * @brief Calcula la ciudad hacia la que se moverá la hormiga en base a la probabilidad de ser visitada.
     * @param ultima_visitada Última ciudad visitada por la hormiga.
     * @param visitadas  Vector de ciudades visitadas actualmente.
     * @return Ciudad hacia la que la hormiga se moverá.
     */
    int siguienteCiudad(int ultima_visitada, vector<bool>* visitadas);

protected:
    // Importancias de la información memorística y heurística
    /**
     * @brief Porcentaje de importancia de la información memorística.
     */
    double alpha;

    /**
     * @brief Porcentaje de importancia de la información heurística.
     */
    double beta;

    /**
     * @brief Matriz de probabilidades de visitar una determinada ciudad no teniendo en cuenta las ya visitadas por la hormiga.
     */
    vector<vector<double> > probabilidades;

};

/**
 * @brief Algoritmo ACO. Resuelve un problema TSP utilizando una heurística basada en colonias de hormigas.
 *
 */

class ACO: public HeuristicaTSP{

public:
    /**
     * @brief Contructor por defecto.
     */
    ACO();

    /**
     * @brief Resuelve un problema TSP.
     * @param citerio_parada Criterios que, una vez cumplidos, terminan con la ejecución del algoritmo.
     * @param ventana_espera Ventana que muestra el progreso del algoritmo.
     * @param identificador_barra_progreso Indentificador de la barra de progreso correspondiente la ejecución de ACO dentro de la Ventana de Espera.
     * @return Vector de soluciones. Cada solución es la mejor que el algoritmo ha construido hasta el momento.
     */
    vector<Solucion> resolverCP(CriterioParada* citerio_parada = 0 , VentanaEspera* ventana_espera = 0, int identificador_barra_progreso = -1);


protected:
    // Número de hormigas de la colonia
    /**
     * @brief Número de hormigas que componen la colonia
     */
    int n_hormigas;

    /**
     * @brief Porcentaje de importancia de la información memorística.
     */
    double alpha;

    /**
     * @brief Porcentaje de importancia de la información heurística.
     */
    double beta;

    /**
     * @brief Calcula la mejor solución encontrada por una colonia de hormigas.
     * @param poblacion Colonia de hormigas.
     * @return Mejor solución.
     */
    Solucion getMejorSolucion(vector<Solucion> poblacion);
};

#endif // ALGORITMOACO_H
