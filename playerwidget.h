#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>


#include "itemwidget.h"
#include "entity.h"
#include "character.h"

class PlayerWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit PlayerWidget(QWidget *parent = nullptr);
    explicit PlayerWidget(QWidget *parent = nullptr);
    void setHealth(int h);
    void setMana(int m);
    void setMaximumHealth(int maxhp);
    void setMaximumMana(int maxmp);
    void setNome(QString name);
    void clear();
    void setWeapon(Item* i);
    void setArmor(Item* i);
    void setFields(Character* c);

signals:

public slots:

private:
    QVBoxLayout *layout;
    QLabel *nome;
    QProgressBar *hp;
    QLabel *hpLabel;
    QProgressBar *mp;
    QLabel *mpLabel;
    ItemWidget *weapon;
    ItemWidget *armor;

};

#endif // PLAYERWIDGET_H
