#ifndef VENTANASELECCIONVARIOSALGORITMOS_H
#define VENTANASELECCIONVARIOSALGORITMOS_H

#include <QDialog>
#include <vector>
#include <ListaAlgoritmos.h>

using namespace std;

namespace Ui {
class VentanaSeleccionVariosAlgoritmos;
}

/**
 * @brief Permite al usuario seleccionar varios algoritmos.
 */
class VentanaSeleccionVariosAlgoritmos : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por parámetros.
     * @param lista_algoritmos Lista de algoritmos seleccionables.
     * @param parent Padre.
     */
    explicit VentanaSeleccionVariosAlgoritmos(ListaAlgoritmos* lista_algoritmos, QWidget *parent = 0);

    /**
     * @brief Constructor por parámetros.
     * @param nombres_algoritmos Conjunto de nombres de los algritmos seleccionables.
     * @param parent Padre.
     */
    explicit VentanaSeleccionVariosAlgoritmos(vector<string> nombres_algoritmos, QWidget *parent = 0);
    ~VentanaSeleccionVariosAlgoritmos();

    /**
     * @brief Calcula las ejecuciones selecionadas.
     * @return Ejecuciones seleccionadas.
     */
    inline vector<int> getEjecucionesSeleccionadas(){return this->lista_algoritmos->getAlgoritmosSeleccionados();};

protected:
    Ui::VentanaSeleccionVariosAlgoritmos *ui;

    /**
     * @brief Lista que contiene los algoritmos seleccionables.
     */
    ListaAlgoritmos* lista_algoritmos;

};

#endif // VENTANASELECCIONVARIOSALGORITMOS_H
