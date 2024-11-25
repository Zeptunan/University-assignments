#include "ghost.h"

#include <cmath>
#include <string>

// Komplettering: Ghost tar fortfarande emot en parameter som endast hör till en av de härledda klasserna.
// Komplettering: Initiera variabler med måsvingar.
// Komplettering: Alla datamedlemmar ska initieras i datamedlemsinitieringslistan.

// Checkar om positionen är korrekt
void validate_position(Point const& p) {
  if (p.x > WIDTH or p.x < 0 || p.y > HEIGHT || p.y < 0) {
    throw std::runtime_error("position outside valid range");
  }
}

// Konstruktor för myEntity
myEntity::myEntity(const Point& position) : pos{position} {
  validate_position(position);
}

// Returnerar positionen för entiteten
Point myEntity::get_position() const { return pos; }

// Sätter positionen för entiteten
void myEntity::set_position(Point const& p) {
  validate_position(p);
  
  pos = p;
  
  // Se kommentar i main.cc
  if (p.x == WIDTH) {
    pos.x = WIDTH - 1;
  }
  
  if (p.y == HEIGHT) {
    pos.y = HEIGHT - 1;
  }
}

Ghost::Ghost(const std::string& color, const Point& position,
             const Point& scatterPoint)
  : myEntity{position}, scatterPoint{scatterPoint}, color{color} {}

std::string Ghost::get_color() const { return color; }

Point Ghost::get_scatter_point() const { return scatterPoint; }

void Ghost::set_scatter_point(Point const& p) { scatterPoint = p; }

// BLINKY
Blinky::Blinky(Pacman& pacman, const Point& position, const Point& scatterPoint)
  : Ghost{"red", position, scatterPoint}, pacman{pacman}, angry{false} {}

// Blinkys scatter
Point Blinky::get_scatter_point() const {
  if (angry) {
    return get_chase_point();
  } else {
    return scatterPoint;
  }
}
// Blinky jagar pacmans position direkt
Point Blinky::get_chase_point() const { return pacman.get_position(); }

bool Blinky::is_angry() const { return angry; }

void Blinky::set_angry(bool angryParam) { angry = angryParam; }

// PINKY
//  Pinky jagar en punkt 2 steg framför pacman
Pinky::Pinky(Pacman& pacman, const Point& position, const Point& scatterPoint)
  : Ghost{"pink", position, scatterPoint}, pacman{pacman} {}

Point Pinky::get_chase_point() const {
  Point pacmanPos{pacman.get_position()};
  Point pacmanDir{pacman.get_direction()};
  return Point{pacmanPos.x + 2 * pacmanDir.x, pacmanPos.y + 2 * pacmanDir.y};
}

// CLYDE
Clyde::Clyde(Pacman& pacman, const Point& position, const Point& scatterPoint, int specialParam)
  : Ghost{"orange", position, scatterPoint}, pacman{pacman}, specialParameter{specialParam} {}

// Clyde jagar pacman om avståndet är större än n, annars går han till sin
// scatter point
Point Clyde::get_chase_point() const {
  Point pacmanPos{pacman.get_position()};
  // Distance formlua: sqrt((x2 - x1)^2 + (y2 - y1)^2)
  // sqrt returnerar double, så vi avrundar värdet nedan i if-satsen
  double distance{sqrt(pow(pacmanPos.x - get_position().x, 2) +
		       pow(pacmanPos.y - get_position().y, 2))};
  
  if (std::round(distance) < specialParameter) {
    return get_scatter_point();
  } else {
    return pacmanPos;
  }
}

// INKY
Inky::Inky(Pacman& pacman, const Point& position, const Point& scatterPoint,
           Ghost& blinky)
  : Ghost{"cyan", position, scatterPoint}, pacman{pacman}, blinky{blinky} {}

Point Inky::get_chase_point() const {
  Point pacmanPos{pacman.get_position()};
  Point blinkyPos{blinky.get_position()};
  Point pacmanDir{pacman.get_direction()};
  Point twoStepsAhead{pacmanPos.x + 2 * pacmanDir.x,
		      pacmanPos.y + 2 * pacmanDir.y};
  
  Point inkyTarget{2 * (twoStepsAhead.x - blinkyPos.x),
		   2 * (twoStepsAhead.y - blinkyPos.y)};
  return inkyTarget;
}
