#include "video.h"

Video::Video(GraficoEvolucionSolucion* grafico, int sps, int alto_video, int ancho_video)
{
    this->grafico = grafico;
    this->sps = sps;
    this->alto_video = alto_video;
    this->ancho_video = ancho_video;
}

// Destructor de la clase
Video::~Video(){
    this->grafico = 0;
}

void Video::guardaVideo(string ruta){
    QImage imagen;
    Mat matriz;
    VideoWriter video_grafico(ruta, CV_FOURCC('M','J','P','G'), this->sps, Size(this->ancho_video,this->alto_video));

    for(int i=0; i<this->grafico->getNumeroSoluciones()+1; i++){
        imagen = grafico->getImagen(this->ancho_video, this->alto_video).toImage();
        QImage   swapped = imagen.rgbSwapped();
        matriz = cv::Mat( swapped.height(), swapped.width(), CV_8UC4, const_cast<uchar*>(swapped.bits()), swapped.bytesPerLine() ).clone();
        video_grafico.write(matriz);
        grafico->avanza();
    }
}


