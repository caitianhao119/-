# ----------------------------------------------------
# This file is generated by the Qt Visual Studio Tools.
# ------------------------------------------------------

TEMPLATE = app
TARGET = QtGuiApplication2
DESTDIR = ../Win32/Debug
QT += core gui widgets printsupport
CONFIG += debug
DEFINES += WIN64 QT_DLL QT_WIDGETS_LIB
INCLUDEPATH += ./GeneratedFiles \
    . \
    ./GeneratedFiles/$(ConfigurationName) \
    $(QT5DIR)/include/QtCore \
    $(QT5DIR)/include/QtGui \
    $(QT5DIR)/include/QtANGLE \
    $(QT5DIR)/include/QtWidgets
DEPENDPATH += .
MOC_DIR += ./GeneratedFiles/$(ConfigurationName)
OBJECTS_DIR += debug
UI_DIR += ./GeneratedFiles
RCC_DIR += ./GeneratedFiles


include(QtGuiApplication2.pri)
