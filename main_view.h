#ifndef MAIN_VIEW_H
#define MAIN_VIEW_H

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
#include <QTextEdit>


#include "game.h"
#include "player.h"
#include "choicebutton.h"
#include "playerwidget.h"
#include "movewidget.h"
#include "choicewidget.h"
#include "mapwidget.h"
#include "randomizer.h"
#include "mob.h"
#include "map.h"
#include "inventorywidget.h"

class main_view : public QWidget
{
    Q_OBJECT

public:
    main_view(Game *g = nullptr, QWidget *parent = nullptr);
    ~main_view();

signals:
    // invio il segnale con la scelta fatta
    void emitChoice(Game::Choice c);

    // emetto il segnale per far partire il dialogo al controller
//    void emitDialog();

//    // segnale di volume changed
    void volumeChanged(int volume);

    void setMiniMapSize(int dim);
    
    void newGameSlot();

public slots:
    // printo su textedit
    void printString(QString s);

//    // gestisco e mostro le varie scelte diponibili
    void showChoice(QVector<Game::Choice> c);
//    // gestisco la pressione del pulsante di scelta
    void choicePressed(Game::Choice c);

//    //gestisco il click del pulsante di dialogo
//    void onDialogPressed();

//    // slot per gestire lo slider del volume
    void onVolumeChanged(int volume);
    void onMute();

    void movePressed(char dir);
    // gestisco il refresh della mapppa
    void onPosChanged(const std::vector<std::vector<Tile>> &miniMap, Coordinate relativePos);

    // gestisco il segnale di cambio di dimensione proveniente da MapWidget
    void onSetMiniMapSize(int dim);

    //setto la vita aggiornata del giocatore
    void updatePlayer(Player* p);

    //setto il nuovo score
    void setNewScore(int s);
    //aggiorno mob
    void setEnemy(Mob* t);
    //pulisco mob
    void clearEnemy();

    void updateMob(Mob* m);
private:
    void createMenu();
    void createMusicSliderBox();
    void createMoveBox();
    void createChoiceBox();
    void createCharachterBox();
    void createInventoryBox();
    void createMapBox();
    void createEnemyBox();


    Game* model;

    QGridLayout* grid;
    InventoryWidget *inventory;

    PlayerWidget *character;
    PlayerWidget *mob;

    QLabel *score;

    MapWidget *mapWidget;

    MoveWidget *moveWidget;

    //widget scelte personaggio
    ChoiceWidget *choiceWidget;

    // slider musica
    QSlider *volumeSlider;

    //widget move
    QPushButton *muteButton;
    QGroupBox *musicSlider;

    //finestra di dialogo con il gioco
    QTextEdit *dialogOutBox;


};

#endif // MAIN_VIEW_H
