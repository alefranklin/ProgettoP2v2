#include "main_view.h"

main_view::main_view(Game *g, QWidget *parent)
    : QWidget(parent)
    , model(g)
{

    createMusicSliderBox();

    //LAYOUT PRINCIPALE
    grid = new QGridLayout();
    setLayout(grid);

    //PERSONAGGIO E NEMICO
    charachter = new PlayerWidget(model->getPlayer(), this);
    PlayerWidget *mob = new PlayerWidget(model->getPlayer(), this); //TODO dichiararlo sul .h

    //INVENTARIO
    inventory= new QListWidget(); //lista di widget (inventario)
    inventory->setFixedWidth(270);

    //MAPPA
    mapWidget = new MapWidget(this, 19, 19, 19);

    // connetto i segnali per la mappa dal modello a view e viceversa
    connect(model, &Game::posChanged, this, &main_view::onPosChanged);  // da model a view
    connect(this, &main_view::setMiniMapSize, model, &Game::onSetMiniMapSize); // da view a model
    connect(mapWidget, &MapWidget::setMiniMapSize, this, &main_view::onSetMiniMapSize);
    connect(mapWidget, &MapWidget::showDetailsOf, mob, &PlayerWidget::onShowDetailOf);

    //TASTI SCELTA
    choiceWidget = new ChoiceWidget(this);
    connect(choiceWidget, &ChoiceWidget::sendChoice, this, &main_view::choicePressed);
    connect(model, &Game::choiceOut, this, &main_view::showChoice);
    connect(this, &main_view::emitChoice, model, &Game::choiceDone);

    //TASTI MOVIMENTO
    moveWidget = new MoveWidget(this);

    //connetto view e model per muovere il personaggio nella mappa
    connect(moveWidget, &MoveWidget::emitDir, this, &main_view::movePressed);

    //FINESTRA DI DIALOGO
    dialogOutBox = new QTextEdit(this);
    dialogOutBox->setReadOnly(true);
    //dialogOutBox->setText("FINESTRA DI DIALOGO");
    connect(model, &Game::dialogOut, this, &main_view::printString);

    score = new QLabel(this);
    score->setText(QString::number(model->getScore()));

    //prima colonna (col = 0)
    grid->addWidget(charachter, 0, 0);
    grid->addWidget(inventory, 1, 0);
    grid->addWidget(musicSlider, 2, 0, Qt::AlignLeft);

    //seconda colonna (col = 1)
    grid->addWidget(mapWidget, 0, 1);
    grid->addWidget(dialogOutBox, 1, 1); //TODO mettere finestra di dialogo
    grid->addWidget(choiceWidget, 2, 1, Qt::AlignCenter);

    //terza colonna (col = 2)
    grid->addWidget(score, 1, 2, Qt::AlignCenter);
    grid->addWidget(moveWidget, 2, 2);
    grid->addWidget(mob, 0, 2); //TODO implementare in modo diverso per mob

}

main_view::~main_view(){}

void main_view::printString(QString s)
{
    dialogOutBox->setText(s);
}

void main_view::createMenu()
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

void main_view::createMusicSliderBox(){

    musicSlider = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    // controllo il volume
    //volumeSlider = ui->volumeSlider; // TODO sostitutire con (riga sotto)
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);

    connect(volumeSlider, &QSlider::valueChanged, this, &main_view::onVolumeChanged);

    // bottone per il muto
    muteButton = new QPushButton("Mute", this);
    connect(muteButton, &QPushButton::clicked, this, &main_view::onMute);

    layout->addWidget(muteButton);
    layout->addWidget(volumeSlider);
    musicSlider->setLayout(layout);

    //musicSlider->setFixedWidth(200);
    //musicSlider->setFixedHeight(65);
    musicSlider->setFixedSize(200, 65);


    //musicSlider->setGeometry(20, 520, 200, 65);
}

void main_view::onPosChanged(const QVector<QVector<Tile>> &miniMap, Coordinate relativePos) {
    MapWidget *mapwidget = mapWidget;
    mapwidget->refresh(miniMap, relativePos);
}

void main_view::onSetMiniMapSize(int dim) {
    emit setMiniMapSize(dim);
}

void main_view::movePressed(char dir){
    std::string s = "Ti sei mosso verso ";
    switch (dir){
        case 'W':
            s += "su";
        break;
        case 'A':
            s += "sinistra";
        break;
        case 'S':
            s += "giu";
        break;
        case 'D':
            s += "destra";
        break;
    }
    dialogOutBox->setText(QString::fromStdString(s));
    model->move(dir);
}

void main_view::showChoice(QVector<Game::Choice> c)
{
    //mostriamo le scelte
    choiceWidget->setChoices(c);
}

void main_view::choicePressed(Game::Choice c)
{
    choiceWidget->cleanGrid();
    emit emitChoice(c);
}

void main_view::onVolumeChanged(int volume) {
    // se il volume è a zero mute è disabilitato
    if(volume == 0) muteButton->setDisabled(true);
    else muteButton->setDisabled(false);
    // emetto il segnale verso il controller
    emit volumeChanged(volume);
}

void main_view::onMute() {
    volumeSlider->setValue(0);
}
