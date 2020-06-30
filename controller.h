#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <game.h>
#include <mainview.h>

#include <QObject>
#include <QString>

class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(Game *g, MainView* v, QObject *parent = nullptr);
    ~Controller();

signals:

public slots:
    // gestisco i testi da model a view
    void onDialogOut(QString s);

    // gestisco la scelta che va da model verso view
    void onChoiceOut(Choice c);

    // gestisco la scelta che arriva da view verso model
    void onChoiceIn(Choice c);

    // faccio partire la funzione che emette il dialogo (solo per test)
    void avviaDialogo();

private:
  Game* model;
  MainView* view;
};

#endif // CONTROLLER_H
