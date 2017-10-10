#ifndef GraficoConvergencia_H
#define GraficoConvergencia_H


#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <vector>
#include <ejecucion.h>

#include <iostream>

using namespace std;

/**
 * @brief Representación que muestra la convergencia de la función objetivo durante el proceso de ejecución del algoritmos. El valor de la función objetivo puede ser representado con respecto al tiempo, el número de evaluaciones o el número de iteraciones.
 */
class GraficoConvergencia : public QwtPlot{
public:
    /**
     * @brief Contructor por parámetros.
     * @param ejecuciones Vector de ejecuciones a representar.
     * @param nombre_problema Nombre del problema.
     */
    GraficoConvergencia(vector<Ejecucion>& ejecuciones, const string nombre_problema);

    /**
     * @brief Constructor por parámetros.
     * @param ejecuciones Vector de ejecuciones a representar.
     */
    GraficoConvergencia(vector<Ejecucion>* ejecuciones, const string nombre_problema);

    /**
     * @brief Realiza un cambio en el eje de abscisas
     * @param tipo Establece el tipo de unidad en el eje de abscisas: tiempo = 0, nº evaluaciones = 1, nº iteraciones = 2.
     */
    void cambioEje(int tipo);

    /**
     * @brief Consultor del mejor coste.
     * @return Coste de la solución con el menos coste.
     */
    inline int getMejorCoste(){return this->min_coste;};

    /**
     * @brief Consultor del peor coste.
     * @return Coste de la solución con peor coste.
     */
    inline int getPeorCoste(){return this->max_coste;};

    /**
     * @brief Consultor del nombre del mejor algoritmo.
     * @return Devuelve el nombre del algoritmo heurístico que ha generado la solución con el menor coste.
     */
    inline QString getMejorAlgoritmo(){return this->algoritmo_mejor_coste;};

    /**
     * @brief Consultor de peor algoritmo.
     * @return Devuelve el nombre del algoritmo heurístico que ha generado la solución con el mayor coste.
     */
    inline QString getPeorAlgoritmo(){return this->algoritmo_peor_coste;};

protected:
    /**
     * @brief Vector de ejecuciones representadas.
     */
    vector<Ejecucion>* ejecuciones;

    /**
     * @brief Conjunto de puntos para representar en el gráfico cuando la unidad del eje de abscisas es el tiempo.
     */
    vector<QPolygonF> conjuntos_puntos_tiempo;

    /**
     * @brief Conjunto de puntos para representar en el gráfico cuando la unidad del eje de abscisas es el número de evaluaciones.
     */
    vector<QPolygonF> conjuntos_puntos_evaluaciones;

    /**
     * @brief Conjunto de puntos para representar en el gráfico cuando la unidad del eje de abscisas es el número de iteraciones.
     */
    vector<QPolygonF> conjuntos_puntos_iteraciones;

    /**
     * @brief Conjunto de puntos para completar el final de la curva el gráfico cuando la unidad del eje de abscisas es el tiempo.
     */
    vector<QPolygonF> conjuntos_puntos_final_tiempo;

    /**
     * @brief Conjunto de puntos para completar el final de la curva en el gráfico cuando la unidad del eje de abscisas es el número de evaluaciones.
     */
    vector<QPolygonF> conjuntos_puntos_final_evaluaciones;

    /**
     * @brief Conjunto de puntos para completar el final de la curva en el gráfico cuando la unidad del eje de abscisas es el número de iteraciones.
     */
    vector<QPolygonF> conjuntos_puntos_final_itereaciones;

    /**
     * @brief Conjunto de curvas.
     */
    vector<QwtPlotCurve*> curvas;

    /**
     * @brief Conjunto de curvas que se superponen el final de las curvas reales para completarlas.
     */
    vector<QwtPlotCurve*> curvas_final;

    /**
     * @brief Nombre del problema.
     */
    QString nombre_problema;

    /**
     * @brief Lista de nombres de los algoritmos cuya ejecución se representa.
     */
    QStringList nombres_algoritmos;


    /**
     * @brief Nombre del algoritmo que presenta la solución final con el mejor coste.
     */
    QString algoritmo_mejor_coste;

    /**
     * @brief Nombre del algoritmo que presenta la solución final con el peor coste.
     */
    QString algoritmo_peor_coste;

    /**
     * @brief Coste de la solución final que presenta un mayor coste.
     */
    int max_coste;

    /**
     * @brief Coste de la solución final que presenta un menor coste.
     */
    int min_coste;

    /**
     * @brief Instante en el que se ha construido la solución final más tardía.
     */
    double max_tiempo;

    /**
     * @brief Instante en el que se ha construido la solución final más temprana.
     */
    double min_tiempo;

    /**
     * @brief Número de evaluaciones que presenta la solución final que se ha construido tras evaluar el mayor número de veces la función objetivo.
     */
    int max_evaluaciones;

    /**
     * @brief Número de evaluaciones que presenta la solución final que se ha construido tras evaluar el menor número de veces la función objetivo.
     */
    int min_evaluaciones;

    /**
     * @brief Número de iteración del algoritmo en la que se ha construido la solución tras un mayor número de iteraciones
     */
    int max_iteraciones;

    /**
     * @brief Número de iteración del algoritmo en la que se ha construido la solución tras un menor número de iteraciones
     */
    int min_iteraciones;

    /**
     * @brief Coste de la solución inicial de un algoritmo que presenta un coste mayor.
     */
    int peor_coste_inicial;

    /**
     * @brief Función auxiliar que permite ajustar los ejes de abscisas y ordenadas.
     * @return Mayor y menor valor para x y para y dentro de las curvas del gráfico.
     */
    vector<qreal> getDatosAjusteEje();
};

#endif // GraficoConvergencia_H
