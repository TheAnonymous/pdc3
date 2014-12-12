TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += main.cpp
#CONFIG += c++11 -fopenmp
QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS += -fopenmp -openmp -std=c++11
#LIBS += -fopenmp

#include(deployment.pri)
#qtcAddDeployment()

