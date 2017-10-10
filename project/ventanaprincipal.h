#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QFileDialog>
#include <vector>
#include <ventanaseleccionunalgoritmo.h>
#include <ventanaseleccionvariosalgoritmos.h>
#include <graficoevolucionsolucion.h>
#include <graficoconvergencia.h>
#include <ventanaespera.h>
#include <ventanaejecucionalgoritmos.h>
#include <ventanaevolucionsolucion.h>
#include <ventanagraficoconvergencia.h>
#include <ventanavideo.h>
#include <ventanaayuda.h>
#include <algoritmoinsercion.h>
#include <algoritmovecinomascercano.h>
#include <algoritmograsp.h>
#include <algoritmoils.h>
#include <algoritmosa.h>
#include <algoritmoga.h>
#include <algoritmoaco.h>
#include <algoritmosaal.h>
#include <datosproblema.h>
#include <algoritmogaal.h>
#include <listaalgoritmos.h>
#include <QtConcurrent/QtConcurrentRun>
#include <string>
#include <ejecucion.h>
#include <sstream>
#include <video.h>



#include <iostream>


#define C_ACO 0
#define C_GA 1
#define C_GAAL 2
#define C_GRASP 3
#define C_ILS 4
#define C_INSERCION 5
#define C_SA 6
#define C_SAAL 7
#define C_VECINO 8




using namespace cv;
namespace Ui {class VentanaPrincipal;}
/**
 * @brief Ventana principal. Está dividida en tres zonas que permiten la carga de un problam TSP, la gestión de ejecuciones de algoritmos y la generación de presentaciones.
 */
class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por defecto.
     * @param parent Padre.
     */
    explicit VentanaPrincipal(QWidget *parent = 0);
    ~VentanaPrincipal();

private slots:
    /**
     * @brief Gestiona la carga en el sistema de una nuevo fichero de especificación TSP.
     */
    void cambioFicheroProblema();

    /**
     * @brief Muestra el usuario la ventana de ayuda.
     */
    void abrirAyuda();

    /**
     * @brief Muestra al usuario la ventana de ejecución de algoritmos.
     */
    void nuevaEjecucion();

    /**
     * @brief Genera un nuevo gráfico de convergencia para varios algoritmos.
     */
    void nuevaGraficoConvergencia();

    /**
     * @brief Genera un nuevo gráfico de evolución de una solución.
     */
    void nuevaRepresentacionSolucion();

    /**
     * @brief Genera un vídeo de evolución de uan solución.
     */
    void nuevoVideo();

    /**
     * @brief Elimina una o varias ejecuciones.
     */
    void eliminarEjecuciones();

    /**
     * @brief Elimina todas las ejecuciones.
     */
    void eliminarTodasEjecuciones();

signals:
    /**
     * @brief Señal que cancela la ejecución de todos los algoritmos.
     */
    void cancelaEjecucionAlgoritmo();
    
private:
    Ui::VentanaPrincipal *ui;
    /**
     * @brief Ruta en sistema de fichero del fichero de especificación TSP.
     */
    QString ruta_fichero_problema;

    /**
     * @brief Nombre del problema TSP.
     */
    QString nombre_problema;

    /**
     * @brief Datos leídos desde el fichero de especificación TSP.
     */
    DatosProblema datos_problema;    

    /**
     * @brief Contiene los algoritmos heurísticos que resuelven TSP.
     */
    vector<HeuristicaTSP*> algoritmos;

    /**
     * @brief Nombres de algoritmos heurísticos.
     */
    vector<string> nombres_algoritmos;

    /**
     * @brief Ejecuciones. Son el resultado de resolver un problema TSP con algún algortimo heurístico.
     */
    vector<Ejecucion> ejecuciones;

    /**
     * @brief Lista donde aparecen las ejecuciones terminadas.
     */
    ListaAlgoritmos* lista_ejecuciones;

    /**
     * @brief Ventana donde aparecen las barras de progreso que informan sobre el proceso de ejecución de los algoritmos.
     */
    VentanaEspera* ventana_espera;



    /**
     * @brief Inicializa las estructoras de datos de los algoritmos, estableciendo para el ellos el problema TSP cargado en el sistema.
     */
    void inicializaAlgoritmos();

    /**
     * @brief Almecenan el resultado de ejecutar de forma concurrente varios algorimos heurísticos.
     * @param id_algoritmos Identeficadores de los algoritmos a ejecutar.
     * @param citerios_parada Criterios de parada.
     * @return Variable que contiene los resultados de las ejecuciones una vez concluidas.
     */
    vector<QFuture<vector<Solucion> > > resolverVariosAlgoritmos(vector<int> id_algoritmos, vector<CriterioParada>& citerios_parada);

    // Devuelve true en el caso de que se hayan cancelado ejecuciones porque no están terminadas
    // Cancela y espera a que termine la ejecución de todos los algoritmos en el caso de que no hayan terminado
    /**
     * @brief Termina las ejecuciones actuales.
     * @param ejecuciones Ejecuciones activas.
     * @return  Verdadero en caso de que se haya detenido alguna ejecución. Falso en otro caso.
     */
    bool cancelaEjecucionesNoTerminadas(vector<QFuture<vector<Solucion> > > ejecuciones);

    // Añade a la lista de ejecuciones las ejecuciones terminadas y agrega los resultados al vector
    // de resultados de ejecuciones
    /**
     * @brief Incluye las nuevas ejecuciones terminadas en la lista de ejecuciones.
     * @param soluciones_ejecuciones Resultados de las ejecuciones de los algoritmos.
     * @param id_algoritmos_ Algoritmos heurísticos ejecutados.
     * @param criterio_parada Criterio de parada para los algoritmos.
     */
    void actualizaNuevasEjecuciones(vector<vector<Solucion> > soluciones_ejecuciones, vector<int> id_algoritmos_, vector<CriterioParada> criterio_parada);

    /**
     * @brief Activa o desactiva opciones la ventana principal en función del estado en el que se encuentre el sistema.
     */
    void actualizaComponentesVentana();

};

#endif // VENTANAPRINCIPAL_H
