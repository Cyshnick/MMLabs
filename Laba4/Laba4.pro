QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Plotter/arrow.cpp \
    Plotter/axis.cpp \
    Plotter/glyph.cpp \
    Plotter/grid.cpp \
    Plotter/plot.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Plotter/arrow.h \
    Plotter/axis.h \
    Plotter/glyph.h \
    Plotter/grid.h \
    Plotter/igraphvisitor.h \
    Plotter/plot.h \
    Plotter/shared.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
