#ifndef TILEBUTTON_H
#define TILEBUTTON_H

#include <map.h>
#include <QPushButton>

class TileButton : public QPushButton
{
    Q_OBJECT

public:
    TileButton(QWidget *parent = nullptr);
    void setTile(Tile t);
    void setPlayerHere(bool here);

signals:
    void buttonClicked(QVector<Entity *>);

private slots:
    void handleClick();

private:
    Tile tile;
};

#endif // CHOICEBUTTON_H
