#include <QFileDialog>
#include <QJsonArray>

#include "main_dialog.h"
#include "main_dialog.h"
#include "main_dialog.h"


main_dialog::main_dialog(bool& refNewGame, Game *g, QWidget *parent)
    : QMainWindow(parent)
    , game(g)
    , newGame(refNewGame)
{
    setWindowTitle("Dungeons & Programming 2");
    setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setFixedSize(1024, 600);
    setMenuBar();

    connect(game, &Game::youDied, this, &main_dialog::onDie);

    mainWidget = new main_view(g, parent);
    setCentralWidget(mainWidget);
}

void main_dialog::setMenuBar()
{
    menubar = menuBar();
    //parent senza valore di default su alcune versioni di QT (ad esempio in laboratorio)
    mFile = new QMenu("&File", nullptr);
    mNewGame = new QAction("&Nuova Partita", nullptr);
    mSavePlayer = new QAction("Sal&va Personaggio", nullptr);
    mEsci = new QAction("&Esci", nullptr);
    mFile->addAction(mNewGame);
    mFile->addSeparator();
    mFile->addAction(mSavePlayer);
    mFile->addSeparator();
    mFile->addAction(mEsci);
    menubar->addMenu(mFile);

    mInfo  = new QMenu("&Info", nullptr);
    mShowInfo = new QAction("Inf&o sviluppatori", nullptr);
    mShowRank = new QAction("&Rank", nullptr);
    mInfo->addAction(mShowInfo);
    mFile->addSeparator();
    mInfo->addAction(mShowRank);
    menubar->addMenu(mInfo);

    mHelp = new QMenu("&Help", nullptr);
    mLegend = new QAction("&Legenda", nullptr);
    mHelp->addAction(mLegend);
    menubar->addMenu(mHelp);


    connect(mNewGame, SIGNAL(triggered(bool)), this, SLOT(newGameSlot()));
    connect(mNewGame, SIGNAL(triggered(bool)), this, SLOT(confirmSavePunt()));
    connect(mNewGame, SIGNAL(triggered(bool)), this, SLOT(confirmSavePg()));
    connect(mNewGame, SIGNAL(triggered(bool)), this, SLOT(close())); //TODO displayare una finestra e chiedere di salvare

    connect(mSavePlayer, SIGNAL(triggered(bool)), this, SLOT(savePlayerToJson()));

    connect(mShowRank, SIGNAL(triggered(bool)), this, SLOT(displayHallOfFame()));
    //connect(mSave, SIGNAL(triggered(bool)), this, SLOT(confirmSave())); //TODO same as above

    connect(mEsci, SIGNAL(triggered(bool)), this, SLOT(confirmSavePunt()));
    connect(mEsci, SIGNAL(triggered(bool)), this, SLOT(confirmSavePg()));//TODO same as above
    connect(mEsci, SIGNAL(triggered(bool)), this, SLOT(close())); //TODO same as above

    connect(mShowInfo, SIGNAL(triggered(bool)), this, SLOT(showInf()));

    connect(mLegend, SIGNAL(triggered(bool)), this, SLOT(showLegend()));

}

void main_dialog::newGameSlot()
{
    newGame = true;
}

void main_dialog::onDie()
{
    QMessageBox::warning(0,"Ops..", "SEI MORTO");
    confirmSavePunt();
    //close();
}

void main_dialog::showInf()
{
    QString str = QString("Applicazione creata da:\n\n %1\n %2\n %3").arg("Franchin Alessandro")
                                                                     .arg("Pagotto Matteo")
                                                                     .arg("Pagotto Manuel");

    QMessageBox::information(0, "Infomazioni", str);
}

void main_dialog::showLegend()
{
    QString str = QString("%1\n%2\n%3").arg("P - Personaggio")
                                       .arg("N - Nemico")
                                       .arg("I - Oggetto");

    QMessageBox::information(0, "Legenda", str);
}


void main_dialog::confirmSavePunt()
{
    QMessageBox salvaPunt;
    salvaPunt.setText("Vuoi salvare il punteggio?");
    salvaPunt.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    int ret = salvaPunt.exec();

    if(ret == QMessageBox::Save){
        game->saveScoreSlot();
    }

}

void main_dialog::confirmSavePg()
{
    QMessageBox salvaPg;
    salvaPg.setText("Vuoi salvare personaggio?");
    salvaPg.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
    int ret = salvaPg.exec();

    if(ret == QMessageBox::Save){
        savePlayerToJson();
    }
}

void main_dialog::savePlayerToJson()
{
    QFileDialog dialog(this);
    dialog.setNameFilter("*.json");
    QString fileName = dialog.getSaveFileName(this, "", "", "Json File (*.json)");

    //controllo che finisca con json, altrimenti lo aggiungo
    if(!fileName.endsWith(".json")) {
        fileName += ".json";
    }

    if(fileName != "") {
        QFile saveLocation(fileName);

        QJsonObject insertPlayer;

        insertPlayer["Caratteristiche"] = game->characterToJson(game->getPlayer());
        insertPlayer["Arma"] = game->itemToJson(game->getPlayer()->getWeapon());
        insertPlayer["Armatura"] = game->itemToJson(game->getPlayer()->getArmor());

        QJsonDocument doc(insertPlayer);
        if(!saveLocation.open(QIODevice::WriteOnly)) {
            return;
        }
        saveLocation.write(doc.toJson());
    }
    return;
}

void main_dialog::displayHallOfFame()
{
//    QString filePlayer = QFileDialog::getOpenFileName(Q_NULLPTR
//                                                      , "Carica file Personaggio"
//                                                      , "../"
//                                                      , "File Player(*.fpg);;All files(*)");


//    if(filePlayer.isEmpty()) return;
//    else {
//        QFile f(filePlayer);

//        if(!f.open(QIODevice::ReadOnly)){
//            //QMessageBox::warning(Q_NULLPTR, "Impossibile aprire il file", f.errorString());
//            emit warningFile(f.errorString());
//            return;
//        }
//        QString on_json = f.readAll();

//        QJsonParseError jsonError;

//        QJsonDocument d_json = QJsonDocument::fromJson(on_json.toUtf8(), &jsonError);

//        if(!jsonError.error){

//            QJsonObject json = d_json.object();

//            pg = new Player(json["nome"].toString().toStdString(), json["vita"].toInt(), json["mana"].toInt());
//        } else {
//            emit loadPlayerFromFile(jsonError);
//        }
//    }
}

