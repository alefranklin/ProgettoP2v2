#ifndef PLAYERWIDGET_H
#define PLAYERWIDGET_H

#include <QWidget>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QLabel>
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

signals:

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
