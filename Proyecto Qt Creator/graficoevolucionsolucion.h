#include <solucion.h>
#include <string>
#include <vector>
#include <QPixmap>
#include <qwt_symbol.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_text.h>
#include <ejecucion.h>
#include <time.h>
#include <windows.h>

#ifndef GraficoEvolucionSolucion_H
#define GraficoEvolucionSolucion_H

using namespace std;

/**
 * @brief Conjunto de representaciones que utlizan nodos y arcos para reflejar ciudades y caminos entre ellas.
 */
class GraficoEvolucionSolucion : public QwtPlot{
public:
    /**
     * @brief Construtor por parámetros.
     * @param posiciones_ciudades Matriz de posiciones para las ciudades.
     * @param ejecucion Ejecución a representar.
     * @param nombre_problema Nombre del problema resuelto.
     */
    GraficoEvolucionSolucion(const vector<vector<double> >& posiciones_ciudades,Ejecucion& ejecucion, const  string nombre_problema);

    ~GraficoEvolucionSolucion();

    /**
     * @brief Sustituye la solución actualmente representada por la siguiente mejor.
     */
    void avanza();

    /**
     * @brief Sustituye la solución actualmente representada por la que se corresponde con el porcentaje indicado con respecto al total de soluciones de la ejecución.
     * @param porcentaje Porcentaje del total de soluciones que hace referancia a la solución a representar.
     */
    void avanza(double porcentaje);

    /**
     * @brief Sustituye la solución actualmente representada por la anterior mejor.
     */
    void retrocede();

    /**
     * @brief Avanza a través de la soluciones pasado un intervalo de tiempo.
     */
    void play();

    /**
     * @brief Genera una imagen a partir de un gráfico.
     * @param ancho Ancho de la imagen.
     * @param alto Alto de la imagen.
     * @return Imagen a partir del gráfico.
     */
    QPixmap getImagen(int ancho, int alto);

    /**
     * @brief Consultor del número de soluciones representables.
     * @return Número de soluciones representables.
     */
    inline int getNumeroSoluciones(){return this->soluciones.size();};

    /**
     * @brief Consultor del porcentaje del total al que pertenece la solución representada.
     * @return  Porcentaje del total al que pertenece la solución representada.
     */
    inline double getPorcentaje(){return  (this->indice_solucion_grafico/(float)(this->soluciones.size()-1))*100.0;};

    /**
     * @brief Consultor del coste de la solución actual.
     * @return Coste de la solución actual.
     */
    inline int getCoste(){return this->soluciones[this->indice_solucion_grafico].getCoste();};

    /**
     * @brief Consultor del índice correspondiente a la solución que se está representando.
     * @return Índice de la solución que se está representando.
     */
    inline int getIndiceSolucion(){return this->indice_solucion_grafico;};



private:
    /**
     * @brief Gráfico.
     */
    QwtPlot grafico;

    /**
     * @brief Altura del gráfico.
     */
    int altura_grafico;

    /**
     * @brief Anchura del gráfico.
     */
    int anchura_grafico;

    /**
     * @brief Índice en el vector de soluciones que ocupa la solución que se muestra en el gráfico.
     */
    unsigned int indice_solucion_grafico;

    /**
     * @brief Vector de arcos que unen ciudades en el gráfico.
     */
    vector<QPolygonF> arcos;

    /**
     * @brief Vector que contiene las posiciones de las ciudades en el gráfico.
     */
    vector<QPointF> posiciones_ciudades;

    /**
     * @brief Vector de soluciones.
     */
    vector<Solucion> soluciones;

    /**
     * @brief Símbolo gráfico con el que se representa una ciudad.
     */
    QwtSymbol *simbolo_ciudad;

    /**
     * @brief Línea que conecta las ciudades en el gráfico.
     */
    QwtPlotCurve *linea_union_ciudades;

    /**
     * @brief Nombre del problema.
     */
    QString nombre_problema;

    /**
     * @brief Nombre del algoritmo.
     */
    QString nombre_algoritmo;

    /**
     * @brief Calcula los valores maximos y mínimos para x e y ocupados por una ciudad en el plano.
     * @return
     */
    vector<int> LimitesMaxMinXY();

    /**
     * @brief Actualiza el gráfico mostrando una nueva solución.
     */
    void actualiza();

};

#endif // GraficoEvolucionSolucion_H
