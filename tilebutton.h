#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <map.h>
#include <QPushButton>

class TileButton : public QPushButton
{
    Q_OBJECT

public:
    TileButton(Tile t, bool playerIn = false, QWidget *parent = nullptr);

signals:
    void buttonClicked(std::vector<Entity *>);

private slots:
    void handleClick();

private:
    Tile tile;
};

#endif // CHOICEBUTTON_H
