TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vmcsolver.cpp \
    trialwavefunction.cpp \
    hydrogenlike.cpp

HEADERS += \
    vmcsolver.h \
    trialwavefunction.h \
    hydrogenlike.h


unix|win32: LIBS += -larmadillo
