TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        multigraph.cpp

HEADERS += \
    def.h \
    matr.h \
    multigraph.h \
    sparse_matrix.h \
    vec.h
