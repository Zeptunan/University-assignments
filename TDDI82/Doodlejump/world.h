#ifndef WORLD_H
#define WORLD_H

#include <SFML/Graphics.hpp>
#include "entity.h"
#include "player.h"
#include "platform.h"
#include "enemy.h"
#include "power_up.h"

#include <vector>
#include <memory>

class World 
{
public:
  World();
  void draw(sf::RenderTarget & target);
  void update();
  void testCollision();
  bool playerAlive();
 
    

  //bool fellOff();
  int score{0};
  
private:
  std::vector< std::unique_ptr<Entity> > entities;
  Player player;
  
  float playerAccel{0};
  float platformAccel{0};
  sf::Font score_font;
  sf::Text score_text;
  void updateScore();
  
  void createPlatforms();
  void destroyPlatforms();
  void moveEntities();
  void updateEntities();
  bool testPlayerCollision(Entity &ent);
  
};

#endif
//kodinnlämning
