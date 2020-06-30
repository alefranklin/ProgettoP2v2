#ifndef MOVEMENTBUTTON_H
#define MOVEMENTBUTTON_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class MovementButton: public QWidget
{
    Q_OBJECT
public:
    MovementButton(QWidget *parent = nullptr);

signals:
    void buttonClicked(QString dir);

private slots:
    void handleClick(QString dir);

private:
    QGridLayout *grid;
    QString direction;
    QPushButton *dir[];
};

#endif // MOVEMENTBUTTON_H
