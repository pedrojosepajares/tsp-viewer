#include "ventanavideo.h"
#include "ui_ventanavideo.h"

VentanaVideo::VentanaVideo(vector<Ejecucion>* ejecuciones, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaVideo)
{
    ui->setupUi(this);

    // Se establece el nombre de la ventana
    this->setWindowTitle("Configuración de vídeo");

    // Conexiones
    // Conexión entre pulsar el botón "Examinar" y el slot "cambioRuta"
    connect(ui->boton_examinar,SIGNAL(clicked()),this,SLOT(examinarRuta()));

    // Conexión entre pulsar el botón "Seleccionar" y el slot "seleccionarRuta"
    connect(ui->boton_seleccionar_ejecucion,SIGNAL(clicked()),this,SLOT(seleccionarEjecucion()));

    // Conexión entre pulsar el botón "Generar vídeo" y el slot "accept()"
    connect(ui->boton_generar_video,SIGNAL(clicked()),this,SLOT(accept()));

    ui->edit_ejecucion->setEnabled(false);
    ui->edit_ruta->setEnabled(true);

    this->ejecuciones = ejecuciones;
}

VentanaVideo::~VentanaVideo()
{
    delete ui;
}

void VentanaVideo::examinarRuta(){
    // Contiene las distintas palabras de la ruta que quedan cuando se eliminan los separadores
    QStringList palabras_ruta;

    // Se abre un cuadro de diálogo para que el usuario seleccione dónde guardar el fichero
    this->ruta = QFileDialog::getSaveFileName(this, tr("Seleccione dónde guardar el vídeo"),
                            "C:",
                            tr("Formato de vídeo (*.avi)"));

    if (this->ruta != ""){
        // Se muentra la ruta en el edit de la ventana
        ui->edit_ruta->setText(this->ruta);

        // Se separa la ruta en palabras
        palabras_ruta = ruta.split("/");

        // El nombre del fichero es la última palabra de la ruta
        this->nombre_fichero = palabras_ruta.value(palabras_ruta.size()-1);

        // Se convierte la ruta del fichero del problema en una ruta válida para abrir el fichero
        // procurando no añadir "\\" al final de la ruta

        this->ruta.clear();
        for (int i=0; i<palabras_ruta.size(); i++){
            this->ruta.push_back(palabras_ruta.value(i));
            if (palabras_ruta.value(i) != this->nombre_fichero){
                this->ruta.push_back("\\");
            }
        }
    }
}

void VentanaVideo::seleccionarEjecucion(){
    // Se genera una nueva ventana de selección de un algoritmo
    VentanaSeleccionUnAlgoritmo* v_seleccion = new VentanaSeleccionUnAlgoritmo(*(this->ejecuciones));
    if (v_seleccion->exec()){
        // Se almacena el índice de la ejecución seleccionada
        this->indice_ejecucion = v_seleccion->getEjecucionSeleccionada();

        // Se muentra el nombre de la ejecución en la ventana
        ui->edit_ejecucion->setText(QString::fromStdString(this->ejecuciones->at(this->indice_ejecucion).nombre_algoritmo));
    }

    // Se elimina la ventana
    delete v_seleccion;
}

int VentanaVideo::getDuracionVideo(){
    return ui->spin_duracion->value();
}
