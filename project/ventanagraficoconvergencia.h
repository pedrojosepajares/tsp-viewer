#ifndef VENTANAGRAFICOCONVERGENCIA_H
#define VENTANAGRAFICOCONVERGENCIA_H

#include <QDialog>
#include <graficoconvergencia.h>

namespace Ui {
class VentanaGraficoConvergencia;
}

/**
 * @brief Ventana que contiene un gráfico de convergencia de la solución de varios algoritmos.
 */
class VentanaGraficoConvergencia : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por parámetros.
     * @param ejecuciones Conjunto de ejecuciones proporcionadas por varios algoritmos.
     * @param nombre_problema Nombre del problema.
     * @param parent Padre.
     */
    explicit VentanaGraficoConvergencia(vector<Ejecucion>& ejecuciones, const string nombre_problema, QWidget *parent = 0);
    ~VentanaGraficoConvergencia();
    
protected:
    Ui::VentanaGraficoConvergencia *ui;

    /**
     * @brief Gráfico de convergencia.
     */
    GraficoConvergencia* grafico;

protected slots:
    /**
     * @brief Hace un cambio en la unidad que muesta el eje de abscisas.
     * @param indice Define la unidad del eje de abscidad: tiempo = 0, evaluaciones = 1, iteraciones = 2.
     */
    void cambiarEje(int indice);
};

#endif // VENTANAGRAFICOCONVERGENCIA_H
