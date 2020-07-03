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
  void moveBack();
  Tile& getCurrentTile();

  QVector<Coordinate> createCircle(Coordinate center, int radius); // va messa su private
  QVector<Coordinate> createRectangle(Coordinate center, int width, int height); // va messa su private
  //QVector<Coordinate> createRand(Coordinate center, int width, int height); // va messa su private
  QVector<Coordinate> createLine(Coordinate start, Coordinate end, int thickness = 2); // va messa su private
  void modifyTile(QVector<Coordinate> points, bool w, Biome b, bool overwrite = false); // va messa su private
  void Generatemap(); // va messa su private

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
  Coordinate lastPos;
  Coordinate relativePos;

  Coordinate RandomPos() const;
  // cambio la posizione e aggiorno la visibilità
  void changePos(Coordinate newPos);
  void changeRelativePos(Coordinate newRelativePos);
  Tile& getTileIn(Coordinate p);
  bool isWalkable(Coordinate p);
  bool isValid(Coordinate p) const;
  float calcSpawnRate(const Tile& t) const;


  void generateOasi(Coordinate center, int minDim, int maxDim, bool overwrite = false);
  void generateDesert(Coordinate center, int minDim, int maxDim, int maxOasis, bool overwrite = false);
  void generateLake(Coordinate center, int minDim, int maxDim, bool overwrite = false);
  void generateValley(Coordinate center, int minDim, int maxDim, int maxLake, bool overwrite = false);

  Coordinate getRandomPos(Biome b);

};

#endif
