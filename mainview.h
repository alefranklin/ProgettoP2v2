#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>
#include <QSlider>
#include <QPushButton>

#include <game.h>
#include <choicebutton.h>
#include <movementbutton.h>

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

public slots:
    // printo su textedit
    void printString(QString s);


    // gestisco e mostro le varie scelte diponibili
    void showChoice(Game::Choice c);
    // gestisco la pressione del pulsante di scelta
    void choicePressed(Game::Choice c, ChoiceButton *cbt);

    //gestisco il click del pulsante di dialogo
    void onDialogPressed();

    // slot per gestire lo slider del volume
    void onVolumeChanged(int volume);
    void onMute();

    void movePressed(QString dir);


private:
    Ui::MainView *ui;

    Game* model;

    // volume musica
    MovementButton *move;
    QSlider *volumeSlider;
    QPushButton *muteButton;
};
#endif // MAINVIEW_H
