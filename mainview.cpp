#include "mainview.h"
#include "movebutton.h"

#include <QObject>
#include <QTextEdit>
#include <QPushButton>
#include <QDebug>
#include <QDialogButtonBox>
#include <QLayout>


MainView::MainView(Game *g, QWidget *parent)
    : QWidget(parent)
    , model(g)
{
    // connetto i segnali per la mappa dal modello a view e viceversa
    connect(model, &Game::posChanged, this, &MainView::onPosChanged);  // da model a view
    connect(this, &MainView::setMiniMapSize, model, &Game::onSetMiniMapSize); // da view a model

    //ui->setupUi(this);


    //fisso la grandezza della finestra del programma
    setFixedSize(1024, 600);

    //setto il titolo della finestra
    setWindowTitle("Dungeons & Programmazione 2");


    // connetto i segnali di MapWidget
    //MapWidget *mapWidget = ui->mapwidget;
    //connect(mapWidget, &MapWidget::setMiniMapSize, this, &MainView::onSetMiniMapSize);


    //TODO solo per il dialogo
    //QPushButton* bt = ui->dialogo;
    //connect(bt, &QPushButton::clicked, this, &MainView::onDialogPressed);

    createMenu();
    createMusicSliderBox();
    createMoveBox();
    createChoiceBox();
    createDialogBox();
    createCharachterBox();
    createInventoryBox();
    createMapBox();
    createEnemyBox();

}

MainView::~MainView()
{
    delete this;
}

void MainView::printString(QString s)
{
    //ui->textEdit->append(s);
}

void MainView::showChoice(QVector<Game::Choice> c)
{
    //mostriamo le scelte
    choiceWidget->setChoices(c);
}

void MainView::choicePressed(Game::Choice c)
{
    choiceWidget->cleanGrid();
    emit emitChoice(c);
}

void MainView::onDialogPressed()
{
    emit emitDialog();
}

void MainView::onVolumeChanged(int volume) {
    // se il volume è a zero mute è disabilitato
    if(volume == 0) muteButton->setDisabled(true);
    else muteButton->setDisabled(false);
    // emetto il segnale verso il controller
    emit volumeChanged(volume);
}

void MainView::onMute() {
    volumeSlider->setValue(0);
}

void MainView::onPosChanged(const std::vector<std::vector<Tile>> &miniMap, Coordinate relativePos) {
    //MapWidget *mapWidget = ui->mapwidget;
    //mapWidget->refresh(miniMap, relativePos);
}

void MainView::onSetMiniMapSize(int dim) {
    emit setMiniMapSize(dim);
}

void MainView::movePressed(char dir){
    //codice per muovere
    //ui->textEdit->append(QString(dir)); //placeholder per test
    qDebug() << "muovi: " << dir;
}

void MainView::createMenu()
{
    menuBar = new QMenuBar(this);

    fileMenu = new QMenu("&File", menuBar);
    saveAction = new QAction("&Save");
    exitAction = new QAction("E&xit");


    //aggiungo le azioni al menu
    fileMenu->addAction(saveAction);
    fileMenu->addAction(exitAction);

    //aggiungo il menu alla barra
    menuBar->addMenu(fileMenu);


    connect(exitAction, SIGNAL(triggered()), this, SLOT(accept()));

}

void MainView::createMusicSliderBox(){

    QGroupBox *musicSlider = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    // controllo il volume
    //volumeSlider = ui->volumeSlider; // TODO sostitutire con (riga sotto)
    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setValue(50);

    connect(volumeSlider, &QSlider::valueChanged, this, &MainView::onVolumeChanged);

    // bottone per il muto
    muteButton = new QPushButton("Mute", this);
    connect(muteButton, &QPushButton::clicked, this, &MainView::onMute);

    layout->addWidget(muteButton);
    layout->addWidget(volumeSlider);
    musicSlider->setLayout(layout);

    musicSlider->setGeometry(20, 520, 200, 65);
}

void MainView::createMoveBox()
{
    //aggiungo bottoni per muovere iQTableWidgetl personaggio
    moveWidget = new MoveWidget(this);

    QGroupBox *moveBox = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(moveWidget);
    moveBox->setLayout(layout);

    moveBox->setGeometry(800, 445, 170, 150);

    connect(moveWidget, &MoveWidget::emitDir, this, &MainView::movePressed);
}

void MainView::createChoiceBox()
{
    choiceWidget = new ChoiceWidget(this);

    QGroupBox *choiceBox = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(choiceWidget);
    choiceBox->setLayout(layout);

    choiceBox->setGeometry(360, 445, 300, 150);
    //choiceWidget->move(0,100); //non serve era solo per spostarlo che si sovrapponeva

    connect(choiceWidget, &ChoiceWidget::sendChoice, this, &MainView::choicePressed);
}

void MainView::createDialogBox()
{
    QTextEdit *prov = new QTextEdit(this);
    prov->setPlainText("FINESTRA DI DIALOGO");

    QGroupBox *characBox = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(prov);
    characBox->setLayout(layout);

    characBox->setGeometry(335, 335, 350, 150);
}

void MainView::createCharachterBox()
{
    QTextEdit *prov2 = new QTextEdit(this);
    prov2->setPlainText("PERSONAGGIO");

    QGroupBox *characBox = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(prov2);
    characBox->setLayout(layout);

    characBox->setGeometry(15, 15, 330, 360);
}

void MainView::createInventoryBox()
{
    QTextEdit *prov3 = new QTextEdit(this);
    prov3->setPlainText("INVETARIO");

    QGroupBox *characBox = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(prov3);
    characBox->setLayout(layout);

    characBox->setGeometry(15, 360, 330, 150);
}

void MainView::createMapBox()
{
    QTextEdit *prov4 = new QTextEdit(this);
    prov4->setPlainText("MAPPA");

    QGroupBox *characBox = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(prov4);
    characBox->setLayout(layout);

    characBox->setGeometry(335, 15, 350, 350);
}

void MainView::createEnemyBox()
{
    QTextEdit *prov5 = new QTextEdit(this);
    prov5->setPlainText("NEMICO");

    QGroupBox *characBox = new QGroupBox(this);
    QHBoxLayout *layout = new QHBoxLayout;

    layout->addWidget(prov5);
    characBox->setLayout(layout);

    characBox->setGeometry(680, 15, 330, 360);
}
