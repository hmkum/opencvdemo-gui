#-------------------------------------------------
#
# Project created by QtCreator 2016-01-19T15:49:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenCVDemo
TEMPLATE = app

QMAKE_CXX += -Wall -std=c++11

LIBS += -lopencv_world

SOURCES += src/main.cpp\
        src/MainWindow.cpp \
    src/edge_detection/CannyEdgeDetection.cpp \
    src/edge_detection/SobelEdgeDetection.cpp \
    src/edge_detection/LaplacianEdgeDetection.cpp \
    src/utility/Filter2D.cpp \
    src/utility/NoiseGenerator.cpp

HEADERS  += src/MainWindow.h \
    src/edge_detection/CannyEdgeDetection.h \
    src/edge_detection/SobelEdgeDetection.h \
    src/edge_detection/LaplacianEdgeDetection.h \
    src/utility/Filter2D.h \
    src/utility/NoiseGenerator.h

FORMS    += forms/MainWindow.ui \
    forms/CannyEdgeDetection.ui \
    forms/SobelEdgeDetection.ui \
    forms/LaplacianEdgeDetection.ui \
    forms/Filter2D.ui \
    forms/NoiseGenerator.ui
