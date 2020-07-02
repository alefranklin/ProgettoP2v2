#include "mapwidget.h"
#include <QPushButton>

MapWidget::MapWidget(QWidget *parent, int min, int max, int val) : QWidget(parent)
{
    dimensionLabel = new QLabel();

    dimensionSlider = new QSlider(Qt::Horizontal);
    connect(dimensionSlider, &QSlider::valueChanged, this, &MapWidget::onDimensionChanged);

    dimensionSlider->setMinimum(min);
    dimensionSlider->setMaximum(max);
    dimensionSlider->setValue(val);
    dimensionSlider->setPageStep(1);
    dimensionSlider->setToolTip("modifica la grandezza della mappa");
    emit setMiniMapSize(val);

    /* setto il backgroud */
    //QPalette pal = palette();
    //pal.setColor(QPalette::Background, QColor(86,86,86)); //#565656
    //setAutoFillBackground(true);
    //setPalette(pal);

    /* creo il layout della griglia e aggiungo gli elementi*/
    tile_layout = new QGridLayout();
    tile_layout->setSpacing(0);

    /* creo il layout dello slider e aggiungo gli elementi*/
    slider_layout = new QGridLayout();
    slider_layout->addWidget(dimensionSlider, 0, 0);
    slider_layout->addWidget(dimensionLabel, 0, 1);

    /* creo il layout di MapWidget e aggiungo gli elementi*/
    layout = new QGridLayout(this);
    layout->addLayout(tile_layout, 0, 0, 9, 10);
    layout->addLayout(slider_layout, 10, 0);

    /* setto il layout appena creata al
     * Widget in modo da avere una diposizione degli oggetti
     */
    setLayout(layout);
}

void MapWidget::refresh(const QVector<QVector<Tile> > &miniMap, Coordinate pos) {

    // eliminio tutti i TileButton precedenti
    clearWidgets(tile_layout);

    // ripopolo tile_layout con nuovi pulsanti che rispecchiano la situazione della mappa attuale
    int row = 0;
    int col = 0;
    TileButton *tb;

    for(auto it_row = miniMap.begin(); it_row != miniMap.end(); ++it_row, ++row) {
        for(auto it_col = (*it_row).begin(); it_col != (*it_row).end(); ++it_col, ++col ) {

            if(Coordinate(row, col) == pos) tb = new TileButton((*it_col), true, this);
            else tb = new TileButton((*it_col), false, this);

            tile_layout->addWidget(tb, row, col);
            connect(tb, &TileButton::buttonClicked, this, &MapWidget::onTileButtonPressd);
        }
        col = 0;
    }
}

void MapWidget::onDimensionChanged(int dim) {
    dimensionLabel->setText(QString::number(dim));
    emit setMiniMapSize(dim);
}

void MapWidget::onTileButtonPressd(QVector<Entity *> e) {
    emit showDetailsOf(e);
}

void MapWidget::clearWidgets(QLayout *layout) {
    if (! layout)
        return;
    while (auto item = layout->takeAt(0)) {
        delete item->widget();
        clearWidgets(item->layout());
    }
}
