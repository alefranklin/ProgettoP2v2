#ifndef ENTERGAME_H
#define ENTERGAME_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPicture>
#include <QMessageBox>
#include "character.h"

class EnterGame: public QDialog
{
    Q_OBJECT
public:

    // costruttore
    EnterGame(Player**pers, QWidget* parent = nullptr);
    void cleanLabel();

public slots:
    // lista degli slot
    void tryEnter();

signals:
    //void send(user*);

private:
    void createLayoutEnterGame();
    void createLoginButton();

//    const listUser& listaUtenti;
//    user**loginUser;
    Player**pg;

    QGridLayout* layoutEnterGame;
    QLabel* nameLabel;
    QLineEdit* pg_name;
    QPushButton* bPlay;
};

#endif // ENTERGAME_H
