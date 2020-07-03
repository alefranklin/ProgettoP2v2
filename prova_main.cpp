#include "prova_main.h"

prova_main::prova_main(Game *g, QWidget *parent)
    : QWidget(parent)
    , model(g)
{
    // connetto i segnali per la mappa dal modello a view e viceversa
    connect(model, &Game::posChanged, this, &prova_main::onPosChanged);  // da model a view
    connect(this, &prova_main::setMiniMapSize, model, &Game::onSetMiniMapSize); // da view a model

    createMusicSliderBox();

    grid = new QGridLayout();
    setLayout(grid);

    charachter = new PlayerWidget(this);
    PlayerWidget *mob = new PlayerWidget(this); //TODO dichiararlo sul .h

    inventory= new QListWidget(); //lista di widget (inventario)
    inventory->setFixedWidth(270);
    //inventory->setFixedHeight(200);
    //inventory->setFixedSize(300, 200);

    QListWidget *placeholder = new QListWidget();

    mapWidget = new MapWidget(this, 10, 20, 15);

    connect(mapWidget, &MapWidget::setMiniMapSize, this, &prova_main::onSetMiniMapSize);
    //mapWidget->setMaximumSize(400,300);


    connect(mapWidget, &MapWidget::showDetailsOf, mob, &PlayerWidget::onShowDetailOf);

    choiceWidget = new ChoiceWidget(this);
    //choiceWidget->setFixedWidth(300);

    moveWidget = new MoveWidget(this);

    //prima colonna (col = 0)
    grid->addWidget(charachter, 0, 0);
    grid->addWidget(inventory, 1, 0);
    grid->addWidget(musicSlider, 2, 0, Qt::AlignLeft);

    //seconda colonna (col = 1)
    grid->addWidget(mapWidget, 0, 1, Qt::AlignCenter);
    grid->addWidget(placeholder, 1, 1); //TODO mettere finestra di dialogo
    grid->addWidget(choiceWidget, 2, 1, Qt::AlignCenter);

    //terza colonna (col = 2)
    grid->addWidget(moveWidget, 2, 2);
    grid->addWidget(mob, 0, 2); //TODO implementare in modo diverso per mob

    //grid->setRowMinimumHeight(0,270);

}

prova_main::~prova_main(){}

void prova_main::createMenu()
{
    menubar = new QMenuBar(this);

    fileMenu = new QMenu("&File", nullptr);
    saveAction = new QAction("&Save", nullptr);
    exitAction = new QAction("E&xit", nullptr);

    //aggiungo le azioni al menu
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);

    //aggiungo il menu alla barra
    menubar->addMenu(fileMenu);

    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

}

void prova_main::createMusicSliderBox(){

    musicSlider = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    // controllo il volume
    //volumeSlider = ui->volumeSlider; // TODO sostitutire con (riga sotto)
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);

    //connect(volumeSlider, &QSlider::valueChanged, this, &MainView::onVolumeChanged);

    // bottone per il muto
    muteButton = new QPushButton("Mute", this);
    //connect(muteButton, &QPushButton::clicked, this, &MainView::onMute);

    layout->addWidget(muteButton);
    layout->addWidget(volumeSlider);
    musicSlider->setLayout(layout);

    //musicSlider->setFixedWidth(200);
    //musicSlider->setFixedHeight(65);
    musicSlider->setFixedSize(200, 65);


    //musicSlider->setGeometry(20, 520, 200, 65);
}

void prova_main::onPosChanged(const QVector<QVector<Tile>> &miniMap, Coordinate relativePos) {
    MapWidget *mapwidget = mapWidget;
    mapwidget->refresh(miniMap, relativePos);
}

void prova_main::onSetMiniMapSize(int dim) {
    emit setMiniMapSize(dim);
}
