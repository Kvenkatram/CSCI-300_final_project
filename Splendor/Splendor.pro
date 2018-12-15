#-------------------------------------------------
#
# Project created by QtCreator 2018-11-26T19:05:38
#
#-------------------------------------------------

QT       += core gui
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Splendor
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        gamewindow.cpp \
    card.cpp \
    nobel.cpp \
    login.cpp \
    #card.cpp \
    #gamewindow.cpp \
    #login.cpp \
    #main.cpp \
    #nobel.cpp

HEADERS += \
        gamewindow.h \
    card.h \
    nobel.h \
    login.h \
    #card.h \
    #gamewindow.h \
    #login.h \
    #nobel.h

FORMS += \
        gamewindow.ui \
    login.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    images/backgroundPic.jpg \
    images/Capture.JPG \
    images/marble.jpg \
    images/stck1Pix.JPG \
    images/stck2Pix.JPG \
    images/stck3Pix.JPG \
    images/tableTop.jpeg \
    images/your_turn.jpg \
    images/3Diff.png \
    images/3Same.png \
    images/diamond.png \
    images/emerald.png \
    images/endturn.png \
    images/noble.png \
    images/pickcard.png \
    images/quartz.png \
    images/reserve.png \
    images/ruby.png \
    images/sapphire.png \
    images/backgroundPic.jpg \
    images/Capture.JPG \
    images/marble.jpg \
    images/stck1Pix.JPG \
    images/stck2Pix.JPG \
    images/stck3Pix.JPG \
    images/tableTop.jpeg \
    images/your_turn.jpg \
    images/3Diff.png \
    images/3Same.png \
    images/diamond.png \
    images/emerald.png \
    images/endturn.png \
    images/noble.png \
    images/pickcard.png \
    images/quartz.png \
    images/reserve.png \
    images/ruby.png \
    images/sapphire.png

RESOURCES += \
    images.qrc

