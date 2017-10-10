#ifndef VIDEO_H
#define VIDEO_H

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv/highgui.h>
#include <string>
#include <Ejecucion.h>
#include <graficoevolucionsolucion.h>

using namespace std;
using namespace cv;

class Video
{
public:
    /**
     * @brief Constructor por parámetros.
     * @param grafico Gráfico a partir del cual se genera el vídeo.
     * @param sps Soluciones por segundo. Define la duración del vídeo.
     * @param alto_video Altura del vídeo.
     * @param ancho_video Anchura del vídeo.
     */
    Video(GraficoEvolucionSolucion* grafico, int sps, int alto_video, int ancho_video);

    // Destructor de la clase
    ~Video();

    /**
     * @brief Almacena el fichero de vídeo en la ruta indicada
     * @param ruta Ruta.
     */
    void guardaVideo(string ruta);

private:
    /**
     * @brief Gráfico a partir del cual se genera el vídeo.
     */
    GraficoEvolucionSolucion* grafico;

    /**
     * @brief Soluciones por segundo.
     */
    int sps;

    /**
     * @brief Alto del vídeo.
     */
    int alto_video;

    /**
     * @brief Ancho del vídeo.
     */
    int ancho_video;
};

#endif // VIDEO_H
