#include "VentanaEvolucionSolucion.h"
#include "ui_ventanaevolucionsolucion.h"

VentanaEvolucionSolucion::VentanaEvolucionSolucion(const vector<vector<double> > posiciones_ciudades,Ejecucion& ejecucion, const  string nombre_problema, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaEvolucionSolucion)
{
    ui->setupUi(this);

    // Se establece el nombre de la ventana
    this->setWindowTitle("Gráfico de evolución de una solución");

    // Se genera un nuevo gráfico y se incluye en el layour
    this->grafico = new GraficoEvolucionSolucion(posiciones_ciudades, ejecucion, nombre_problema);
    ui->layout_grafico->addWidget(grafico);


    // Conexión entre pulsar el boton "Siguiente" y el slot avanzaGrafico()
    connect(ui->boton_avanzar, SIGNAL(clicked()),this, SLOT(avanzaGrafico()));

    // Conexión entre pulsar el boton "Retrocede" y el slot retrocedeGrafico()
    connect(ui->boton_retroceder, SIGNAL(clicked()),this, SLOT(retrocedeGrafico()));

    // Conexión entre mover la barra de progreso  y el slot avanzaGraficoPorcentaje()
    connect(ui->barra_progeso, SIGNAL(valueChanged(int)),this, SLOT(avanzaGraficoPorcentaje(int)));

    // Se muestra el coste de la solución actual
    ui->label_valor_coste->setText(QString::number(this->grafico->getCoste()));

    // Se muestra el número de mejoras realizadas
    ui->label_valor_n_mejoras->setText(QString::number(this->grafico->getIndiceSolucion()));
}

VentanaEvolucionSolucion::~VentanaEvolucionSolucion()
{
    delete ui;
    delete this->grafico;
}

void VentanaEvolucionSolucion::avanzaGrafico(){
    this->grafico->avanza();
    ui->barra_progeso->setValue(this->grafico->getPorcentaje());

    // Se muestra el coste de la solución actual
    ui->label_valor_coste->setText(QString::number(this->grafico->getCoste()));

    // Se muestra el número de mejoras realizadas
    ui->label_valor_n_mejoras->setText(QString::number(this->grafico->getIndiceSolucion()));
}

void VentanaEvolucionSolucion::retrocedeGrafico(){
    this->grafico->retrocede();
    ui->barra_progeso->setValue(this->grafico->getPorcentaje());
    // Se muestra el coste de la solución actual
    ui->label_valor_coste->setText(QString::number(this->grafico->getCoste()));

    // Se muestra el número de mejoras realizadas
    ui->label_valor_n_mejoras->setText(QString::number(this->grafico->getIndiceSolucion()));

}

void VentanaEvolucionSolucion::playGrafico(){
    this->grafico->play();
}

void VentanaEvolucionSolucion::avanzaGraficoPorcentaje(int porcentaje){
    this->grafico->avanza(porcentaje);
    // Se muestra el coste de la solución actual
    ui->label_valor_coste->setText(QString::number(this->grafico->getCoste()));

    // Se muestra el número de mejoras realizadas
    ui->label_valor_n_mejoras->setText(QString::number(this->grafico->getIndiceSolucion()));
}

