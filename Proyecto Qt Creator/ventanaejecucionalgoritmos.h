#ifndef VENTANAEJECUCIONALGORITMOS_H
#define VENTANAEJECUCIONALGORITMOS_H

#include <QDialog>
#include <ListaAlgoritmos.h>
#include <vector>

namespace Ui {
class VentanaEjecucionAlgoritmos;
}

/**
 * @brief Ventana donde se seleccionan los algoritmos que van a resolver un problema TSP así como un criterio de parada.
 */
class VentanaEjecucionAlgoritmos : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por parámentros
     * @param nombre_algoritmos Cadenas de texto con los algoritmos a ejecutar.
     * @param parent Padre.
     */
    explicit VentanaEjecucionAlgoritmos(vector<string> nombre_algoritmos, QWidget *parent = 0);
    ~VentanaEjecucionAlgoritmos();

    /**
     * @brief Calcula lo enteros asociados a los algoritmos seleccionados.
     * @return Vector de índices asociados a los algoritmos seleccionados.
     */
    vector<int> getAlgoritmosAEjecutar();

    /**
     * @brief Consultor del criterio de parada tiempo
     * @return Tiempo
     */
    double getTiempo();

    /**
     * @brief Consultor del criterio de para número de evaluaciones.
     * @return Número de evaluaciones.
     */
    int getEvaluaciones();

    /**
     * @brief Consultor del criterio de para número de iteraciones.
     * @return Número de iteraciones.
     */
    int getIteraciones();

    
protected:
    Ui::VentanaEjecucionAlgoritmos *ui;

    /**
     * @brief Panel con objetos seleccionables donde aparecen los algoritmos que se pueden ejecutar.
     */
    ListaAlgoritmos* lista_algoritmos;


protected slots:
    /**
     * @brief Activa o desactiva el botón "Ejecutar" en función de las opciones seleccionadas.
     */
    void actualizaComponenteVentana();

};

#endif // VENTANAEJECUCIONALGORITMOS_H
