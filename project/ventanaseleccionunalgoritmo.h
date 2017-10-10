#ifndef VENTANASELECCIONUNALGORITMO_H
#define VENTANASELECCIONUNALGORITMO_H

#include <QDialog>
#include <vector>
#include <string>
#include <Ejecucion.h>

using namespace std;

namespace Ui {
class VentanaSeleccionUnAlgoritmo;
}
/**
 * @brief Permite al usuario seleccionar un algoritmo heurístico.
 */
class VentanaSeleccionUnAlgoritmo : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por parámetros.
     * @param ejecuciones Ejecuciones.
     * @param parent Padre.
     */
    explicit VentanaSeleccionUnAlgoritmo(vector<Ejecucion> ejecuciones, QWidget *parent = 0);
    ~VentanaSeleccionUnAlgoritmo();

    /**
     * @brief Calcula la ejecución seleccionada.
     * @return Ejecución seleccionada.
     */
    int getEjecucionSeleccionada();
    
private:
    Ui::VentanaSeleccionUnAlgoritmo *ui;
};

#endif // VENTANASELECCIONUNALGORITMO_H
