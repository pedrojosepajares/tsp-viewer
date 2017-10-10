#include "VentanaEjecucionAlgoritmos.h"
#include "ui_VentanaEjecucionAlgoritmos.h"

VentanaEjecucionAlgoritmos::VentanaEjecucionAlgoritmos(vector<string> nombres_algoritmos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaEjecucionAlgoritmos)
{
    ui->setupUi(this);

    // Se establece el nombre de la ventana
    this->setWindowTitle("Ejecución de algoritmos");

    // Conexión entre pulsar el boton "Ejecutar" y el slot accept()
    connect(ui->boton_ejecutar, SIGNAL(clicked()),this, SLOT(accept()));

    // Conexión entre los checks con la actualización de la ventana
    connect(ui->check_tiempo, SIGNAL(clicked()), this, SLOT(actualizaComponenteVentana()));

    // Conexión entre los checks con la actualización de la ventana
    connect(ui->check_evaluaciones, SIGNAL(clicked()), this, SLOT(actualizaComponenteVentana()));

    // Conexión entre los checks con la actualización de la ventana
    connect(ui->check_iteraciones, SIGNAL(clicked()), this, SLOT(actualizaComponenteVentana()));

    // Se añade a la interfaz la lista de algoritmos a seleccionar
    this->lista_algoritmos = new ListaAlgoritmos(nombres_algoritmos);
    ui->layout_algoritmos->addWidget(this->lista_algoritmos, Qt::AlignTop | Qt::AlignLeft);

    // Se actualizan los componentes de la ventana
    this->actualizaComponenteVentana();

}

VentanaEjecucionAlgoritmos::~VentanaEjecucionAlgoritmos(){
    delete this->lista_algoritmos;
}

vector<int> VentanaEjecucionAlgoritmos::getAlgoritmosAEjecutar(){
    // Se inicializa el vector con los índices de los elementos selccionados
    vector<int> indices = lista_algoritmos->getAlgoritmosSeleccionados();
    // Se inserta al final del vector las iteraciones de los algoritmos
    return indices;
}

void VentanaEjecucionAlgoritmos::actualizaComponenteVentana(){
    // Si al menos hay un criterio de parada activado se activa el botón de ejecutar
    if (ui->check_tiempo->isChecked() || ui->check_evaluaciones->isChecked() || ui->check_iteraciones->isChecked()){
        ui->boton_ejecutar->setEnabled(true);
    }
    else{
        ui->boton_ejecutar->setEnabled(false);
    }

    // Se activa el spinbox cerrespondiente a cada check activo
    if (ui->check_tiempo->isChecked()){
        ui->spin_tiempo->setEnabled(true);
    }
    else{
        ui->spin_tiempo->setEnabled(false);
    }

    if (ui->check_evaluaciones->isChecked()){
        ui->spin_evaluaciones->setEnabled(true);
    }
    else{
        ui->spin_evaluaciones->setEnabled(false);
    }

    if (ui->check_iteraciones->isChecked()){
        ui->spin_iteraciones->setEnabled(true);
    }
    else{
        ui->spin_iteraciones->setEnabled(false);
    }
}

double VentanaEjecucionAlgoritmos::getTiempo(){
    if (ui->check_tiempo->isChecked()){
        return ui->spin_tiempo->value();
    }
    else{
        return 0;
    }
}

int VentanaEjecucionAlgoritmos::getEvaluaciones(){
    if (ui->check_evaluaciones->isChecked()){
        return ui->spin_evaluaciones->value();
    }
    else{
        return 0;
    }
}

int VentanaEjecucionAlgoritmos::getIteraciones(){
    if(ui->check_iteraciones->isChecked()){
        return ui->spin_iteraciones->value();
    }
    else{
        return 0;
    }
}
