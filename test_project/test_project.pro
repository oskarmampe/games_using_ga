QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  \
    tst_geneticalgorithm.cpp \
    ..\LatticeThread.cpp \
    ..\genetic_algorithm.cpp \
    ..\geneticindividual.cpp \
    ..\geneticlattice.cpp \
    ..\lattice.cpp \
    ..\latticeqobject.cpp \

HEADERS += \
    ..\LatticeThread.h \
    ..\genetic_algorithm.h \
    ..\geneticindividual.h \
    ..\geneticlattice.h \
    ..\lattice.h \
    ..\latticeqobject.h
