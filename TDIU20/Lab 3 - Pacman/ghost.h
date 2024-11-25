#ifndef GHOST_H
#define GHOST_H

#include <string>

#include "given.h"

/*
 * OBS: vi har en egen entity class,
 * den konflikterar med full_game,
 * så entity klassen är inkluderad i denna fil istället
 * och i ghost.cc
#include "custom_entity.h"
 */

// Information om komplettering:
//   Kompletteringen kan gälla hela filen och alla filer i labben,
//   så får ni komplettering på en sak, kan samma sak förekomma på
//   fler ställen utan att jag skrivit det.
//
//   Komplettering lämnas in via sendlab efter senast en (1) vecka.
//
//   Har ni frågor om kompletteringen kan ni maila mig på:
//   love.arreborn@liu.se

class myEntity {
public:
  myEntity(const Point& position);
  Point get_position() const;
  void set_position(Point const& p);
  virtual ~myEntity() = default;
  
private:
  Point pos{};
};

class Ghost : public myEntity {
public:
  Ghost(const std::string& color, const Point& position,
	const Point& scatterPoint);
  
  virtual ~Ghost() = default;

  std::string get_color() const;
  
  virtual Point get_scatter_point() const;
  void set_scatter_point(Point const& p);
  
  virtual Point get_chase_point() const = 0;
  
protected:
  Point scatterPoint;
  
private:
  std::string color;
};

class Blinky : public Ghost {
public:
  Blinky(Pacman& pacman, const Point& position, const Point& scatterPoint);
  Point get_scatter_point() const override;
  Point get_chase_point() const override;
  bool is_angry() const;
  void set_angry(bool angry);
  
private:
  Pacman& pacman;
  bool angry {false};  // Om Blinky är arg
};

class Pinky : public Ghost {
public:
  Pinky(Pacman& pacman, const Point& position, const Point& scatterPoint);
  Point get_chase_point() const override;
  
private:
  Pacman& pacman;
};

class Clyde : public Ghost {
public:
  Clyde(Pacman& pacman, const Point& position, const Point& scatterPoint,
	int specialParam);
  Point get_chase_point() const override;
  
private:
  Pacman& pacman;
  int specialParameter;
};

class Inky : public Ghost {
public:
  Inky(Pacman& pacman, const Point& position, const Point& scatterPoint,
       Ghost& blinky);
  Point get_chase_point() const override;
  
private:
  Pacman& pacman;
  Ghost& blinky;
};

#endif  // GHOST_H
