#ifndef GAME_H
#define GAME_H

#include "entity.h"
#include "map.h"
#include <QObject>
#include <QString>
#include <vector>
#include <QVector>
#include <QJsonObject>

class Player;
class Character;
class Item;

class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game(Character *player, QObject *parent = nullptr);
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
        static Choice pickItem() { return Choice("Raccogli", 5); }
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

    void moveBack();

    void dialog(QString s);

    QJsonObject itemToJson(Item *i);

    unsigned int getScore() const;

    //DEBUG
    //elimino pg e lo setto a nullptr per nuova partita
    void setPgNull();

signals:
    // emetto segnale per il dialogo
    void dialogOut(QString s);
    // emetto segnale per inviare le scelte
    void choiceOut(QVector<Choice> c);
    // il giocatore si è spostato, emetto la nuova minimappa

    void posChanged(const std::vector<std::vector<Tile>> &miniMap, Coordinate relativePos);

    //cambio lo stato dei pulsanti di movimento
    void setEnableMove(bool);
    
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


//PRIVATE DI GAME
private:

    Character *pg;
    Map map;
    unsigned int score = 0;


    static const QString fileScore;
    static const int mapSize;
    int miniMapSize;


    // struttura per memorizzare lo stato del combattimento in corso
    struct CombatState {
        unsigned int numero_turno;
        bool turno_player;
        std::vector<Entity*> &enemies;
        Player *player;
        CombatState(std::vector<Entity*> &e, Player *pg): enemies(e), player(pg) {}
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

    /* creo mob random */
    void pushRandomMob(int range, Coordinate c);

    /* creo item random */
    void pushRandomItem(int range, Coordinate c);


};
#endif // GAME_H
