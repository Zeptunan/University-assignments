#ifndef POWER_UP_H
#define POWER_UP_H

#include "entity.h"
#include <SFML/Graphics.hpp>
#include <string>

class Power_up : public Entity {
protected:
  sf::Texture Power_up_texture;
  Power_up(float x, float y, const std::string& textureFile);

public:
  void draw(sf::RenderTarget& window) override;
  sf::FloatRect getGlobalBounds() override;
  sf::FloatRect getPlatDetection() override;
  void setSprite(std::string newSprite) override;

  void update() override;
  //void collision(Entity& ent) override;
};

class Big_boost : public Power_up {
public:
  Big_boost(float x, float y);
  //void update() override;
  void collision(Entity& ent) override;
};

class Shield : public Power_up {
public:
  Shield(float x, float y);
  //void update() override;
  void collision(Entity& ent) override;
};

#endif // POWER_UP_H
