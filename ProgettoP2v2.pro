QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    character.cpp \
    choicebutton.cpp \
    choicewidget.cpp \
    controller.cpp \
    entergame.cpp \
    game.cpp \
    inventorywidget.cpp \
    item.cpp \
    itemwidget.cpp \
    main.cpp \
    main_dialog.cpp \
    mainview.cpp \
    map.cpp \
    mapwidget.cpp \
    movewidget.cpp \
    playerwidget.cpp \
    prova_main.cpp \
    randomizer.cpp \
    tilebutton.cpp

HEADERS += \
    character.h \
    choicebutton.h \
    choicewidget.h \
    controller.h \
    entergame.h \
    entity.h \
    game.h \
    inventorywidget.h \
    item.h \
    itemwidget.h \
    main_dialog.h \
    mainview.h \
    map.h \
    mapwidget.h \
    movewidget.h \
    playerwidget.h \
    prova_main.h \
    randomizer.h \
    tilebutton.h

FORMS += \
    mainview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
