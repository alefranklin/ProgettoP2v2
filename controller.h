#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <game.h>
#include <mainview.h>
#include <main_dialog.h>

#include <QObject>
#include <QString>
#include <QMediaPlaylist>
#include <QMediaPlayer>

class Controller: public QObject
{
    Q_OBJECT

public:
    Controller(main_dialog* v, Game *g = nullptr, QObject *parent = nullptr);
    ~Controller();

signals:

public slots:
    // faccio partire la funzione che emette il dialogo (solo per test)
    //void avviaDialogo();

private:
  Game* model;
  main_dialog* view;

  // musica di sottofondo
  // aggiungo la musica
  QMediaPlaylist *playlist;
  QMediaPlayer *music;

};

#endif // CONTROLLER_H
