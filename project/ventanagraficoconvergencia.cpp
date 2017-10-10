#include "ventanagraficoconvergencia.h"
#include "ui_ventanagraficoconvergencia.h"

VentanaGraficoConvergencia::VentanaGraficoConvergencia(vector<Ejecucion> &ejecuciones, const string nombre_problema, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaGraficoConvergencia)
{
    ui->setupUi(this);

    // Conexión entre el combo box eje y el slot cambiarEje()
    connect(ui->combo_box_eje, SIGNAL(currentIndexChanged(int)),this, SLOT(cambiarEje(int)));

    // Se establece el nombre de la ventana
    this->setWindowTitle("Gráfico de convergencia");

    // Se genera un nuevo gráfico de convergencia y se añade a la interfaz
    this->grafico = new GraficoConvergencia(&ejecuciones, nombre_problema);
    ui->layout_grafico->addWidget(grafico);
    ui->label_mejor_solucion->setText("Mejor solución: " + QString::number(this->grafico->getMejorCoste()) +
                                      " (" + this->grafico->getMejorAlgoritmo() + ")" );
    ui->label_peor_solucion->setText( "Peor solución:   " + QString::number(this->grafico->getPeorCoste()) +
                                     " (" + this->grafico->getPeorAlgoritmo() + ")" );


}

VentanaGraficoConvergencia::~VentanaGraficoConvergencia()
{
    delete ui;
    delete this->grafico;
}

void VentanaGraficoConvergencia::cambiarEje(int indice){
    this->grafico->cambioEje(indice);
}
