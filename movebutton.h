#ifndef MOVEBUTTON_H
#define MOVEBUTTON_H

#include <QPushButton>

class MoveButton: public QPushButton
{
    Q_OBJECT

public:
    MoveButton(char dir, QWidget *parent = nullptr);
signals:
    void buttonClicked(char dir);

private slots:
    void handleClick();

private:
    char dir;
};


#endif // MOVEBUTTON_H
