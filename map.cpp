#include <cmath>
#include <set>
#include <QDebug>

#include "map.h"
#include "randomizer.h"

//#include "colors.h"

using namespace std;

int Map::minDim = 80;

ostream& operator<<(ostream& out, const Coordinate &c) {
  out << "(" << c.row << "," << c.col << ")";
  return out;
}


Map::Map(int d): pos() {
  //la mappa deve avere una dimensione minima
  dim = (d < minDim) ? minDim : d;

  qDebug() << "dim:" << dim << endl; //debug

  // instanzio i vettori della mappa
  map = QVector<QVector<Tile>>(dim, QVector<Tile>(dim, Tile()));

  Generatemap();

  // costruisco la mappa
  //  -> creo spazi aperti
  //  -> creo corridoi
  //  -> posiziono oggetti e mob in maniera random

  // aggiorno la posizione iniziale
  changePos(RandomPos());

}

// ritorna true se la posizione è stata settata
// fasle altrimenti
bool Map::setPos(Coordinate newPos) {
  //if(isWalkable(newPos)) {
    changePos(newPos);
    return true;
  //} else return false;

  // TODO decommentare quando finito il dev // debug
}

Coordinate Map::getPos() const {
  return pos;
}

Coordinate Map::getRelativePos() const {
  return relativePos;
}

QVector<QVector<Tile> > Map::getMiniMap(int size) {

  // controllo se ho una grandezza sufficiente a creare una minimappa
  // in caso contrario ritorno tutta la mappa

  if (size >= dim) {
    changeRelativePos(pos);
    return map;
  }

  // a questo punto  sono certo che la mappa sia più grande della minimappa
  // quindi posso avere overflow solo su uno dei due lati non su entrambi

  QVector<QVector<Tile>> miniMap(size, QVector<Tile>(size, Tile(false)));

  int overflow_row = 0;
  int overflow_col = 0;
  int half_size = size/2;


  // calcolo overflow row
  if(pos.row + half_size > dim-1) overflow_row = (pos.row + half_size) - (dim-1);
  if(pos.row - half_size < 0) overflow_row = pos.row - half_size;


  //calcolo overflow col
  if(pos.col + half_size > dim-1) overflow_col = (pos.col + half_size) - (dim-1);
  if(pos.col - half_size < 0) overflow_col = pos.col - half_size;

  for(int row = 0; row < size; row++)
    for(int col = 0; col < size; col++) {
      // clacolo la posizione relativa alla mappa grande
      int map_row = pos.row - half_size + row - overflow_row; /*size=11 h_size=5 ov_row=1 ov_col=1 map_row=79 map_col=79*/
      int map_col = pos.col - half_size + col - overflow_col;

      miniMap[row][col] = map[ map_row ][ map_col ];

      // trovo la posizione relativa
      if(pos.row == map_row && pos.col == map_col)
        changeRelativePos(Coordinate(row, col));
    }

  return miniMap;
}


Coordinate Map::RandomPos() const {
  // vettore contenente le /possibili posizioni
  // in cui è possibile spawnare sulla mappa
  QVector<Coordinate> possiblePos;

  // trovo tutte le possibili posizioni
  for(int row = 0; row < dim; row++){
    for(int col = 0; col < dim; col++){
      if(map[row][col].walkable == true){
        possiblePos.push_back(Coordinate(row,col));
      }
    }
  }
  // ne scelgo una a caso
  if(possiblePos.size()) {
     int selected = Randomizer::randomNumberBetween(0, possiblePos.size()-1);
    return possiblePos[selected];
  }
  return Coordinate();   //da fixare
}

// cambio la posizione e aggiorno la visibilità
void Map::changePos(Coordinate newPos) {
  pos = newPos;
}

void Map::changeRelativePos(Coordinate newRelativePos) {
  relativePos = newRelativePos;
}
//alessandro merda

// nelle funzioni move isValid() è ridondante in quanto utilizzata anche in isWalkable(),
// per chiarezza l'abbiamo utilizzata lo stesso nel controllo

void Map::moveUP() {
  Coordinate newPos(pos.row-1, pos.col);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

void Map::moveDOWN() {
  Coordinate newPos(pos.row+1, pos.col);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

void Map::moveLEFT() {
  Coordinate newPos(pos.row, pos.col-1);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

void Map::moveRIGHT() {
  Coordinate newPos(pos.row, pos.col+1);
  if(isValid(newPos) && isWalkable(newPos)) changePos(newPos);
}

// restituisce la tile corrent in modo da poter controllare esternamente cosa contiene
// non è const perche Tile potrebbe essere modificato esternamente e a cascata anche getTileIn() non può essere const
Tile& Map::getCurrentTile() {
  return getTileIn(pos);
}

// richiede una posizione valida
Tile& Map::getTileIn(Coordinate p) {
  return map[p.row][p.col];
}

bool Map::isWalkable(Coordinate p) {
  return (isValid(p)) ? getTileIn(p).walkable : false;
}

bool Map::isValid(Coordinate p) const {
  return (p.row < 0 || p.row >= dim || p.col < 0 || p.col >= dim ) ? false : true;
}

QVector<Coordinate> Map::createCircle(Coordinate center, int radius) {
  /* controllo tutte le posizioni in una regione grande radius^2 x radius^2 con centro in center
     e controllo se fanno parte dell'area utilizzando la formula del cerchio */
  QVector<Coordinate> points;

  // il raggio deve essere >= 0
  radius = (radius < 0) ? radius*(-1) : radius;

  // itero nell'area da controllare
  for(int i = center.row - radius; i <= center.row + radius; i++) {
    for(int j = center.col - radius; j <= center.col + radius; j++) {

      // utilizzo l'equazione del cerchio
      if((i-center.row)*(i-center.row) + (j-center.col)*(j-center.col) <= radius*radius) {
        // se valida aggiungo la posizione alla lista dei punti selezionati
        Coordinate p(i,j);
        if(isValid(p)) points.push_back(p);
      }

    }
  }
  return points;
}

QVector<Coordinate> Map::createRectangle(Coordinate center, int width, int height) {
  QVector<Coordinate> points;

  // itero nell'area da controllare
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {

      int row = center.row - (height/2) + i;
      int col = center.col - (width/2) + j;

      // se valida aggiongo la posizione alla lista di punti selezionati
      Coordinate p(row,col);
      if(isValid(p)) points.push_back(p);
    }
  }
  return points;
}

QVector<Coordinate> Map::createLine(Coordinate p1, Coordinate p2, int thickness) {
  QVector<Coordinate> line;

  /*
  if(p1 > p2){
    Coordinate temp = p1;
    p1 = p2;
    p2 = temp;
  }
  */

  // utilizziamo l'algoritmo di bresenham per calcolare la linea

  int dx = p2.row - p1.row;
  int ix((dx > 0) - (dx < 0));
  dx = abs(dx) << 1;

  int dy = p2.col - p1.col;
  int iy((dy > 0) - (dy < 0));
  dy = abs(dy) << 1;

  line.push_back(p1);

  if (dx >= dy) {
    // error may go below zero
    int error(dy - (dx >> 1));

    while (p1.row != p2.row)
    {
      if ((error >= 0) && (error || (ix > 0))) {
          error -= dx;
          p1.col += iy;
      }
      // else do nothing

      error += dy;
      p1.row += ix;

      line.push_back(p1);
    }
  } else {
    // error may go below zero
    int error(dx - (dy >> 1));

    while (p1.col != p2.col){
      if ((error >= 0) && (error || (iy > 0))) {
          error -= dy;
          p1.row += ix;
      }
      // else do nothing

      error += dx;
      p1.col += iy;

      line.push_back(p1);
    }
  }


  // thickness deve essere >= 2
  if(thickness <= 1) thickness = 2;

  //ingrosso la linea
  QVector<Coordinate> points;
  for(auto it = line.begin(); it != line.end(); ++it) {
    // creo un quadrato di dimensione thicknessxthickness intorno ad ogni punto della linea
    QVector<Coordinate> v = createRectangle(*it, thickness, thickness);
    //points.insert(points.end(), v.begin(), v.end());
    for(auto it = v.begin(); it != v.end(); ++it){ points << *it; }
  }

  // elimino tutti i punti duplicati
  set<Coordinate> s( points.begin(), points.end() );
  //points.assign( s.begin(), s.end() );
  points.erase(points.begin(), points.end());
  for(auto it = s.begin(); it != s.end(); ++it){ points << *it; }
  return points;

}

void Map::modifyTile(QVector<Coordinate> points, bool w, Biome b, bool overwrite) {
  for(auto it = points.begin(); it != points.end(); ++it) {
    if(isValid(*it)) {
      Tile &t = getTileIn(*it);
      // sovrawscrivo sempre se overWrite a true
      // altrimenti solo se il bioma è Null
      if(overwrite || t.biome == Null) {
        t.walkable = w;
        t.biome = b;
      }
    }
  }
}

/* calcolo la percentuale di spawn in base al Bioma */
float Map::calcSpawnRate(const Tile& t) const {
  //se non ci posso andare laprobabilità di spawn è 0
  if(t.walkable == false) return 0.0;

  float rate = 0.1;
  switch (t.biome)
  {
    case Valley:    rate = 0.1;  break;
    case Desert:    rate = 0.2;  break;
    case Doungeon:  rate = 0.4;  break;
    case Street:    rate = 0.05; break;
    default:        rate = 0.1;  break;
  }
  return rate;
}

void Map::generateOasi(Coordinate center, int minDim, int maxDim, bool overwrite) {
  QVector<Coordinate> oasi;

  // scelgo la forma
  if( Randomizer::randomNumberBetween(0,100) <= 50 ) {

    int radius = Randomizer::randomNumberBetween(minDim/2, maxDim/2);
    oasi = createCircle(center, radius);

  } else {

    int w = Randomizer::randomNumberBetween(minDim, maxDim);
    int h = Randomizer::randomNumberBetween(minDim, maxDim);
    oasi = createRectangle(center, w, h);

  }
  // aggiungo l'oasi
  modifyTile(oasi, true, Valley, overwrite);

  // aggiungo l'acqua
  modifyTile(QVector<Coordinate>(1, center), false, Water, overwrite);

}

void Map::generateDesert(Coordinate center, int minDim, int maxDim, int maxOasis, bool overwrite) {
  QVector<Coordinate> desert;
  bool oasis = true;
  // scelgo la forma
  if( Randomizer::randomNumberBetween(0,100) <= 50 ) {

    int radius = Randomizer::randomNumberBetween(minDim, maxDim);
    desert = createCircle(center, radius);
    if(radius <= 10 ) oasis = false;

  } else {

    int w = Randomizer::randomNumberBetween(minDim, maxDim);
    int h = Randomizer::randomNumberBetween(minDim, maxDim);
    desert = createRectangle(center, w, h);
    if(w*h <= 400) oasis = false;

  }

  // aggiungo il deserto
  modifyTile(desert, true, Desert, overwrite);

  if(oasis) {
    // aggiungo le oasi
    for(int i = 0; i < Randomizer::randomNumberBetween(0, maxOasis); i++) {
      Coordinate oasi = desert[ Randomizer::randomNumberBetween(0, desert.size()-1) ];
      generateOasi(oasi, 2, 5, true);
    }
  }
}


void Map::generateLake(Coordinate center, int minDim, int maxDim, bool overwrite) {
  QVector<Coordinate> lake;

  int radius = Randomizer::randomNumberBetween(minDim/2, maxDim/2);
  lake = createCircle(center, radius);

  // aggiungo lago
  modifyTile(lake, false, Water, overwrite);

}

/**
 * @brief
 *
 * @param
 * @return
 */
void Map::generateValley(Coordinate center, int minDim, int maxDim, int maxLakes, bool overwrite) {
  QVector<Coordinate> valley;
  bool lake = true;
  // scelgo la forma
  if( Randomizer::randomNumberBetween(0,100) <= 50 ) {

    int radius = Randomizer::randomNumberBetween(minDim, maxDim);
    valley = createCircle(center, radius);
    if(radius <= 10 ) lake = false;

  } else {
    int w = Randomizer::randomNumberBetween(minDim, maxDim);
    int h = Randomizer::randomNumberBetween(minDim, maxDim);
    valley = createRectangle(center, w, h);
    if(w*h <= 400) lake = false;

  }

  // aggiungo valle
  modifyTile(valley, true, Valley, overwrite);

  if(lake){
    // aggiungo laghi
    for(int i = 0; i < Randomizer::randomNumberBetween(0, maxLakes); i++) {
      Coordinate lake = valley[ Randomizer::randomNumberBetween(0, valley.size()-1) ];
      generateLake(lake, 3, 6, true);
    }
  }
}

/**
 * @brief ritorna una coordinata casuale della mappa in cui è presente il bioma b
 *
 * @param Biome b: bioma da ricercare
 * @return Coordinate
 */
Coordinate Map::getRandomPos(Biome b){
  QVector<Coordinate> v;
  for(int r = 0; r < dim; r++) {
    for(int c = 0; c < dim; c++) {
      Coordinate p(r,c);
      if(getTileIn(p).biome == b) v.push_back(p);
    }
  }

  return v[ Randomizer::randomNumberBetween(0, v.size()-1) ];

}


/**
 * chiama combinazioni casuali di forme geometriche
 * che si differenziano per biomi
 *
 * le linee collegano i centri di generazione di ogni forma geomtrica
 * e rappresentano
 *
 * si possono fare vallate
 * deserti giganti con oasi in mezzo
 *
 * magari prevedere un modo di generare acqua o lava rendendo decidibile anche il walkable oltre al bioma
 */
void Map::Generatemap() {

  QVector<Coordinate> centers;

  int maxNumPerBioma = 5;
  Coordinate center;

  //generate [1..maxNumPerBioma] desert
  for(int i = 0; i < Randomizer::randomNumberBetween(1, maxNumPerBioma); ++i){
    center = getRandomPos(Null);
    centers.push_back(center);
    generateDesert(center, 15, 25, 4, true);
  }

  //generate [1..maxNumPerBioma] valley
  for(int i = 0; i < Randomizer::randomNumberBetween(1, maxNumPerBioma); ++i){
    center = getRandomPos(Null);
    centers.push_back(center);
    generateValley(center, 15, 25, 4, true);
  }

  // creo le strade di collegamento tra i centri dei vari biomi
  for(int i = 0; i < centers.size()-1; i++) {
    QVector<Coordinate> line = createLine(centers[i], centers[i+1], 2);
    modifyTile(createLine(centers[i], centers[i+1]), true, Street, true);
  }
  modifyTile(createLine(centers[0], centers[centers.size()-1]), true, Street, true);


  //modifyTile(createLine(Coordinate(40,40), Coordinate(79,20)), true, Street, true);  //debug
}
int Map::getMapDimension() const {
    return dim;
}
