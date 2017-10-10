#ifndef VENTANAEVOLUCIONSOLUCION_H
#define VENTANAEVOLUCIONSOLUCION_H

#include <QDialog>
#include <graficoevolucionsolucion.h>
namespace Ui {
class VentanaEvolucionSolucion;
}

/**
 * @brief Ventana que contiene un gráfico de evolución de una solución.
 */
class VentanaEvolucionSolucion : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por parámetros.
     * @param posiciones_ciudades Matriz de posiciones para las ciudades.
     * @param ejecucion Ejecución a representar.
     * @param nombre_problema Nombre del problema resuelto.
     * @param parent Padre.
     */
    explicit VentanaEvolucionSolucion(vector<vector<double> > posiciones_ciudades,Ejecucion& ejecucion, const  string nombre_problema ,QWidget *parent = 0);
    ~VentanaEvolucionSolucion();
    
protected:
    Ui::VentanaEvolucionSolucion *ui;
    /**
     * @brief Gráfico de evolución de una solución.
     */
    GraficoEvolucionSolucion* grafico;

protected slots:
    /**
     * @brief El gráfico sustituye la solución actual por la siguiente mejor solución.
     */
    void avanzaGrafico();

    /**
     * @brief El gráfico sustituye la solución actual por la anteorior mejor solución.
     */
    void retrocedeGrafico();

    /**
     * @brief  El gráfico sustituye la solución actual por la solución que se corresponde con un porcentaje dado del total de soluciones.
     * @param porcentaje Porcentaje del total de soluciones.
     */
    void avanzaGraficoPorcentaje(int porcentaje);

    /**
     * @brief Sustituye la solución actual por la siguiente mejor solución de forma sucesiva manteniendo cada solución un intervalo de tiempo en el gráfico.
     */
    void playGrafico();

};

#endif // VENTANAEVOLUCIONSOLUCION_H
