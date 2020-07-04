#ifndef MOVEWIDGET_H
#define MOVEWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLayout>
#include "movebutton.h"

class MoveWidget : public QWidget
{
    Q_OBJECT

public:
    MoveWidget(QWidget *parent = nullptr);
    ~MoveWidget();

signals:
    // invio il segnale con la direzione scelta
    void emitDir(char c);

public slots:
    void dirPressed(char c);

    void setEnabled(bool enable);

private:
    MoveButton *UP;
    MoveButton *DOWN;
    MoveButton *RIGHT;
    MoveButton *LEFT;

    QGridLayout *grid;
    //QGroupBox *grid;
};
#endif // MOVEWIDGET_H
