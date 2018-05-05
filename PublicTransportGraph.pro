#-------------------------------------------------
#
# Project created by QtCreator 2018-05-01T12:42:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PublicTransportGraph
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
        busline.cpp \
        busstop.cpp \
        linedirection.cpp \
        location.cpp \
        network.cpp \
        textparser.cpp \
        graphformatgenerator.cpp \
        lgraphgenerator.cpp \
        cgraphgenerator.cpp \
        outputfileformater.cpp \
        gmloutput.cpp \
        csvoutput.cpp \
        lineinfowindow.cpp \
    directiontabwidget.cpp \
    savedialog.cpp \
    addlinedialog.cpp \
    filterdialog.cpp \
    deletedialog.cpp \
    connectedlinesdialog.cpp \
    textwidget.cpp \
    connectedpairsdialog.cpp \
    lineforstopdialog.cpp \
    twostopsdialog.cpp \
    linedialog.cpp \
    locationwidget.cpp


HEADERS += \
        mainwindow.h \
        location.h \
        network.h \
        textparser.h \
        ptrcomparator.h \
        busline.h \
        busstop.h \
        linedirection.h \
        graphformatgenerator.h \
        lgraphgenerator.h \
        cgraphgenerator.h \
        outputfileformater.h \
        gmloutput.h \
        csvoutput.h \
        node.h \
        lineinfowindow.h \
    directiontabwidget.h \
    savedialog.h \
    addlinedialog.h \
    filterdialog.h \
    deletedialog.h \
    connectedlinesdialog.h \
    textwidget.h \
    connectedpairsdialog.h \
    lineforstopdialog.h \
    twostopsdialog.h \
    linedialog.h \
    locationwidget.h


FORMS += \
        mainwindow.ui \
    lineinfowindow.ui \
    directiontabwidget.ui \
    savedialog.ui \
    addlinedialog.ui \
    filterdialog.ui \
    deletedialog.ui \
    connectedlinesdialog.ui \
    textwidget.ui \
    connectedpairsdialog.ui \
    lineforstopdialog.ui \
    twostopsdialog.ui \
    linedialog.ui \
    locationwidget.ui
