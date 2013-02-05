TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vmcsolver.cpp \
    trialwavefunction.cpp \
    hydrogenlike.cpp \
    lib.cpp \
    vmcapplication.cpp

HEADERS += \
    vmcsolver.h \
    trialwavefunction.h \
    hydrogenlike.h \
    lib.h \
    vmcapplication.h


unix|win32: LIBS += -larmadillo

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += libconfig++
