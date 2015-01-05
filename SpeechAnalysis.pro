#-------------------------------------------------
#
# Project created by QtCreator 2014-12-30T14:21:52
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpeechAnalysis
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    utils.cpp \
    wavfile.cpp \
    wavanalyzer.cpp \
    vectorutils.cpp

HEADERS  += mainwindow.h \
    utils.h \
    wavfile.h \
    wavanalyzer.h \
    vectorutils.h

FORMS    += mainwindow.ui
