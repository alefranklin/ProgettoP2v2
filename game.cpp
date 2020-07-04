#include "game.h"

// per il random (provvisorio)
#include <QtGlobal>
#include <QTime>
#include <QFile>

const int Game::mapSize = 150;

const QString Game::fileScore = "../Save.txt";


Game::Game(Player* player, QObject *parent) : QObject(parent)
  , miniMapSize(20) // 20 di default
  , combat(nullptr)
  , pg(player)
  , map(mapSize)
{
    // genero mostri in tutta la mappa partedo dal centro
    pushRandomMob(mapSize/2, Coordinate(mapSize/2, mapSize/2));
    pushRandomItem(mapSize/2, Coordinate(mapSize/2, mapSize/2));

    //per il rand di test
//    QTime time = QTime::currentTime();
//    qsrand((uint)time.msec());



    //la grandezza della minimappa è settata quindi aggiorno la view
    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
}

Game::~Game()
{
    qDebug() << "Distruttore game";
    if(pg) {
        delete pg;
        qDebug() << "Elimino pg";
    }

}

void Game::dialog(QString s)
{
    emit dialogOut(s);
    //emit choiceOut(Choice::escape());

}

QJsonObject Game::itemToJson(Item *i){
    QJsonObject json;
    json.insert("nome",QString::fromStdString(i->getNome()));
    if(Game::isArmor(i)){
        const Armor *a = dynamic_cast<const Armor*>(i);
        //json.insert("nome",QString::fromStdString(a->getNome()));
        json.insert("tipo","Armatura");
        json.insert("difesa",a->getArmatura());
    }
    if(Game::isBow(i)){
        const Bow *b = dynamic_cast<const Bow*>(i);
        //json.insert("nome",QString::fromStdString(b->getNome()));
        json.insert("tipo","Arco");
        json.insert("danno",b->getDamage());
        json.insert("frecce",b->getArrow());
    }
    if(Game::isSword(i)){
        const Sword *s = dynamic_cast<const Sword*>(i);
        //json.insert("nome",QString::fromStdString(s->getNome()));
        json.insert("tipo","Spada");
        json.insert("danno",s->getDamage());
        json.insert("range",s->getRange());
    }
    if(Game::isMagicWeapon(i)){
        const MagicWeapon *mw = dynamic_cast<const MagicWeapon*>(i);
        //json.insert("nome",QString::fromStdString(mw->getNome()));
        json.insert("tipo","Arma Magica");
        json.insert("danno",mw->getDamage());
        json.insert("effetto",mw->getEffect());
        json.insert("mana",mw->getMana());
    }
    return json;
}

unsigned int Game::getScore() const
{
    return score;
}

void Game::usePotionMana() { emit dialogOut("sto usando la pozione del mana"); }

void Game::usePotionHealth() { emit dialogOut("sto usando la pozione della vita"); }

void Game::startCombat(Tile &t) {
    combat = new CombatState(t.e, nullptr);
    emit dialogOut("sei entrato in combattimento.\nCosa vuoi fare?");
    // usare combat per tenere traccia dello stato del sistema
    combat->turno_player = Randomizer::randomNumberBetween(0,1);
    if(combat->turno_player){
        QVector<Choice> c;
        c << Choice::attack() << Choice::escape();
    } else {
        dialogOut("Il mostro attacca per primo");
        pg->setDamage(5);

    }
}

void Game::attacca() {

}

void Game::scappa() {
    //emit dialogOut("Tiro i dadi per vedere se riesco a scappare");
    // con una certa probabilita scappa
    if(randInt(0,1)) {
        moveBack();
    }
    else {
        emit dialogOut("non sei riuscito a scappare!");
        //startCombat();
    }
}

void Game::endCombat() {
    delete combat;
    combat = nullptr;
}

int Game::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

void Game::pushRandomMob(int range, Coordinate c) {
    std::vector<Coordinate> t = map.getWalkableTile(range, c);

    // aggiungo i mob
    for(auto it = t.begin(); it != t.end(); ++it) {

        Tile &t = map.getTileIn(*it);

        // salto il tile se il vettore non è vuoto
        if( ! t.e.empty())  continue;

        //con una certa probabilità aggiungo un mob (30%)
        if( Randomizer::randomNumberBetween(0, 100) < 2 ) {
            t.e.push_back( Randomizer::getRandomMob() );
        }
    }

}

void Game::choiceDone(Choice c)
{
    emit dialogOut("scelta fatta: "+c.getLabel()+"\nadesso devo gestire le varie funzioni delle scelte");

    switch(c) {
    case 0:{
        scappa();
        break;
    }
    case 1:{
        //startCombat(map.getCurrentTile());
        break;
    }

    case 2:{
        startCombat(map.getCurrentTile());
        break;
    }
    case 5:{
        //aggiungi item all'inventario
        Tile &t = map.getCurrentTile();
        Item* item_preso = dynamic_cast<Item*>(t.e[0]);
        emit dialogOut("Hai preso l'oggetto");
        t.e.clear();
        emit setEnableMove(true);
        break;
    }
    case 6:{
        emit dialogOut("Hai lasciato l'oggetto");
        emit setEnableMove(true);
        break;
    }
    }

}

void Game::move(char m) {
    switch (m) {
    case 'W': map.moveUP();     break;
    case 'A': map.moveLEFT();   break;
    case 'S': map.moveDOWN();   break;
    case 'D': map.moveRIGHT();  break;
    default:  break;
    }

    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());

    //controllare il tile se esiste un nemico if(map.getCurrentTile().e) scappa o attacca

    Tile &t = map.getCurrentTile();
    QVector<Choice> c;

    if(!t.e.empty()) {
        emit setEnableMove(false);

        if(isMob(t.e[0])){
            c << Choice::attack() << Choice::escape();
        }

        if(isItem(t.e[0])){
            emit dialogOut("Hai trovato "+QString::fromStdString(dynamic_cast<Item*>(t.e[0])->getNome()));
            c << Choice::pickItem() << Choice::leaveItem();
        }

        emit choiceOut(c);
    }

    //pushRandomItem(miniMapSize, map.getPos());
}

void Game::onSetMiniMapSize(int s) {
    if(s > 0 && s <= map.getMapDimension() && s != miniMapSize) miniMapSize = s;
    else miniMapSize = mapSize;

    //la grandezza è cambiata quindi aggiorno la mappa
    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
}

void Game::saveScoreSlot(){
    QFile file(fileScore);

    qDebug() << "entro salva file";

    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        QTextStream outputStream(&file);

        outputStream << "Giocatore: " << pg->getName() << "\t Punteggio: " << score << "\n";

        file.close();
    }

}

void Game::savePlayerSlot()
{
    QString filePlayer = QFileDialog::getSaveFileName(Q_NULLPTR, "Save Player", "../", "File Player(*.fpg)");

    if(filePlayer.isEmpty()) return;
    else {
        QFile file(filePlayer);

        if(!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(nullptr, "Unable to open file", file.errorString());
            return;
        }

        QJsonObject json; //= QJsonObject::fromVariantMap(v_map);

        json["nome"] = pg->getName();
        json["vita"] = pg->getVita();
        json["mana"] = pg->getMana();
        json["armatura"] = itemToJson(pg->getArmor());
        json["arma"] = itemToJson(pg->getWeapon());

        QJsonDocument d_json;
        d_json.setObject(json);

        file.write(d_json.toJson());

        file.close();
    }
}

void Game::loadPlayerSlot(bool)
{
    QString filePlayer = QFileDialog::getOpenFileName(Q_NULLPTR
                                                      , "Carica file Personaggio"
                                                      , "../"
                                                      , "File Player(*.fpg);;All files(*)");

    if(filePlayer.isEmpty()) return;
    else {
        QFile f(filePlayer);

        if(!f.open(QIODevice::ReadOnly)){
            QMessageBox::warning(Q_NULLPTR, "Impossibile aprire il file", f.errorString());
            return;
        }
        QString on_json = f.readAll();

        QJsonDocument d_json = QJsonDocument::fromJson(on_json.toUtf8());
        QJsonObject json = d_json.object();


        //qDebug() << json["nome"].toString();


        pg = new Player(json["nome"].toString(), json["vita"].toInt(), json["mana"].toInt());
    }

}

bool Game::isItem(const Entity *e) { return (dynamic_cast<const Item*>(e)) ? true : false; }
bool Game::isWeapon(const Entity *e) { return (dynamic_cast<const Weapon*>(e)) ? true : false; }
bool Game::isArmor(const Entity *e) { return (dynamic_cast<const Armor*>(e)) ? true : false; }
bool Game::isPotion(const Entity *e) { return (dynamic_cast<const Potion*>(e)) ? true : false; }
bool Game::isCharacter(const Entity *e) { return (dynamic_cast<const Character*>(e)) ? true : false; }
bool Game::isMob(const Entity *e) { return (dynamic_cast<const Mob*>(e)) ? true : false; }
bool Game::isPlayer(const Entity *e) { return (dynamic_cast<const Player*>(e)) ? true : false; }
bool Game::isSword(const Entity *e) { return (dynamic_cast<const Sword*>(e)) ? true : false;}
bool Game::isBow(const Entity *e) { return (dynamic_cast<const Bow*>(e)) ? true : false;}
bool Game::isMagicWeapon(const Entity *e) { return (dynamic_cast<const MagicWeapon*>(e)) ? true : false;}

Character *Game::getPlayer() { return pg; }

void Game::moveBack()
{
    emit dialogOut("Sei riuscito a scappare");
    map.moveBack();
    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
    emit setEnableMove(true);
}
