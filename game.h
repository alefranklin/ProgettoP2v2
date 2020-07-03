#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "character.h"
#include "item.h"
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
    void moveBack() { emit dialogOut("sono fuggito"); }
    void dialog(QString s);
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
private:

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
    // funzioni test per vedere
    void scappa() {
        emit dialogOut("sto provando a scappare");
        // con una certa probabilita scappa
        if(randInt(0,1)) {
            moveBack();
            emit dialogOut("sono scappato");
        }
        else {
            emit dialogOut("non sei riuscito a scappare!");
            //startCombat();
        }
    }
    void usePotionMana();
    void usePotionHealth();
    void startCombat(Tile &t) {
        combat = new CombatState(t.e, nullptr);
        emit dialogOut("sei entrato nel pieno del combattimento");
        emit dialogOut("il tuo nemico ti sferra un fendente micidiale");
        // usare combat per tenere traccia dello stato del sistema
        combat->numero_turno++;
        combat->turno_player = true;
        emit dialogOut("cosa vuoi fare?");
        emit choiceOut(Choice::attack());
        //ememies.arma.use(player)
    }
    void attacca() {
        emit dialogOut("usi la tua arma pazzesca per sfonnare il nemico");
    }
    void endCombat() {
        delete combat;
        combat = nullptr;
    }
    int randInt(int low, int high);
    CombatState* combat;
    Character *pg;
    Map map;
    unsigned int score = 0;
};
#endif // GAME_H
