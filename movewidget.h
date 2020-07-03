#ifndef MOVEWIDGET_H
#define MOVEWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>


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
    void setEnabled(bool enable);

private slots:
    void clickedUP();
    void clickedDOWN();
    void clickedRIGHT();
    void clickedLEFT();

private:
    QPushButton *UP;
    QPushButton *DOWN;
    QPushButton *RIGHT;
    QPushButton *LEFT;

    QGridLayout *grid;
};
#endif // MOVEWIDGET_H
