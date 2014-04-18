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
      fontconfig.cpp \
    fontconfigframe.cpp \
    fontpreview.cpp \
    fontcreator.cpp \
    fontoutputframe.cpp \
    fontpage.cpp\
    colorbutton.cpp

HEADERS  += include/mainwindow.h\
       include/charsselectwidget.h \
       include/charmapdialog.h \
       include/charactersframe.h\
       include/fontconfig.h \
       include/fontconfigframe.h \
       include/fontpreview.h \
       include/fontcreator.h \
    include/fontoutputframe.h \
    include/fontpage.h\
    include/colorbutton.h

FORMS    += mainwindow.ui\
         charmapdialog.ui\
         charactersframe.ui \
    fontconfigframe.ui \
    fontpreview.ui \
    fontoutputframe.ui

INCLUDEPATH+=include
TRANSLATIONS = FontConverter_zh_CN.ts
RESOURCES +=\
  resource.qrc
RC_FILE = appicon.rc
