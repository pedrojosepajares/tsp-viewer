#include "ventanaseleccionunalgoritmo.h"
#include "ui_ventanaseleccionunalgoritmo.h"

VentanaSeleccionUnAlgoritmo::VentanaSeleccionUnAlgoritmo(vector<Ejecucion> ejecuciones, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaSeleccionUnAlgoritmo)
{
    ui->setupUi(this);

    // Se establece el nombre de la ventana
    this->setWindowTitle("Selección de ejecuciones");

    // Conexión entre pulsar el boton "Aceptar" y el slot nuevaEjecucion()
    connect(ui->boton_aceptar, SIGNAL(clicked()),this, SLOT(accept()));

    stringstream stream_n_mejoras, stream_coste;
    QStringList textos_ejecuciones;
    for (unsigned int i=0; i<ejecuciones.size(); i++){
        stream_n_mejoras.str("");
        stream_coste.str("");
        stream_n_mejoras << ejecuciones[i].soluciones.size()-1;
        stream_coste << ejecuciones[i].soluciones[ ejecuciones[i].soluciones.size()-1].getCoste();
        textos_ejecuciones.push_back(QString::fromStdString(ejecuciones[i].nombre_algoritmo +  + " (" + stream_n_mejoras.str() +" mejoras, mejor coste: "+ stream_coste.str() + ")"));
    }
    ui->combo_lista_algoritmos->addItems(textos_ejecuciones);
}

VentanaSeleccionUnAlgoritmo::~VentanaSeleccionUnAlgoritmo()
{
    delete ui;
}

int VentanaSeleccionUnAlgoritmo::getEjecucionSeleccionada(){
    return ui->combo_lista_algoritmos->currentIndex();
}

