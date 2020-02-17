#-------------------------------------------------
#
# Project created by QtCreator 2019-05-16T21:50:31
#
#-------------------------------------------------
QT += xml sql
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course_work
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
    csv.cpp \
    csvstorage.cpp \
    main.cpp \
    mainwindow.cpp \
    storage.cpp \
    xmlstorage.cpp \
    add_editdialog.cpp \
    sqlite_storage.cpp \
    login.cpp \
    edit_dialog.cpp \
    registration.cpp

HEADERS += \
    branch.h \
    csv.h \
    csvstorage.h \
    mainwindow.h \
    optional.h \
    station.h \
    storage.h \
    xmlstorage.h \
    add_editdialog.h \
    sqlite_storage.h \
    user.h \
    login.h \
    edit_dialog.h \
    registration.h \
    iterator.h

FORMS += \
    mainwindow.ui \
    add_editdialog.ui \
    login.ui \
    edit_dialog.ui \
    registration.ui

SUBDIRS += \
    course_work.pro

DISTFILES += \
    lab7.pro.user \
    data/xml/branch.xml \
    data/xml/station.xml \
    data/csv/branch.csv \
    data/csv/station.csv \
    data/sql/data.sqlite
