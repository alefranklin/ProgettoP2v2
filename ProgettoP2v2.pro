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
    armor.cpp \
    bow.cpp \
    character.cpp \
    choicebutton.cpp \
    choicewidget.cpp \
    controller.cpp \
    entergame.cpp \
    entity.cpp \
    game.cpp \
    inventorywidget.cpp \
    item.cpp \
    itemwidget.cpp \
    magic.cpp \
    magicweapon.cpp \
    main.cpp \
    main_dialog.cpp \
    main_view.cpp \
    mainview.cpp \
    map.cpp \
    mapwidget.cpp \
    mob.cpp \
    movewidget.cpp \
    player.cpp \
    playerwidget.cpp \
    potion.cpp \
    randomizer.cpp \
    sword.cpp \
    tilebutton.cpp \
    weapon.cpp

HEADERS += \
    armor.h \
    bow.h \
    character.h \
    choicebutton.h \
    choicewidget.h \
    container.h \
    controller.h \
    entergame.h \
    entity.h \
    game.h \
    inventorywidget.h \
    item.h \
    itemwidget.h \
    magic.h \
    magicweapon.h \
    main_dialog.h \
    main_view.h \
    mainview.h \
    map.h \
    mapwidget.h \
    mob.h \
    movewidget.h \
    player.h \
    playerwidget.h \
    potion.h \
    randomizer.h \
    sword.h \
    tilebutton.h \
    weapon.h

FORMS += \
    mainview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
