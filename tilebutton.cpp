#include "tilebutton.h"
#include "game.h"

TileButton::TileButton(Tile t, bool playerIn, QWidget *parent): QPushButton(parent), tile(t) {

    //se non ci sono entity disabilito il pulsante
    if(tile.e.isEmpty()) setDisabled(true);

    //TODO mettere lo stile in base a Tile
    /*
        b->setToolTip("tesoro");
        // setto background
        pal = b->palette();
        pal.setColor(QPalette::Button, QColor(Qt::yellow));
        b->setAutoFillBackground(true);
        b->setPalette(pal);
        */

    if(playerIn) setText("P");

    connect(this, SIGNAL(clicked()), this, SLOT(handleClick()));
}

void TileButton::handleClick()
{
    //emit buttonClicked(tile.e);
}
