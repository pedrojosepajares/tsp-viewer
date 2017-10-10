#include "ventanaayuda.h"
#include "ui_ventanaayuda.h"

HelpBrowser::HelpBrowser(QHelpEngine *motor_ayuda, QWidget *parent = 0){
    this->motor_ayuda = motor_ayuda;
    this->setSource(QUrl("qthelp://ayuda/doc/index.html"));
}

QVariant HelpBrowser::loadResource(int type, const QUrl &url)
{
    if (url.scheme() == "qthelp")
        return QVariant(this->motor_ayuda->fileData(url));
    else
        return QTextBrowser::loadResource(type, url);
}


VentanaAyuda::VentanaAyuda(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaAyuda)
{
    ui->setupUi(this);

    this->setWindowTitle("Ayuda");

    // Se carga la ayuda desde la carpeta "ayuda" en el directorio de la aplicación
    this->motor_ayuda = new QHelpEngine(QApplication::applicationDirPath()+"\\ayuda\\doc.qhc");
    this->motor_ayuda->setupData();

    // Se genera el panel que contendrá la información
    this->panel = new QSplitter(Qt::Horizontal);

    // Se genera el widget para contener la explicación
    this->helpBrowser = new HelpBrowser(this->motor_ayuda);

    // Se inserta el índice en el panel y se ajusta
    panel->insertWidget(0,this->motor_ayuda->contentWidget());
    panel->widget(0)->setMinimumWidth(300);
    panel->widget(0)->setMaximumWidth(300);

    // Se inserta la ayuda en el panel y se ajusta
    panel->insertWidget(1, helpBrowser);
    panel->widget(1)->setMinimumWidth(500);
    panel->widget(1)->setMaximumWidth(500);

    // Se conecta la ayuda con el índice
    connect(this->motor_ayuda->contentWidget(),
            SIGNAL(linkActivated(const QUrl &)),
            helpBrowser, SLOT(setSource(const QUrl &)));

    // Se añade el panel a la ventana
    ui->layout_general->addWidget(panel);
}

VentanaAyuda::~VentanaAyuda()
{
    delete this->motor_ayuda;
    delete this->helpBrowser;
    delete this->panel;
    delete ui;
}
