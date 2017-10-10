#ifndef VENTANAAYUDA_H
#define VENTANAAYUDA_H

#include <QDialog>
#include <QTabWidget>
#include <QTextBrowser>
#include <QHelpEngine>
#include <QHelpContentWidget>
#include <QHelpIndexWidget>
#include <QTreeWidget>
#include <QSplitter>

#include <iostream>
using namespace std;

namespace Ui {
class VentanaAyuda;
}

/**
 * @brief Muestra al usuario ayuda sobre la utilización del sistema.
 */
class HelpBrowser : public QTextBrowser
{
    Q_OBJECT

public:
    /**
     * @brief Constructor por parámetros.
     * @param motor_ayuda Objeto que lee los ficheros html comprimidos que contienen la ayuda.
     * @param parent Padre.
     */
    HelpBrowser(QHelpEngine* motor_ayuda, QWidget *parent);

private:
    /**
     * @brief Carga en el panel de texto una Url
     * @param type Tipo.
     * @param name Nombre de la Url.
     * @return Unión de tipos comunes.
     */
    QVariant loadResource(int type, const QUrl &name);

    /**
     * @brief Objeto que lee los ficheros html comprimidos que contienen la ayuda.
     */
    QHelpEngine *motor_ayuda;
};


/**
 * @brief Ventana que contiene el índice de ayuda y la ayuda al usuario.
 */
class VentanaAyuda : public QDialog
{
    Q_OBJECT
    
public:
    /**
     * @brief Constructor por defecto.
     * @param parent Padre.
     */
    explicit VentanaAyuda(QWidget *parent = 0);
    ~VentanaAyuda();
    
protected:
    Ui::VentanaAyuda *ui;

    /**
     * @brief Carga los ficheros de html de ayuda y los gestiona.
     */
    QHelpEngine* motor_ayuda;

    /**
     * @brief Contiene el índice de ayuda y la ayuda al usuario.
     */
    QSplitter* panel;

    /**
     * @brief Contiene la ayuda al usuario.
     */
    HelpBrowser* helpBrowser;
};

#endif // VENTANAAYUDA_H
