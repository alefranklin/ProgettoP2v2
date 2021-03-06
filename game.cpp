#include "game.h"

#include "character.h"
#include "item.h"
#include "randomizer.h"
#include "player.h"
#include "bow.h"
#include "sword.h"
#include "magicweapon.h"
#include "armor.h"
#include "mob.h"
#include "potion.h"

#include <QSaveFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>


// per il random (provvisorio)
#include <QtGlobal>
#include <QTime>
#include <QFile>

const int Game::mapSize = 150;

const QString Game::fileScore = "Classifica.txt";

Game::Game(Character* player, QObject *parent) : QObject(parent)
  , pg(player)
  , map(mapSize)
  , miniMapSize(20) // 20 di default
  , combat(nullptr)
{
    // genero mostri in tutta la mappa partedo dal centro
    pushRandomMob(mapSize/2, Coordinate(mapSize/2, mapSize/2));
    pushRandomItem(mapSize/2, Coordinate(mapSize/2, mapSize/2));

    //per il rand di test
//    QTime time = QTime::currentTime();
//    qsrand((uint)time.msec());



    //la grandezza della minimappa è settata quindi aggiorno la view
    emit posChanged(map.getMiniMap(miniMapSize), map.getRelativePos());
    inventoryRefreshSlot();
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

QJsonObject Game::characterToJson(Character* c)
{
  QJsonObject json;

  for(auto &elem : c->getAttributes()) {
      json.insert(QString::fromStdString(elem.name),
                  QString::fromStdString(elem.val));
  }

  return json;
}

QJsonObject Game::itemToJson(Item *i){
    QJsonObject json;

    for( auto &elem : i->getAttributes()) {
        json.insert(QString::fromStdString(elem.name),
                    QString::fromStdString(elem.val));
    }

    return json;
}


/* creo l'oggetto dalle caratteristiche ritorno nullptr se fallisco */
Item *Game::JsonToItem(QJsonObject &obj){
    Item *i = nullptr;

    if(obj["Tipo"].toString() == "Spada") {
        i = new Sword(obj["Nome"].toString().toStdString(),
                      obj["Danno"].toString().toInt(),
                      obj["Range"].toString().toInt());
    }

    if(obj["Tipo"].toString() == "Arco") {
        i = new Bow(obj["Nome"].toString().toStdString(),
                    obj["Immagine"].toString().toStdString(),
                    obj["Danno"].toString().toInt(),
                    obj["Frecce"].toString().toInt());
    }

    if(obj["Tipo"].toString() == "ArmaMagica") {
        i = new MagicWeapon(obj["Nome"].toString().toStdString(),
                            obj["Danno"].toString().toInt(),
                            obj["Effetto"].toString().toInt(),
                            obj["Mana"].toString().toInt());
    }

    if(obj["Tipo"].toString() == "Armatura") {
        i = new Armor(obj["Nome"].toString().toStdString(),
                      obj["Armatura"].toString().toInt());
    }

    if(obj["Tipo"].toString() == "Pozione") {
        bool vita = (obj["Vita"].toString() == "si") ? true : false;
        bool mana = (obj["Mana"].toString() == "si") ? true : false;
        i = new Potion(obj["Nome"].toString().toStdString(),
                       obj["Effetto"].toString().toInt(),
                       vita, mana);
    }

    return i;
}

unsigned int Game::getScore() const
{
    return score;
}

void Game::setPgNull()
{
    delete pg;
    pg = nullptr;
}

void Game::setScore(unsigned int s)
{
    score = score + s;
}

void Game::usePotionMana() { emit dialogOut("sto usando la pozione del mana"); }

void Game::usePotionHealth() { emit dialogOut("sto usando la pozione della vita"); }

void Game::startCombat(Tile &t) {
    if(t.e && Game::isMob(t.e)) {
        Character* c = dynamic_cast<Character*>(t.e);
        combat = new CombatState(c, pg);
        emit dialogOut("Sei entrato in combattimento.\n\n");
        inCombat();
    } else {
        emit dialogOut("Provi a combattare ma ti accorgi che il mostro non è più lì.\n\n");
        emit setEnableMove(true);
    }
}

void Game::inCombat(){
    QVector<Choice> c;
    // usare combat per tenere traccia dello stato del sistema
    if(combat->first_turn){
        combat->first_turn = false;
        combat->turno_player = Randomizer::randomNumberBetween(0,1);
    }

    //controllo se il mostro è vivo
    if(dynamic_cast<Mob*>(combat->enemy)->isAlive()) {
        //se è il mio turno
        if(combat->turno_player){
                c << Choice::attack() << Choice::escape();
                combat->turno_player = false;
                emit choiceOut(c);
        }
        else { //turno del nemico
            int dannoFatto = combat->enemy->attacca(pg);
            dialogOut("Il mostro ti attacca.\n"
                      "Ti infligge "+QString::number(dannoFatto)+" danni.\n"
                      "Cosa vuoi fare?\n");
            combat->turno_player = true;

            Mob* m =  dynamic_cast<Mob*>(combat->enemy);

            //aggiorno view
            emit updatePlayer(dynamic_cast<Player*>(pg));
            emit updateMob(m);

            if(!pg->isAlive()){
                endCombat(false);
                return;
            }
            inCombat();
        }
    } else {
        endCombat(true);
        return;
    }
}

void Game::attacca() {
    emit dialogOut("Hai attaccato il nemico.\n\n");

    Mob* m = dynamic_cast<Mob*>(combat->enemy);

    int dannoFatto = pg->attacca(combat->enemy);

    if(typeid(*(pg->getWeapon())) == typeid(MagicWeapon) && pg->getMana() == 0){
        dialogOut("Hai finito il mana. Infliggi +"+QString::number(dannoFatto)+" danno.\nUsa una pozione per ripristinarlo.\n");
    } else {
        if (typeid(*(pg->getWeapon())) == typeid(Bow)) {
            dialogOut("Hai finito le frecce. Infliggi +"+QString::number(dannoFatto)+" danno.\nCambia arma.\n");
        }
        else emit dialogOut("Hai inflitto "+QString::number(dannoFatto)+" danni la nemico.\n");
    }

    //aggiorno view
    emit updateMob(m);
    emit updatePlayer(dynamic_cast<Player*>(pg));

    return;
}

void Game::scappa() {
    //emit dialogOut("Tiro i dadi per vedere se riesco a scappare");
    // con una certa probabilita scappa
    if(randInt(0,1)) {
        emit clearViewMob();
        moveBack();
    }
    else {
        emit dialogOut("Non sei riuscito a scappare!\n\n");
        if(!combat) {
            startCombat(map.getCurrentTile());
        } else {
            inCombat();
        }
    }
}

void Game::endCombat(bool victory) {
    delete combat;
    combat = nullptr;

    if(victory){
        map.getCurrentTile().e = nullptr;
        dialogOut("Hai ucciso il nemico. (+5 punti)\n\n");
        emit clearViewMob();
        setScore(5);
        emit newScore(score);
        emit setEnableMove(true);
    } else {
        emit youDied();
    }

    return;
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

        // salto il tile se è vuoto
        if(t.e)  continue;

        //con una certa probabilità aggiungo un mob (30%)
        if( Randomizer::randomNumberBetween(0, 100) < 2 ) {
            t.e = Randomizer::getRandomMob();
        }
    }

}

void Game::pushRandomItem(int range, Coordinate c) {
    std::vector<Coordinate> t = map.getWalkableTile(range, c);

    // aggiungo i mob
    for(auto it = t.begin(); it != t.end(); ++it) {

        Tile &t = map.getTileIn(*it);

        // salto il tile se è vuoto
        if(t.e) continue;

        if (Randomizer::randomNumberBetween(0, 200) < 1 ) {
            // 20 % oggetto tra tutti quelli possibili quindi spada, armatura, pozze
            t.e = Randomizer::getRandomItem();

        } /*else {
                // solo pozioni

                // TODO sistemare sto pezzo in base a come facciomo la generazione delle pozze

                if ( Randomizer::randomNumberBetween(0, 100) < 1 ) {
                    // 65 % vita
                    t.e.push_back( Randomizer::getRandomPotion() );
                } else {
                    // 35% mana
                    t.e.push_back( Randomizer::getRandomPotion() );
                }
            }*/
    }
}

void Game::choiceDone(Choice c)
{
    //emit dialogOut("scelta fatta: "+c.getLabel()+"\nadesso devo gestire le varie funzioni delle scelte");

    switch(c) {
    case 0:{
        scappa();
        break;
    }
    case 1:{
        startCombat(map.getCurrentTile());
        break;
    }

    case 2:{
        attacca();
        inCombat();
        break;
    }
    case 4:{
        //aggiungi item all'inventario
        emit setEnableMove(true);
        Tile &t = map.getCurrentTile();
        Item* item_preso = dynamic_cast<Item*>(t.e);

        (dynamic_cast<Player*>(pg))->inventoryAdd(item_preso);

        emit dialogOut("Hai preso l'oggetto.\n\n");
        emit inventoryRefreshSlot();
        t.e = nullptr;

        break;
    }
    case 5:{
        emit dialogOut("Hai lasciato l'oggetto.\n\n");
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

    if(t.e) {
        emit setEnableMove(false);

        if(isMob(t.e)){
            emit mobEncounter(dynamic_cast<Mob*>(t.e));
            c << Choice::combat() << Choice::escape();
        }

        if(isItem(t.e)){
            emit dialogOut("Hai trovato "+QString::fromStdString(dynamic_cast<Item*>(t.e)->getNome()));
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
    if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)){
        QTextStream out(&file);
        QString name = QString::fromStdString(pg->getName());
        out << name.toUtf8() << " " << score << "\n";
        file.close();
    }
}


void Game::loadPlayerSlot(bool)
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

void Game::inventoryRefreshSlot() {
    Player* p = dynamic_cast<Player*>(pg);
    if(p) {
        emit inventoryRefreshSGNL(p->getInventory());
    }
}

void Game::onSelectItem(int id) {
    Player *p = dynamic_cast<Player*>(pg);
    if (p) {
        Item *i = p->inventoryGetItem(id);
        if(i){
            if( Game::isWeapon(i) || Game::isArmor(i)) {
                p->equip(i);
             }
            else {
                Potion *consumable = dynamic_cast<Potion*>(i);
                if(consumable) p->usePotion(i);
            }
        }
        emit updatePlayer(p);
        emit inventoryRefreshSlot();
    }
}

void Game::onDeleteItem(int id) {
    Player *p = dynamic_cast<Player*>(pg);
    if (p) {
        p->inventoryDelete(id);
        emit inventoryRefreshSlot();
        emit dialogOut("Hai eliminato il tuo prezioso oggetto!");
    }
}

void Game::refreshPlayer() {
    Player *p = dynamic_cast<Player*>(pg);
    if(p) emit updatePlayer(p);
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


Game::CombatState::CombatState(Character* &e, Character *pg, bool f): first_turn(f)
  , enemy(e)
  , player(pg) {}
