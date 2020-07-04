#ifndef MAP_H
#define MAP_H

#include <QVector>
#include "entity.h"

#include <iostream>

enum Biome {Valley, Desert, Doungeon, Street, Water, Null};

struct Coordinate {
  int row;
  int col;
  Coordinate(int row=0, int col=0): row(row), col(col) {}

  // TODO gli operatori sono da testare (a parte <<)
  bool operator==(const Coordinate& p) const { return ((this->row == p.row) && (this->col == p.col)); }
  bool operator!=(const Coordinate& p) const { return !(*this == p); }
  bool operator<(const Coordinate& p) const {
    if(this->row < p.row) return true;
    if( (this->row == p.row) && (this->col < p.col) ) return true;
    return false;
  }
  bool operator>(const Coordinate& p) const { return !(*this < p || *this == p); }
  friend std::ostream& operator<<(std::ostream& out, const Coordinate &c);
};

struct Tile {
  bool walkable;
  Biome biome;
  QVector<Entity*> e;
  Tile(bool w = false, Biome b = Null, QVector<Entity*> en = QVector<Entity*>()): walkable(w), biome(b), e(en) {}
};

class Map {
public:
  Map(int d = 0);

  void moveUP();
  void moveDOWN();
  void moveLEFT();
  void moveRIGHT();
  Tile& getCurrentTile();
  QVector<Tile&> getWalkableTile(int range, Coordinate c) {

    // ritorna arrai coordinate valide
    QVector<Coordinate> circle = createCircle(c, range);

    // filtro e tengo solo quelle camminabili
    for (auto it = circle.begin(); it != circle.end(); ++it)
    {
      if( isWalkable(*it) ) {
        it = circle.erase(it);
        --it;
      }
    }

    // creo vettore tile
    QVector<Tile&> t;
    for (auto it = circle.begin(); it != circle.end(); ++it)
    {
      t.push_back(getTileIn(*it) );
    }

    return t;
    
  }


  int getMapDimension() const;
  bool setPos(Coordinate newPos);
  Coordinate getPos() const;
  Coordinate getRelativePos() const;

  QVector<QVector<Tile> > getMiniMap(int size);

  static void printMap(QVector<QVector<Tile>> m, Coordinate pos);
//qui giace la funzione pronta

private:
  static int minDim;
  int dim;
  QVector<QVector<Tile>> map;
  Coordinate pos;
  Coordinate relativePos;

  Coordinate RandomPos() const;
  // cambio la posizione e aggiorno la visibilità
  void changePos(Coordinate newPos);
  void changeRelativePos(Coordinate newRelativePos);
  bool isWalkable(Coordinate p);
  bool isValid(Coordinate p) const;
  Tile& getTileIn(Coordinate p);
  float calcSpawnRate(const Tile& t) const;

  QVector<Coordinate> createCircle(Coordinate center, int radius);
  QVector<Coordinate> createRectangle(Coordinate center, int width, int height);
  QVector<Coordinate> createLine(Coordinate start, Coordinate end, int thickness = 2);
  void modifyTile(QVector<Coordinate> points, bool w, Biome b, bool overwrite = false);
  void Generatemap();


  void generateOasi(Coordinate center, int minDim, int maxDim, bool overwrite = false);
  void generateDesert(Coordinate center, int minDim, int maxDim, int maxOasis, bool overwrite = false);
  void generateLake(Coordinate center, int minDim, int maxDim, bool overwrite = false);
  void generateValley(Coordinate center, int minDim, int maxDim, int maxLake, bool overwrite = false);

  Coordinate getRandomPos(Biome b);

};

#endif
