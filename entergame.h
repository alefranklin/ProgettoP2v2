#ifndef ENTERGAME_H
#define ENTERGAME_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPicture>
#include <QMessageBox>
#include <regex>

//#include "character.h"
#include "game.h"

class EnterGame: public QDialog
{
    Q_OBJECT
public:

    // costruttore
    EnterGame(Game** g, QWidget* parent = nullptr);
    void cleanEnter();

public slots:
    // lista degli slot
    void tryEnter();

signals:


private:
    void createLayoutEnterGame();

    //Player**pg;

    Game** gioco;

    QGridLayout* layoutEnterGame;
    QLabel* nameLabel;
    QLineEdit* pg_name;
    QPushButton* bPlay;
    QPushButton* bLoadPlayer;
};

#endif // ENTERGAME_H
