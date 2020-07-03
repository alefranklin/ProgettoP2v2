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
