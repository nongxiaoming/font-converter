#-------------------------------------------------
#
# Project created by QtCreator 2013-12-27T17:22:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FontConverter
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
       charsselectwidget.cpp \
       charmapdialog.cpp \
      charactersframe.cpp\
      fontconfig.cpp

HEADERS  += include/mainwindow.h\
       include/charsselectwidget.h \
       include/charmapdialog.h \
      include/charactersframe.h\
      include/fontconfig.h

FORMS    += mainwindow.ui\
         charmapdialog.ui\
         charactersframe.ui

INCLUDEPATH+=include

RESOURCES +=\
  resource.qrc

