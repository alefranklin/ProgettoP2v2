#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <game.h>
#include <mainview.h>

#include <QObject>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(Game *g, MainView* v, QObject *parent = nullptr);
    ~Controller();

signals:

public slots:
    // faccio partire la funzione che emette il dialogo (solo per test)
    //void avviaDialogo();
    //void exitWindow();

private:
  Game* model;
  MainView* view;

  // musica di sottofondo
  // aggiungo la musica
  QMediaPlaylist *playlist;
  QMediaPlayer *music;

};

#endif // CONTROLLER_H
