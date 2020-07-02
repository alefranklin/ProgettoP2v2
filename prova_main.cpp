#include "prova_main.h"

prova_main::prova_main(Game *g, QWidget *parent)
    : QWidget(parent)
    , model(g)
{
    createMusicSliderBox();

    grid = new QGridLayout();
    setLayout(grid);

    charachter = new PlayerWidget(this);

    inventory= new QListWidget(); //lista di widget (inventario)
    inventory->setFixedWidth(270);
    //inventory->setFixedHeight(200);
    //inventory->setFixedSize(300, 200);

    mapWidget = new MapWidget(this, 10, 30, 15);

    choiceWidget = new ChoiceWidget(this);
    choiceWidget->setFixedWidth(300);

    moveWidget = new MoveWidget(this);
    moveWidget->setFixedWidth(300);

    //prima colonna (col = 0)
    grid->addWidget(charachter, 0, 0);
    grid->addWidget(inventory, 1, 0);
    grid->addWidget(musicSlider, 2, 0);

    //seconda colonna (col = 1)
    grid->addWidget(mapWidget, 0, 1);
    grid->addWidget(choiceWidget, 2, 1);

    //terza colonna (col = 2)
    grid->addWidget(moveWidget, 2, 3);
}

prova_main::~prova_main()
{
    delete this;
}

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
