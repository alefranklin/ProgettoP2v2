#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>
#include <item.h>
#include <itemwidget.h>
class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerWidget(QWidget *parent = nullptr);
    void setHealth(int h);
    void setMana(int m);
    void setMaximumHealth(int maxhp);
    void setMaximumMana(int maxmp);
    void setNome(QString name);
    void clear();
    void changeArmor(Item *i){
        armor->change(i);    }
    void changeWeapon(Item *i){
        weapon->change(i);
    }
signals:

private:
    QVBoxLayout *layout;
    QLabel *nome;
    QLabel *hpHead;
    QProgressBar *hp;
    QLabel *hpLabel;
    QLabel *mpHead;
    QProgressBar *mp;
    QLabel *mpLabel;
    ItemWidget *weapon;
    ItemWidget *armor;

};

#endif // PLAYERWIDGET_H
