#include "main_view.h"

main_view::main_view(Game *g, QWidget *parent)
    : QWidget(parent)
    , model(g)
{

    //LAYOUT PRINCIPALE
    mapWidget = new MapWidget(this,19);
    choiceWidget = new ChoiceWidget(this);
    moveWidget = new MoveWidget(this);
    charachter = new PlayerWidget(model->getPlayer(), this);
    grid = new QGridLayout(this);
    setLayout(grid);

    createMusicSliderBox();

    dialogOutBox = new QTextEdit(this);
    dialogOutBox->setReadOnly(true);
    //dialogOutBox->setDisabled(true);


    mob = new PlayerWidget(Randomizer::getRandomMob(), this); //TODO dichiararlo sul .h
    mob->clear();


    //pulisco view del mob
    connect(model, &Game::clearViewMob, this, &main_view::clearEnemy);

    //aggiorno view del mob
    connect(model, &Game::mobEncounter, this, &main_view::setEnemy);

    //aggiorno vita giocatore/mob
    connect(model, &Game::dannoPlayer, this, &main_view::setPlayerHealth);
    connect(model, &Game::dannoMob, this, &main_view::setMobHealth);

    //INVENTARIO
    inventory= new QListWidget(); //lista di widget (inventario)
    inventory->setFixedWidth(270);

    //MAPPA

    // connetto i segnali per la mappa dal modello a view e viceversa
    connect(model, &Game::posChanged, mapWidget, &MapWidget::refresh);  // da model a view
    connect(mapWidget, &MapWidget::setMiniMapSize, model, &Game::onSetMiniMapSize); // da view a model
    //connect(mapWidget, &MapWidget::setMiniMapSize, this, &main_view::onSetMiniMapSize);
    connect(mapWidget, &MapWidget::showDetailsOf, mob, &PlayerWidget::onShowDetailOf);

    mapWidget->syncDimension();
    //TASTI SCELTA

    connect(choiceWidget, &ChoiceWidget::sendChoice, this, &main_view::choicePressed);
    connect(model, &Game::choiceOut, this, &main_view::showChoice);
    connect(this, &main_view::emitChoice, model, &Game::choiceDone);

    //TASTI MOVIMENTO

    connect(model, &Game::setEnableMove, moveWidget, &MoveWidget::setEnabled);
    //connetto view e model per muovere il personaggio nella mappa
    connect(moveWidget, &MoveWidget::emitDir, this, &main_view::movePressed);

    //FINESTRA DI DIALOGO
    connect(model, &Game::dialogOut, this, &main_view::printString);

    score = new QLabel(this);
    score->setText(QString::number(model->getScore()));

    connect(model, &Game::newScore, this, &main_view::setNewScore);

    //prima colonna (col = 0)
    grid->addWidget(charachter, 0, 0);
    grid->addWidget(inventory, 1, 0);
    grid->addWidget(musicSlider, 2, 0, Qt::AlignLeft);

    //seconda colonna (col = 1)
    grid->addWidget(mapWidget, 0, 1);
    grid->addWidget(dialogOutBox, 1, 1);
    grid->addWidget(choiceWidget, 2, 1, Qt::AlignCenter);

    //terza colonna (col = 2)
    grid->addWidget(score, 1, 2, Qt::AlignCenter);
    grid->addWidget(moveWidget, 2, 2);
    grid->addWidget(mob, 0, 2); //TODO implementare in modo diverso per mob

}

main_view::~main_view(){}

void main_view::printString(QString s)
{
    dialogOutBox->append(s);
}

void main_view::createMusicSliderBox(){

    musicSlider = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    // controllo il volume
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

    musicSlider->setFixedSize(200, 65);
}

void main_view::onPosChanged(const std::vector<std::vector<Tile>> &miniMap, Coordinate relativePos) {
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

void main_view::setPlayerHealth(int d)
{
    charachter->setHealth(d);
}

void main_view::setMobHealth(int d)
{
    mob->setHealth(d);
}

void main_view::setNewScore(int s)
{
    score->setText(QString::number(s));
}

void main_view::setEnemy(Mob* t)
{
    mob->setFields(t);
}

void main_view::clearEnemy()
{
    mob->clear();
}
