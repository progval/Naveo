#-------------------------------------------------
#
# Project created by QtCreator 2010-10-25T15:33:04
#
#-------------------------------------------------

#TEMPLATE = app


CONFIG += dll
TEMPLATE = lib

QT += core gui network
TARGET = maj
CONFIG += console


SOURCES += main.cpp\
		widget.cpp \
		httpget.cpp \
	downloadWidget.cpp

HEADERS  += widget.h \
		httpget.h \
	downloadWidget.h

RESOURCES += \
	ress.qrc
