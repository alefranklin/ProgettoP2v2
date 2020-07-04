#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QMenuBar>

#include <game.h>
#include <choicebutton.h>
#include <mapwidget.h>
#include <map.h>
#include <movewidget.h>
#include <choicewidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE


class MainView : public QWidget
{
    Q_OBJECT

public:
    MainView(Game *g, QWidget *parent = nullptr);
    ~MainView();

signals:
    // invio il segnale con la scelta fatta
    void emitChoice(Game::Choice c);

    // emetto il segnale per far partire il dialogo al controller
    void emitDialog();

    // segnale di volume changed
    void volumeChanged(int volume);

    // segnale per il cambio della dimensione della minimappa
    void setMiniMapSize(int dim);

public slots:
    // printo su textedit
    void printString(QString s);

    // gestisco e mostro le varie scelte diponibili
    void showChoice(QVector<Game::Choice> c);
    // gestisco la pressione del pulsante di scelta
    void choicePressed(Game::Choice c);

    //gestisco il click del pulsante di dialogo
    void onDialogPressed();

    // slot per gestire lo slider del volume
    void onVolumeChanged(int volume);
    void onMute();


    // gestisco il refresh della mapppa
    void onPosChanged(const std::vector<std::vector<Tile>> &miniMap, Coordinate relativePos);

    // gestisco il segnale di cambio di dimensione proveniente da MapWidget
    void onSetMiniMapSize(int dim);

    void movePressed(char dir);



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

    //menu
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QAction *exitAction;
    QAction *saveAction;


    Game* model;
    MoveWidget *moveWidget;

    //widget scelte personaggio
    ChoiceWidget *choiceWidget;

    // slider musica
    QSlider *volumeSlider;

    //widget move
    QPushButton *muteButton;


};
#endif // MAINVIEW_H
