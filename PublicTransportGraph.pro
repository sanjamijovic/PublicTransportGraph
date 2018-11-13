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
        ui/mainwindow.cpp \
        network/busline.cpp \
        network/busstop.cpp \
        network/linedirection.cpp \
        network/location.cpp \
        network/network.cpp \
        input/textparser.cpp \
        output/graphformatgenerator.cpp \
        output/lgraphgenerator.cpp \
        output/cgraphgenerator.cpp \
        output/outputfileformater.cpp \
        output/gmloutput.cpp \
        output/csvoutput.cpp \
        ui/lineinfowindow.cpp \
  		ui/directiontabwidget.cpp \
  		ui/savedialog.cpp \
  		ui/addlinedialog.cpp \
  		ui/filterdialog.cpp \
  		ui/deletedialog.cpp \
  		ui/connectedlinesdialog.cpp \
  		ui/textwidget.cpp \
  		ui/connectedpairsdialog.cpp \
  		ui/twostopsdialog.cpp \
  		ui/linedialog.cpp \
  		ui/locationwidget.cpp \
  		ui/bfsdialog.cpp \
  		utils/invalidfile.cpp \
  		ui/changelinename.cpp \
  		ui/linechangestop.cpp \
  		ui/infoforstopdialog.cpp


HEADERS += \
        ui/mainwindow.h \
        network/location.h \
        network/network.h \
        input/textparser.h \
        utils/ptrcomparator.h \
        network/busline.h \
        network/busstop.h \
        network/linedirection.h \
        output/graphformatgenerator.h \
        output/lgraphgenerator.h \
        output/cgraphgenerator.h \
        output/outputfileformater.h \
        output/gmloutput.h \
        output/csvoutput.h \
        network/node.h \
        ui/lineinfowindow.h \
	 	ui/directiontabwidget.h \
	 	ui/savedialog.h \
	 	ui/addlinedialog.h \
	 	ui/filterdialog.h \
	 	ui/deletedialog.h \
	 	ui/connectedlinesdialog.h \
	 	ui/textwidget.h \
	 	ui/connectedpairsdialog.h \
	 	ui/twostopsdialog.h \
	 	ui/linedialog.h \
	 	ui/locationwidget.h \
	 	ui/bfsdialog.h \
	 	utils/invalidfile.h \
	 	ui/changelinename.h \
	 	ui/linechangestop.h \
	 	ui/infoforstopdialog.h


FORMS += \
    	ui/mainwindow.ui \
    	ui/lineinfowindow.ui \
    	ui/directiontabwidget.ui \
    	ui/savedialog.ui \
    	ui/addlinedialog.ui \
    	ui/filterdialog.ui \
    	ui/deletedialog.ui \
    	ui/connectedlinesdialog.ui \
    	ui/textwidget.ui \
    	ui/connectedpairsdialog.ui \
    	ui/twostopsdialog.ui \
    	ui/linedialog.ui \
    	ui/locationwidget.ui \
    	ui/bfsdialog.ui \
    	ui/changelinename.ui \
    	ui/linechangestop.ui \
    	ui/infoforstopdialog.ui

INCLUDEPATH += \
        $$PWD \
        input \
        output \
        network \
        ui \
        utils
