TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
QMAKE_LFLAGS += -fopenmp
QMAKE_CXXFLAGS += -std=c++0x


include(deployment.pri)
qtcAddDeployment()
