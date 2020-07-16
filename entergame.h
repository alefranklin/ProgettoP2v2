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
//    void errorLoadPlayer(QJsonParseError jsonError);
//    void errorOpenFile(QString s);

signals:


private:
    void createLayoutEnterGame();
    void loadPlayerSlot();

    //Player**pg;

    Game** gioco;

    QGridLayout* layoutEnterGame;
    QLabel* nameLabel;
    QLineEdit* pg_name;
    QPushButton* bPlay;
    QPushButton* bLoadPlayer;
};

#endif // ENTERGAME_H
