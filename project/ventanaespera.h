#ifndef VENTANAESPERA_H
#define VENTANAESPERA_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QProgressBar>
#include <string>
#include "ui_ventanaespera.h"

using namespace std;

/**
 * @brief Muesta el progeso de la ejecuión de un algoritmo.
 */
class BarraProgresoAlgoritmo : public QVBoxLayout {
    Q_OBJECT

public:
    /**
     * @brief Constructor por parámetros.
     * @param nombre_algoritmo Nombre del algoritmo.
     */
    BarraProgresoAlgoritmo(string nombre_algoritmo);
    ~BarraProgresoAlgoritmo();
    /**
     * @brief Cambia el progreso que muentra la barra de progreso.
     * @param nuevo_valor Nuevo progreso.
     */
    void actualizaBarraProgreso(int nuevo_valor);

protected:
    /**
     * @brief Contiene la barra de progreso y el nombre del algoritmo.
     */
    QGroupBox* contenedor;

    /**
     * @brief Zona de se muestra la barra de progreso.
     */
    QVBoxLayout* layout_barra_progreso;

    /**
     * @brief Muestra el progreso de un algoritmo durante una ejecución.
     */
    QProgressBar* barra_progreso;
};


namespace Ui {

class VentanaEspera;
}

/**
 * @brief Informa al usuario sobre el progreso en base a los criterio de parada de la ejecución de los algoritmos que ha seleccionado para resolver un problema TSP
 */
class VentanaEspera : public QDialog{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por defecto.
     * @param parent Padre.
     */
    explicit VentanaEspera(QWidget *parent = 0);
    ~VentanaEspera();

    /**
     * @brief Ejecuta la Ventana de Espera y la hace visible al usuario.
     * @return Bandera que muestra el resultado de la ejecución de la ventana.
     */
    int exec();

    /**
     * @brief Genera las barras de progreso y la incializa a cero.
     * @param nombres_algoritmos Nombres de los algoritmos a ejecutar.
     */
    void inicializaBarrasProgreso(vector<string> nombres_algoritmos);
    
protected:
    Ui::VentanaEspera *ui;

    /**
     * @brief Barras de progreso.
     */
    vector<BarraProgresoAlgoritmo*> barras_progreso_algoritmos;

    /**
     * @brief Un elemento del vector es verdadero si la barra de progreso asociada continúa activa.
     */
    vector<bool> barras_activas;

public slots:
    /**
     * @brief Modifica el valor del progreso de una barra de progreso.
     * @param nuevo_valor Nuevo valor.
     * @param id_barra_progreso Identificador de la barra de progreso a modificar su valor.
     */
    void actualizaBarraProgreso(int nuevo_valor, int id_barra_progreso);

};

#endif // VENTANAESPERA_H
