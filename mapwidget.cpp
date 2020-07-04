#include "mapwidget.h"
#include <QPushButton>

#include <QDebug>

MapWidget::MapWidget(QWidget *parent, int val) : QWidget(parent), dimension(val), tiles(val*val)
{
    /* creo il layout della griglia e lo setto al MapWidget*/
    layout = new QGridLayout(this);
    layout->setSpacing(0);
    setLayout(layout);

    //istanzio pulsanti per i tile
    int pos = 0;
    int row;
    int col;
    for (auto it = tiles.begin(); it != tiles.end(); ++it, ++pos) {
        *it = new TileButton(this);
        row = pos/val;
        col = pos%val;
        layout->addWidget(*it, row, col); //calcolare pos
        connect(*it, &TileButton::buttonClicked, this, &MapWidget::onTileButtonPressed);
    }


    //imposto il widget ad una dimensione fissata
    setFixedSize(400,300);

    emit setMiniMapSize(val);
}

void MapWidget::refresh(const std::vector<std::vector<Tile> > &miniMap, Coordinate pos) {

    // ripopolo tile_layout con nuovi pulsanti che rispecchiano la situazione della mappa attuale
    int row = 0;
    int col = 0;
    TileButton *tb;

    for(auto it_row = miniMap.begin(); it_row != miniMap.end(); ++it_row, ++row) {
        for(auto it_col = (*it_row).begin(); it_col != (*it_row).end(); ++it_col, ++col ) {
            tb = tiles[(row*dimension)+col]; //calcolo in base a col e row
            tb->setTile((*it_col));
            if(Coordinate(row, col) == pos) tb->setPlayerHere(true);
        }
        col = 0;
    }
}

void MapWidget::onTileButtonPressed(std::vector<Entity *> e) {
    emit showDetailsOf(e);
}

void MapWidget::syncDimension() {
    emit setMiniMapSize(dimension);
}
