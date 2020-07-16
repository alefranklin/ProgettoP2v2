#include "randomizer.h"

#include <iostream>
#include <cstdlib>
#include <ctime>



using namespace std;

unsigned int Randomizer::seed = 1; //valore di default di srand


unsigned int Randomizer::setup() {
  setSeed(time(NULL));
  return getSeed();
}  //funzione pronta

unsigned int Randomizer::getSeed() { return seed; }  //funzione pronta
void Randomizer::setSeed(unsigned int s) { seed = s; srand(s); } //funzione pronta


int Randomizer::randomNumberBetween(int min, int max) {
    return min+(rand()%(max-min+1));
}


Item* Randomizer::getRandomItem()
{/*chiamare casualmente o randomWeapon o randonArmor o potion o altri item istanziabili*/
    int i = randomNumberBetween(1,4);

    switch (i) {
        case 1: return getRandomWeapon(); break;
        case 2: return getRandomPotionMana(); break;
        case 3: return getRandomPotionVita(); break;
        case 4: return getRandomArmor(); break;
        default: return getRandomPotionMana(); break;
    }
}

Weapon* Randomizer::getRandomWeapon()
{/*chiamare casualmente uno dei metodi sotto*/
    int i = randomNumberBetween(1,3);

    switch (i) {
        case 1: return getRandomBow(); break;
        case 2: return getRandomSword(); break;
        case 3: return getRandomMagicWeapon(); break;
        default: return getRandomSword(); break;
    }
}

//TODO randomizzare i nomi

MagicWeapon* Randomizer::getRandomMagicWeapon()
{
    return new MagicWeapon("Bastone della morte", randomNumberBetween(2,9), randomNumberBetween(2,8), randomNumberBetween(2,5));
}

Bow* Randomizer::getRandomBow()
{
    ScrapedInfo s = getRandomImgBow();
    return new Bow(s.name, s.file, randomNumberBetween(2,8), randomNumberBetween(2,8));
}

Sword* Randomizer::getRandomSword()
{
    return new Sword("Spada di legno", randomNumberBetween(2,8), 1);
}

Armor* Randomizer::getRandomArmor()
{
    return new Armor("Armatura", randomNumberBetween(2,7));
}

Potion* Randomizer::getRandomPotionMana()
{
    return new Potion("Pozione", randomNumberBetween(10,20), randomNumberBetween(0,1), true);
}

Potion* Randomizer::getRandomPotionVita()
{
    return new Potion("Pozione", randomNumberBetween(10,20), true, randomNumberBetween(0,1));
}

//static Armor* getRandomArmor(int livello);

Mob* Randomizer::getRandomMob()
{
    return new Mob(getRandomMobName(), randomNumberBetween(10,20), randomNumberBetween(7,15));
}

//TODO mettere nomi random
string Randomizer::getRandomMobName() {
    std::vector<std::string> nomi;


    nomi.push_back("Gatha");
    nomi.push_back("Rodphia");
    nomi.push_back("Godra");
    nomi.push_back("Daelin");
    nomi.push_back("Lin");
    nomi.push_back("Erilmar");
    nomi.push_back("Mae");
    nomi.push_back("Thelmí");
    nomi.push_back("Thornda");
    nomi.push_back("Thornpa");
    nomi.push_back("Ieleres");
    nomi.push_back("Ne");
    nomi.push_back("Tarlin");
    nomi.push_back("Casael");
    nomi.push_back("Halaz");
    nomi.push_back("Oniborn");
    nomi.push_back("Mardel");
    nomi.push_back("Azhal");
    nomi.push_back("Thila");
    nomi.push_back("Thidír");

    return nomi[randomNumberBetween(0, nomi.size()-1)];
}

Randomizer::ScrapedInfo Randomizer::getRandomImgBow()
{
    vector<ScrapedInfo> v;

    v.push_back(ScrapedInfo("Arco per principianti", 15, ":/archi/Arc15.png"));
    v.push_back(ScrapedInfo("Arco piccolo", 20, ":/archi/Arc20.png"));
    v.push_back(ScrapedInfo("Arco della vita", 21, ":/archi/Arc21.png"));
    v.push_back(ScrapedInfo("Arco della velocità", 26, ":/archi/Arc26.png"));
    v.push_back(ScrapedInfo("Arco di bambù", 29, ":/archi/Arc29.png"));
    v.push_back(ScrapedInfo("Arco Fiamma", 30, ":/archi/Arc30.png"));
    v.push_back(ScrapedInfo("Arco magico", 34, ":/archi/Arc34.png"));
    v.push_back(ScrapedInfo("Arco di legno di quercia", 36, ":/archi/Arc36.png"));
    v.push_back(ScrapedInfo("Arco sintetico", 37, ":/archi/Arc37.png"));
    v.push_back(ScrapedInfo("Arco del vento", 40, ":/archi/Arc40.png"));
    v.push_back(ScrapedInfo("Arco di corno", 42, ":/archi/Arc42.png"));
    v.push_back(ScrapedInfo("Arco doppio", 43, ":/archi/Arc43.png"));
    v.push_back(ScrapedInfo("Arco rosso", 45, ":/archi/Arc45.png"));
    v.push_back(ScrapedInfo("Arco con impugnatura in pelle", 46, ":/archi/Arc46.png"));
    v.push_back(ScrapedInfo("Arco da caccia", 48, ":/archi/Arc48.png"));
    v.push_back(ScrapedInfo("Arco Feroce", 49, ":/archi/Arc49.png"));
    v.push_back(ScrapedInfo("Arco del coraggio", 52, ":/archi/Arc52.png"));
    v.push_back(ScrapedInfo("Arco lungo", 53, ":/archi/Arc53.png"));
    v.push_back(ScrapedInfo("Arco grande", 54, ":/archi/Arc54.png"));
    v.push_back(ScrapedInfo("Arco di bronzo", 57, ":/archi/Arc57.png"));
    v.push_back(ScrapedInfo("Arco dello spirito", 60, ":/archi/Arc60.png"));
    v.push_back(ScrapedInfo("Arco d'assedio", 63, ":/archi/Arc63.png"));
    v.push_back(ScrapedInfo("Arco della pace", 65, ":/archi/Arc65-68.png"));
    v.push_back(ScrapedInfo("Arco della foresta", 68, ":/archi/Arc65-68.png"));
    v.push_back(ScrapedInfo("Arco della potenza", 70, ":/archi/Arc70-73.png"));
    v.push_back(ScrapedInfo("Seraphion", 71, ":/archi/Arc71.png"));
    v.push_back(ScrapedInfo("Arco Darkangelus", 73, ":/archi/Arc70-73.png"));
    v.push_back(ScrapedInfo("Arco maestoso", 75, ":/archi/Arc75.png"));
    v.push_back(ScrapedInfo("Caiperu", 79, ":/archi/Arc79.png"));
    v.push_back(ScrapedInfo("Onorevole: Arco Alta marea di Calvina", 82, ":/archi/Arc45.png"));
    v.push_back(ScrapedInfo("Arco dei Banditi del Deserto", 83, ":/archi/Arc83-85.png"));
    v.push_back(ScrapedInfo("Arco elementale", 85, ":/archi/Arc83-85.png"));
    v.push_back(ScrapedInfo("Arco della distruzione", 88, ":/archi/Arc88.png"));
    v.push_back(ScrapedInfo("Arco degli abissi di Hatus", 88, ":/archi/Arc88.png"));
    v.push_back(ScrapedInfo("Arco Alta marea di Calvinas", 88, ":/archi/Arc88.png"));
    v.push_back(ScrapedInfo("Onorevole: arco a cuneo del Grande Comandante", 88, ":/archi/Arc83-85.png"));
    v.push_back(ScrapedInfo("Arco a cuneo del Grande leader", 90, ":/archi/Arc90.png"));
    v.push_back(ScrapedInfo("Arco dell'eroe obliato (+10)", 90, ":/archi/Arc90+10.png"));
    v.push_back(ScrapedInfo("Ala della fenice", 92, ":/archi/Arc92.png"));
    v.push_back(ScrapedInfo("Ala di Gral", 95, ":/archi/Arc95.png"));
    v.push_back(ScrapedInfo("Arco Inferno sigillato", 25, ":/archi/ArcoInfernoSigillato.png"));
    v.push_back(ScrapedInfo("Arco Paradiso sigillato", 25, ":/archi/ArcoParadisoSigillato.png"));
    v.push_back(ScrapedInfo("Ali di Azrael", 45, ":/archi/AliDiAzrael.png"));
    v.push_back(ScrapedInfo("Arco del Loa aquila", 55, ":/archi/ArcoDelLoaAquila.png"));

    return v[randomNumberBetween(0, v.size()-1)];
}
