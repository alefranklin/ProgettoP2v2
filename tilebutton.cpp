#include "tilebutton.h"
#include "game.h"

TileButton::TileButton(QWidget *parent): QPushButton(parent) {

    //all'inizio disabilito tutto e aspetto che venga settato un tile che sostituisca quello creato di default
    setStyleSheet("background-color: black; border: 0px;");
    setDisabled(true);

    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));

}

void TileButton::setTile(Tile t)
{
    setPlayerHere(false);

    //sostituisco tile
    tile = t;

    //se non ci sono entity disabilito il pulsante
    if(tile.e.empty()) setDisabled(true);
    else               setDisabled(false);

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
}

void TileButton::setPlayerHere(bool here)
{
    if(here) {
        setText("P");
        setStyleSheet("font-weight: bold; color: black; border: 1px solid black;");
    } else {
        setText("");
    }
}

void TileButton::handleClick()
{
    //emit buttonClicked(tile.e);

}
