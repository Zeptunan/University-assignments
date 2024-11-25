#include "platform.h"
#include "entity.h"
#include <SFML/Graphics.hpp>

Platform::Platform( float x, float y) 
 : Platform( sf::Vector2f(x, y))
{ }

Platform::Platform(sf::Vector2f pos)
 : Entity{"platform", pos}
{ 
    pTexture = new sf::Texture;
    std::string texture = "resources/platform_green.png";
    pTexture->loadFromFile(texture);
    sprite.setTexture(*pTexture);
}

void Platform::draw (sf::RenderTarget & rTarget) 
{
    rTarget.draw(sprite);
}


void Platform::update() {

}

void Platform::setSprite(std::string newSprite) {

}

void Platform::collision(Entity & ent) {
  if (ent.getPlatDetection().intersects(sprite.getGlobalBounds()) and ent.getAccel() > 0)
    {
      ent.setAccel(-11);
    }
}

sf::Rect<float> Platform::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

sf::Rect<float> Platform::getPlatDetection() {
    return sf::Rect<float>(0.0, 0.0, 0.0, 0.0);
}

Red_Platform::Red_Platform( float x, float y) 
 : Red_Platform( sf::Vector2f(x, y))
{ }

Red_Platform::Red_Platform(sf::Vector2f pos)
 : Platform{pos}
{ 
    pTexture = new sf::Texture;
    std::string texture = "resources/platform_red.png";
    pTexture->loadFromFile(texture);
    sprite.setTexture(*pTexture);
}

void Red_Platform::collision(Entity & ent) {
    pTexture->loadFromFile("resources/platform_red_broken.png");
    sprite.setTexture(*pTexture);
    ent.setAccel(0);
}

// void Platform::setSprite(std::string newSprite) {
//     pTexture->loadFromFile(newSprite);
//     sprite.setTexture(*pTexture);
// }



Blue_Platform::Blue_Platform( float x, float y) 
 : Blue_Platform( sf::Vector2f(x, y))
{ }

Blue_Platform::Blue_Platform(sf::Vector2f pos)
 : Platform{pos}
{ 
    pTexture = new sf::Texture;
    std::string texture = "resources/platform_blue.png";
    pTexture->loadFromFile(texture);
    sprite.setTexture(*pTexture);
}

void Blue_Platform::update() 
{
    if (sprite.getPosition().x >= 570) {
        direction = -1;
    }
    else if (sprite.getPosition().x < 0) {
        direction = 1;
    }
    sprite.move(direction, 0); 
}
