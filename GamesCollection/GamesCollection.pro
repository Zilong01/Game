QT       += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += resources_big
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    choosegamescene.cpp \
    infowindow.cpp \
    main.cpp \
    mainscene.cpp \
    minesblock.cpp \
    minesdiffset.cpp \
    minesinfobar.cpp \
    minessweeperlogic.cpp \
    minessweeperscene.cpp \
    mypushbutton.cpp \
    mywindow.cpp \
    numwidget.cpp \
    snakescene.cpp \
    tetrislogic.cpp \
    tetrislogic1.cpp \
    tetrisscene.cpp

HEADERS += \
    choosegamescene.h \
    infowindow.h \
    mainscene.h \
    minesblock.h \
    minesdiffset.h \
    minesinfobar.h \
    minessweeperlogic.h \
    minessweeperscene.h \
    mypushbutton.h \
    mywindow.h \
    numwidget.h \
    snakescene.h \
    tetrislogic.h \
    tetrislogic1.h \
    tetrisscene.h

FORMS += \
    choosegamescene.ui \
    infowindow.ui \
    minesdiffset.ui \
    numwidget.ui \
    snakescene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
