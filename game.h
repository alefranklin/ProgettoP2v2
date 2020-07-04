#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "character.h"
#include "item.h"
#include "randomizer.h"
#include <QObject>
#include <QString>
#include <QSaveFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDebug>



class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game(Player* player, QObject *parent = nullptr);
    ~Game();

    class Choice {
    public:
        Choice(QString l = "Null", int n = -1): label(l), number(n) {}
        QString getLabel() { return label; }
        int getNumber() { return number; }
        static Choice escape() { return Choice("Scappa", 0); }
        static Choice combat() { return Choice("Combatti", 1); }
        static Choice attack() { return Choice("Attacca", 2); }
        static Choice useManaPotion() { return Choice("Usa pozione mana", 3); }
        static Choice useHealthPotion() { return Choice("Usa pozione vita", 4); }
        operator int() const
        {
           return number;
        }
    private:
        QString label;
        int number;
    };

    static bool isItem(const Entity *e);
    static bool isWeapon(const Entity *e);
    static bool isArmor(const Entity *e);
    static bool isPotion(const Entity *e);
    static bool isCharacter(const Entity *e);
    static bool isMob(const Entity *e);
    static bool isPlayer(const Entity *e);
    static bool isSword(const Entity *e);
    static bool isBow(const Entity *e);
    static bool isMagicWeapon(const Entity *e);
    Character* getPlayer();
    void moveBack() { 
        //map.moveBack(); 
        emit dialogOut("sono fuggito"); 
    }
    void dialog(QString s);
    QJsonObject itemToJson(Item *i);
signals:
    // emetto segnale per il dialogo
    void dialogOut(QString s);
    // emetto segnale per inviare le scelte
    void choiceOut(Choice c);
    // il giocatore si è spostato, emetto la nuova minimappa
    void posChanged(const QVector<QVector<Tile>> &miniMap, Coordinate relativePos);
public slots:
    // slot che gestisce le scelte fatte dal giocatore
    void choiceDone(Choice c);
    // gestisco segnale movimento
    void move(char m);
    // gestisco segnale regolazione grandezza minimappa
    void onSetMiniMapSize(int s);
    //salvo il punteggio
    void saveScoreSlot();
    //salvo il personaggio
    void savePlayerSlot();
    //carico il personaggio
    void loadPlayerSlot(bool);

    //DEBUG
    //elimino pg e lo setto a nullptr per nuova partita
    void setPgNull()
    {
        delete pg;
        pg = nullptr;
    }

//PRIVATE DI GAME
private:

    Player *pg;
    Map map;
    unsigned int score = 0;


    static const QString fileScore;
    static const int mapSize;
    int miniMapSize;


    // struttura per memorizzare lo stato del combattimento in corso
    struct CombatState {
        unsigned int numero_turno;
        bool turno_player;
        QVector<Entity*> &enemies;
        Player *player;
        CombatState(QVector<Entity*> &e, Player *pg): enemies(e), player(pg) {}
    };
    CombatState* combat;


    // funzioni test per vedere
    void scappa();
    void usePotionMana();
    void usePotionHealth();
    void startCombat(Tile &t);
    void attacca();
    void endCombat();
    int randInt(int low, int high);

    void pushRandomMob(int range, Coordinate c) {
        Qvector<Tile&> t = map.getWalkableTile(range, c);

        // aggiungo i mob
        for(auto it = t.begin(); it != t.end(), ++it) {
            
            // salto il tile se il vettore non è vuoto
            if( ! *it.e.isEmpty() ) continue;

            //con una certa probabilità aggiungo un mob (30%)
            if( Randomizer::randomNumberBetween(0, 100) < 30 ) {
                *it = ;
                *it.e.push_back( Randomizer::getRandomMob() )
            }
        }

    }

    void pushRandomItem(in range, Coordinate c) {
        Qvector<Tile&> t = map.getWalkableTile(range, c);

        // aggiungo i mob
        for(auto it = t.begin(); it != t.end(), ++it) {
            
            // salto il tile se il vettore non è vuoto
            if( ! *it.e.isEmpty() ) continue;

            if (Randomizer::randomNumberBetween(0, 100) < 20 ) {
                    // 20 % oggetto tra tutti quelli possibili quindi spada, armatura, pozze
                    *it.e.push_back( Randomizer::getRandomItem() )

            } else {
                // solo pozzioni

                // TODO sistemare sto pezzo in base a come facciomo la generazione delle pozze
                if ( Randomizer::randomNumberBetween(0, 100) < 65 ) {
                    // 65 % vita
                    *it.e.push_back( Randomizer::getRandomPotion() )
                } else {
                    // 35% mana
                    *it.e.push_back( Randomizer::getRandomPotion() )
                }
            }
        }

    }


};
#endif // GAME_H
