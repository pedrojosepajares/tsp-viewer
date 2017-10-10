#-------------------------------------------------
#
# Project created by QtCreator 2015-10-16T16:06:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TFG
TEMPLATE = app
CONFIG += qwt
CONFIG += help
CONFIG += static

INCLUDEPATH += C:\opencv-mingw\install\include
LIBS += -L"C:/opencv-mingw/install/x86/mingw/bin"
LIBS += -lopencv_core310 -lopencv_highgui310 -lopencv_imgproc310 -lopencv_videoio310


SOURCES += main.cpp\
        ventanaprincipal.cpp \
    ventanaseleccionunalgoritmo.cpp \
    ventanaseleccionvariosalgoritmos.cpp \
    graficoevolucionsolucion.cpp \
    solucion.cpp \
    heuristicatsp.cpp \
    algoritmoinsercion.cpp \
    algoritmovecinomascercano.cpp \
    algoritmograsp.cpp \
    algoritmoils.cpp \
    algoritmosa.cpp \
    algoritmoga.cpp \
    ventanaespera.cpp \
    datosproblema.cpp \
    listaalgoritmos.cpp \
    ventanaejecucionalgoritmos.cpp \
    ventanaevolucionsolucion.cpp \
    video.cpp \
    graficoconvergencia.cpp \
    ventanagraficoconvergencia.cpp \
    algoritmoaco.cpp \
    ventanavideo.cpp \
    ventanaayuda.cpp \
    algoritmogaal.cpp \
    algoritmosaal.cpp

HEADERS  += ventanaprincipal.h \
    ventanaseleccionunalgoritmo.h \
    ventanaseleccionvariosalgoritmos.h \
    graficoevolucionsolucion.h \
    solucion.h \
    heuristicatsp.h \
    algoritmoinsercion.h \
    algoritmovecinomascercano.h \
    algoritmograsp.h \
    algoritmoils.h \
    algoritmosa.h \
    algoritmoga.h \
    algoritmoaco.h \
    ventanaespera.h \
    datosproblema.h \
    listaalgoritmos.h \
    ventanaejecucionalgoritmos.h \
    ejecucion.h \
    ventanaevolucionsolucion.h \
    video.h \
    graficoconvergencia.h \
    ventanagraficoconvergencia.h \
    ventanavideo.h \
    ventanaayuda.h \
    algoritmogaal.h \
    algoritmosaal.h

FORMS    += ventanaprincipal.ui \
    ventanaseleccionunalgoritmo.ui \
    ventanaseleccionvariosalgoritmos.ui \
    ventanaespera.ui \
    ventanaejecucionalgoritmos.ui \
    ventanaevolucionsolucion.ui \
    ventanagraficoconvergencia.ui \
    ventanavideo.ui \
    ventanaayuda.ui
