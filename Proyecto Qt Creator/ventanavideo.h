#ifndef VENTANAVIDEO_H
#define VENTANAVIDEO_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <ventanaseleccionunalgoritmo.h>
#include <ejecucion.h>

namespace Ui {
class VentanaVideo;
}

/**
 * @brief Ventana que muestra al usuario las distintas opciones para generar un vídeo.
 */
class VentanaVideo : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por parámetros.
     * @param ejecuciones Conjunto de ejecuciones.
     * @param parent Padre.
     */
    explicit VentanaVideo(vector<Ejecucion>* ejecuciones = 0,QWidget *parent = 0);
    ~VentanaVideo();

    /**
     * @brief Consultor del nombre del fichero de vídeo.
     * @return Nombre del fichero.
     */
    inline QString getNombreFichero(){return this->nombre_fichero;}

    /**
     * @brief Consultor de la ruta del fichero de vídeo.
     * @return Ruta del fichero de vídeo.
     */
    inline QString getRuta(){return this->ruta;}

    /**
     * @brief Consultor del índice de ejecución del algoritmos heurístico que proporciona la solución.
     * @return Índice del algoritmo heurístico.
     */
    inline int getIndiceEjecucion(){return this->indice_ejecucion;}

    /**
     * @brief Consultor de la duración del vídeo.
     * @return Duración del video.
     */
    int getDuracionVideo();
    
protected:
    Ui::VentanaVideo *ui;

    /**
     * @brief Conjunto de ejecuciones seleccionables.
     */
    vector<Ejecucion>* ejecuciones;

    /**
     * @brief Ruta del vídeo.
     */
    QString ruta;

    /**
     * @brief Nombre del vídeo.
     */
    QString nombre_fichero;

    /**
     * @brief Índice de la ejecución seleccionada.
     */
    int indice_ejecucion;

private slots:
    /**
     * @brief Abre un cuadro de navegación por el sistema de ficheros y permite seleccionar un fichero.
     */
    void examinarRuta();

    /**
     * @brief Abre una ventana de Selección de un Algoritmo.
     */
    void seleccionarEjecucion();
};

#endif // VENTANAVIDEO_H
