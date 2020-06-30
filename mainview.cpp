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

    //fisso la grandezza della finestra del programma
    setFixedSize(1024, 600);

    //setto il titolo della finestra
    setWindowTitle("Dungeons & Programmazione 2");


    createMenu();
    createMusicSliderBox();
    createMoveBox();
    createButtonBox();

    choiceWidget = new ChoiceWidget(this);
    choiceWidget->move(0,100);
    connect(choiceWidget, &ChoiceWidget::sendChoice, this, &MainView::choicePressed);
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

void MainView::movePressed(char dir){
    //codice per muovere
    //ui->textEdit->append(QString(dir)); //placeholder per test
    qDebug() << "muovi: " << dir;
}

void MainView::createMenu()
{
    menuBar = new QMenuBar(this);

    fileMenu = new QMenu("&File", menuBar);
    exitAction = new QAction("E&xit");
    saveAction = new QAction("&Save");


    //aggiungo le azioni al menu
    fileMenu->addAction(exitAction);
    fileMenu->addAction(saveAction);

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

    moveBox->setGeometry(800, 350, 150, 130);

    connect(moveWidget, &MoveWidget::emitDir, this, &MainView::movePressed);
}

void MainView::createButtonBox()
{
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    //connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    //connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    buttonBox->setGeometry(840, 495, 170, 150);
}

