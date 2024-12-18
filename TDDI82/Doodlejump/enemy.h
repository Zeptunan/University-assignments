#ifndef ENEMY_H
#define ENEMY_H

#include "entity.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>

// Basklass för alla fiender
class Enemy : public Entity {
public:
  Enemy(float x, float y);
  Enemy(float x, float y, std::string id); // Lägg till denna rad
  virtual void draw(sf::RenderTarget& window) override;
  virtual void update() override = 0;  // Gör update ren virtuell
  sf::Rect<float> getGlobalBounds() override;
  sf::Rect<float> getPlatDetection() override;
  void setSprite(std::string) override;
  virtual void collision(Entity &ent) override = 0;
  
protected:
  float direction = 1;
  sf::Texture *enemyTexture;
};

// Existerande fiende som rör sig horisontellt
class HorizontalEnemy : public Enemy {
public:
  HorizontalEnemy(float x, float y);
  void update() override;
  void collision(Entity &ent) override;
};

// Fiende som fungerar som en plattform på ovansidan
class PlatformEnemy : public Enemy {
public:
  PlatformEnemy(float x, float y);
  void update() override;
  void collision(Entity &ent) override;
};

// Fiende som rör sig neråt och förstör plattformar
class FallingEnemy : public Enemy {
public:
  FallingEnemy(float x, float y);
  void update() override;
  void collision(Entity &ent) override;
};

#endif // ENEMY_H
