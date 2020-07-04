#include "tilebutton.h"
#include "game.h"

TileButton::TileButton(Tile t, bool playerIn, QWidget *parent): QPushButton(parent), tile(t) {

    //se non ci sono entity disabilito il pulsante
    if(tile.e.empty()) setDisabled(true);

    switch(tile.biome){
        case Valley:
            setStyleSheet("background-color: green; border: 0px;");
        break;
        case Desert:
            setStyleSheet("background-color: #f6d66c; border: 0px;");
        break;
        case Street:
            setStyleSheet("background-color: gray; border: 0px;");
        break;
        case Water:
            setStyleSheet("background-color: blue; border: 0px;");
        break;
        case Null:
            setStyleSheet("background-color: black; border: 0px;");
        break;
    }

    if(!tile.e.empty()){
        if(Game::isMob(tile.e[0])){
            setText("N");
            setStyleSheet("font-weight: bold; color: red; border: 1px solid red;");
        }

        if(Game::isItem(tile.e[0])){
            setText("I");
            setStyleSheet("font-weight: bold; color: purple; border: 1px solid purple;");
        }
    }

    if(playerIn){
        setText("P");
        setStyleSheet("font-weight: bold; color: black; border: 1px solid black;");
    }

    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void TileButton::handleClick()
{
    //emit buttonClicked(tile.e);

}
