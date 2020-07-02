#ifndef ITEMWIDGET_H
#define ITEMWIDGET_H

#include <QWidget>
#include <QLabel>
#include <item.h>
#include <game.h>
class ItemWidget : public QWidget
{
    Q_OBJECT
public:
    ItemWidget(QWidget *parent = nullptr);
    ItemWidget(QString n, QString t, int s1, int s2 = 0, int s3 = 0, QWidget *parent = nullptr);
    ItemWidget(Item *i, QWidget *parent = nullptr);
    void clear();
    void change(Item *i);
signals:

private:
    QLabel *nome;
    QLabel *tipo;
    QLabel *stat1Name;
    QLabel *stat1;
    QLabel *stat2Name;
    QLabel *stat2;
    QLabel *stat3Name;
    QLabel *stat3;
};

#endif // ITEMWIDGET_H
