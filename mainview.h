#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

#include <game.h>
#include <choicebutton.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainView : public QWidget
{
    Q_OBJECT

public:
    MainView(Game *g, QWidget *parent = nullptr);
    ~MainView();

public slots:
    // printo su textedit
    void printString(QString s);


    // gestisco e mostro le varie scelte diponibili
    void showChoice(Choice c);
    // gestisco la pressione del pulsante di scelta
    void choicePressed(Choice c, ChoiceButton *cbt);

    //gestisco il click del pulsante di dialogo
    void onDialogPressed();

signals:
    // invio il segnale con la scelta fatta
    void emitChoice(Choice c);

    // emetto il segnale per far partire il dialogo al controller
    void emitDialog();

private:
    Ui::MainView *ui;

    Game* model;
};
#endif // MAINVIEW_H
