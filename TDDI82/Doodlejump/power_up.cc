#include "power_up.h"
#include <iostream>


Power_up::Power_up(float x, float y, const std::string& textureFile) 
  : Entity{"Power_up", sf::Vector2f(x, y)} 
{
  if (!Power_up_texture.loadFromFile(textureFile)) {
    std::cerr << "Failed to load Power_up texture from " << textureFile << std::endl;
  }
  sprite.setTexture(Power_up_texture);
  sprite.setPosition(x, y); 
  sprite.setScale(2, 2);
}

void Power_up::draw(sf::RenderTarget& window) {
  window.draw(sprite);
}

sf::FloatRect Power_up::getGlobalBounds() {
  return sprite.getGlobalBounds();
}

sf::FloatRect Power_up::getPlatDetection() {
  
  return sf::FloatRect(0.0f, 0.0f, 0.0f, 0.0f);
}

void Power_up::setSprite(std::string newSprite) {
  if (!Power_up_texture.loadFromFile(newSprite)) {
    std::cerr << "Failed to load new texture from " << newSprite << std::endl;
  }
  sprite.setTexture(Power_up_texture);
}

void Power_up::update() {

}

Big_boost::Big_boost(float x, float y)
  : Power_up(x, y, "resources/PU_BB.png") {}

void Big_boost::collision(Entity& ent) {
  ent.setAccel(-19); 
}


Shield::Shield(float x, float y)
  : Power_up(x, y, "resources/PU_Shield.png") {}

void Shield::collision(Entity& ent) {
  ent.hasShield=true; 
}

