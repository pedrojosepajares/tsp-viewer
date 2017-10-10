#include "ventanaespera.h"

BarraProgresoAlgoritmo::BarraProgresoAlgoritmo(string nombre_algoritmo){
    // Se genera un nuevo QGroupBox cuyo texto es el nombre del algoritmo;
    this->contenedor = new QGroupBox(QString::fromStdString(nombre_algoritmo));
    // Se genera una nueva barra de progreso
    this->barra_progreso = new QProgressBar();
    // Se genera un nuevo layout para la barra de progreso
    this->layout_barra_progreso = new QVBoxLayout();
    // Se establece el valor inicial de la barra a cero
    this->barra_progreso->setValue(0);
    // Se añade la barra de progreso al layout de la barra de progreso
    this->layout_barra_progreso->addWidget(this->barra_progreso);
    // Se añader el layout de la barra de progreso al contenedor
    this->contenedor->setLayout(this->layout_barra_progreso);
    // Se añade el contenedor al layout
     this->addWidget(this->contenedor);
}

BarraProgresoAlgoritmo::~BarraProgresoAlgoritmo(){
    delete this->barra_progreso;
    delete this->layout_barra_progreso;
    delete this->contenedor;
}

void BarraProgresoAlgoritmo::actualizaBarraProgreso(int nuevo_valor){
    this->barra_progreso->setValue(nuevo_valor);
    if (nuevo_valor == 100){
        this->contenedor->hide();
        this->barra_progreso->hide();
    }
}

VentanaEspera::VentanaEspera(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaEspera){
    ui->setupUi(this);

    // Se establece el nombre de la ventana
    this->setWindowTitle("Ejecución de algoritmos");

    // Conexión entre pulsar el botón "Cancelar ejecución" y el slot (reject())
    connect(ui->boton_cancelar_ejecucion, SIGNAL(clicked()),this, SLOT(reject()));

    // Las barras de progreso deben ir acumulándose desde arriba a la izquierda
    ui->layout_progreso_algoritmo->setAlignment(Qt::AlignTop | Qt::AlignLeft);

}

VentanaEspera::~VentanaEspera(){
    delete ui;
    for (unsigned int i=0; i<this->barras_progreso_algoritmos.size(); i++){
        delete this->barras_progreso_algoritmos[i];
    }
}

int VentanaEspera::exec(){
    return QDialog::exec();
}

void VentanaEspera::inicializaBarrasProgreso(vector<string> nombres_algoritmos){

    // En el caso de que ya se encuentren inicializadas las barras de progreso se limpian
    if (!this->barras_progreso_algoritmos.empty()){
        for (unsigned int i=0; i<this->barras_progreso_algoritmos.size(); i++){
            delete this->barras_progreso_algoritmos[i];
        }
        this->barras_progreso_algoritmos.clear();
    }    
    this->barras_activas.clear();

    // Reserva memoria e inicializa las barras de progreso para los algoritmos y
    // se incluyen en la ventana las barras de progreso
    for (unsigned int i=0; i<nombres_algoritmos.size(); i++){
        this->barras_progreso_algoritmos.push_back(new BarraProgresoAlgoritmo(nombres_algoritmos[i]));
        ui->layout_progreso_algoritmo->addLayout(this->barras_progreso_algoritmos[i]);
        // Se marcan todas las barras como activas
        this->barras_activas.push_back(true);
    }
}

void  VentanaEspera::actualizaBarraProgreso(int nuevo_valor, int id_barra_progreso){
    bool barra_activa = false;

    // Se actualiza en valor de la barra
    this->barras_progreso_algoritmos[id_barra_progreso]->actualizaBarraProgreso(nuevo_valor);

    // Si el valor a actualizar la barra es 100, se supone que el algoritmo ha concluido
    // y por tanto la barra se ha ocultado
    if (nuevo_valor == 100){
        this->barras_activas[id_barra_progreso] = false;

        // Se comprueban si todas las barras han llegado a 100. En ese caso la ventana se cierra
        // y exec() devuelve aceptado
        for (unsigned int i = 0; i<this->barras_activas.size() && !barra_activa; i++){
            if (this->barras_activas[i]){
                barra_activa = true;
            }
        }

        // Si no hay ninguna barra activa
        if (!barra_activa){
            emit accept();
        }
    }
}
