#ifndef ENTERGAME_H
#define ENTERGAME_H

#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPicture>
#include <QMessageBox>

class EnterGame: public QDialog
{
    Q_OBJECT
public:

    // costruttore
    EnterGame(QWidget* parent = nullptr);
    //void clean();

public slots:
    // lista degli slot
    //void tryLogin();

signals:
    //void send(user*);

private:
    void createLayoutEnterGame();
    void createLoginButton();

//    const listUser& listaUtenti;
//    user**loginUser;

    QGridLayout* layoutLogin;
    QLabel* lname;
    QLabel* lpass;
    QLabel* lImgLogin;
    QLineEdit* tname;
    QLineEdit* tpass;
    QPushButton* blogin;
};

#endif // ENTERGAME_H
