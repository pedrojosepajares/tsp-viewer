#ifndef DATOSPROBLEMA_H
#define DATOSPROBLEMA_H

#include <vector>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cmath>

#include <iostream>

using namespace std;

/**
 * @brief Contiene información referente a un problema TSP cargado desde el sistema de fichero. También genera las matrices de distancias y posiciones para las ciudades.
 */

class DatosProblema{
public:
    /**
     * @brief Constructor por defecto.
     */
    DatosProblema();

    /**
     * @brief Consultor de la matriz de distancias.
     * @return Matriz de distancias entre ciudades.
     */
    inline vector<vector<int> > getDistanciasCiudades(){return this->distancias_ciudades;};

    /**
     * @brief Consultor de la matriz de posiciones.
     * @return Matriz de posiciones de ciudades.
     */
    inline vector<vector<double> > getPosicionesCiudades(){return this->posiciones_ciudades;};

    /**
     * @brief  Consultor del nombre del problema.
     * @return Nombre del problema.
     */
    inline string getNombreProblema(){return this->nombre_problema;};

    /**
     * @brief Consultor del nombre del número de ciudades.
     * @return Número de ciudades
     */
    inline int getNumeroCiudades(){return this->numero_ciudades;};

    /**
     * @brief Consultor de la distancia óptima.
     * @return Distancia óptima.
     */
    inline int getDistanciaOptima(){return this->distancia_optima;};

    /**
     * @brief Lee la información sobre un problema TSP en un fichero y genera las matrices de distancias y posiciones entre ciudades.
     * @param nombre_fichero Ruta del fichero de especificación TSP.
     */
    void leeFichero(string nombre_fichero);

protected:
    /**
     * @brief Nombre del problema.
     */
    string nombre_problema;

    /**
     * @brief Número de ciudades.
     */
    int numero_ciudades;

    /**
     * @brief Matriz de posiciones de ciudades.
     */
    vector<vector<double> > posiciones_ciudades;

    /**
     * @brief Matriz de distancias entre ciudades.
     */
    vector<vector<int> > distancias_ciudades;

    /**
     * @brief Distancia óptima.
     */
    int distancia_optima;

    /**
     * @brief Genera la matriz de distancias a partir de las posiciones de las ciudades.
     */
    void generaMatrizDistancias();

    /**
     * @brief Calcula la distancia entre dos ciudades.
     * @param ciudad_1 Primera ciudad.
     * @param ciudad_2 Segunda ciudad.
     * @return Distancia entre ciudad_1 y ciudad_2.
     */
    int calculaDistancia(int ciudad_1, int ciudad_2);

    /**
     * @brief Elimina el contenido de las estructuras de datos de la clase y la prepara para leer un nuevo fichero de especificación TSP.
     */
    void limpia();
};

#endif // DATOSPROBLEMA_H
