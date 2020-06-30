#ifndef MOVEMENTBUTTONCONTAINER_H
#define MOVEMENTBUTTONCONTAINER_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

class MovementButtonContainer: public QWidget
{
    Q_OBJECT
public:
    MovementButtonContainer(QWidget *parent = nullptr);

signals:
    void buttonClicked(QString dir);

private slots:
    void handleClick(QString dir);

private:
    QGridLayout *grid;
    QPushButton *dir[];
};

#endif // MOVEMENTBUTTONCONTAINER_H
