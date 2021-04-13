TARGET		= aud
DESTDIR		= bin
MOC_DIR		= bin
OBJECTS_DIR	= bin
QT		+= core multimedia

HEADERS += lib.h
SOURCES += main.cpp io.cpp

QMAKE_CXXFLAGS += -std=gnu++11 -Wno-comment

CONFIG -= debug debug_and_release release
CONFIG += console

