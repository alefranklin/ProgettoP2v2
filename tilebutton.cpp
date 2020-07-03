#include "tilebutton.h"
#include "game.h"

TileButton::TileButton(Tile t, bool playerIn, QWidget *parent): QPushButton(parent), tile(t) {

    //se non ci sono entity disabilito il pulsante
    if(tile.e.isEmpty()) setDisabled(true);

    switch(tile.biome){
        case Valley:
            setStyleSheet("background-color: green; border: 0px;");
        break;
        case Desert:
            setStyleSheet("background-color: yellow; border: 0px;");
        break;
        case Doungeon:
            setStyleSheet("background-color: #5c5c5c; border: 0px;");
        break;
        case Street:
            setStyleSheet("background-color: gray; border: 0px;");
        break;
        case Water:
            setStyleSheet("background-color: blue; border: 0px;");
        break;
        case Null:
            setStyleSheet("border: 0px;");
        break;
    }

    if(playerIn) setText("P");

    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void TileButton::handleClick()
{
    //emit buttonClicked(tile.e);

}
