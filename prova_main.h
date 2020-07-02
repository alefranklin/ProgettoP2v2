#ifndef PROVA_MAIN_H
#define PROVA_MAIN_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QMenuBar>
#include <QMenu>
#include <QListWidget>
#include <QScrollArea>
#include <QLabel>
#include <QGroupBox>


#include <game.h>
#include "choicebutton.h"
#include "playerwidget.h"
#include <movewidget.h>
#include <choicewidget.h>
#include "mapwidget.h"

class prova_main : public QWidget
{
    Q_OBJECT

public:
    prova_main(Game *g, QWidget *parent = nullptr);
    ~prova_main();

signals:
    // invio il segnale con la scelta fatta
    //void emitChoice(Game::Choice c);

    // emetto il segnale per far partire il dialogo al controller
//    void emitDialog();

//    // segnale di volume changed
//    void volumeChanged(int volume);

public slots:
    // printo su textedit
//    void printString(QString s);

//    // gestisco e mostro le varie scelte diponibili
//    void showChoice(QVector<Game::Choice> c);
//    // gestisco la pressione del pulsante di scelta
//    void choicePressed(Game::Choice c);

//    //gestisco il click del pulsante di dialogo
//    void onDialogPressed();

//    // slot per gestire lo slider del volume
//    void onVolumeChanged(int volume);
//    void onMute();

//    void movePressed(char dir);


private:
    void createMenu();
    void createMusicSliderBox();
    void createMoveBox();
    void createChoiceBox();
    void createDialogBox();
    void createCharachterBox();
    void createInventoryBox();
    void createMapBox();
    void createEnemyBox();

    QGridLayout* grid;
    QListWidget *inventory;

    PlayerWidget *charachter;

    QLabel *info;

    QPushButton* bottone;

    //menu
    QMenuBar *menubar;
    QMenu *fileMenu;
    QAction *exitAction;
    QAction *saveAction;

    MapWidget *mapWidget;

    Game* model;
    MoveWidget *moveWidget;

    //widget scelte personaggio
    ChoiceWidget *choiceWidget;

    // slider musica
    QSlider *volumeSlider;

    //widget move
    QPushButton *muteButton;

    QGroupBox *musicSlider;


};

#endif // PROVA_MAIN_H
