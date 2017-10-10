#include "ventanaseleccionvariosalgoritmos.h"
#include "ui_ventanaseleccionvariosalgoritmos.h"

VentanaSeleccionVariosAlgoritmos::VentanaSeleccionVariosAlgoritmos(ListaAlgoritmos* lista_algoritmos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaSeleccionVariosAlgoritmos)
{
    ui->setupUi(this);

    // Se establece el nombre de la ventana
    this->setWindowTitle("Selección de algoritmos");

    // Conexión entre pulsar la acción "Aceptar" y el slot accept()
    connect(ui->boton_aceptar,SIGNAL(clicked()), this,SLOT(accept()));

    this->lista_algoritmos = new ListaAlgoritmos(lista_algoritmos);
    ui->layout_lista_algoritmos->addWidget(this->lista_algoritmos);
}

VentanaSeleccionVariosAlgoritmos::VentanaSeleccionVariosAlgoritmos(vector<string> nombres_algoritmos, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaSeleccionVariosAlgoritmos)
{
    ui->setupUi(this);

    // Conexión entre pulsar la acción "Aceptar" y el slot accept()
    connect(ui->boton_aceptar,SIGNAL(clicked()), this,SLOT(accept()));

    this->lista_algoritmos = new ListaAlgoritmos(nombres_algoritmos);
    ui->layout_lista_algoritmos->addWidget(this->lista_algoritmos);
}


VentanaSeleccionVariosAlgoritmos::~VentanaSeleccionVariosAlgoritmos()
{
    delete ui;
    delete lista_algoritmos;
}
