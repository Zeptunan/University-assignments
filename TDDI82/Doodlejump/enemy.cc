#include "enemy.h"
#include <iostream>

// Basklass-implementation
Enemy::Enemy(float x, float y) 
  : Entity{"enemy", sf::Vector2f(x, y)} {
  enemyTexture = new sf::Texture;
  if (!enemyTexture->loadFromFile("resources/enemy.png")) {
    std::cerr << "Failed to load enemy texture" << std::endl;
  }
  sprite.setTexture(*enemyTexture);
}


Enemy::Enemy(float x, float y, std::string id)
  : Entity{id, sf::Vector2f(x, y)} {
  enemyTexture = new sf::Texture;
  if (!enemyTexture->loadFromFile("resources/enemy.png")) {
    std::cerr << "Failed to load enemy texture" << std::endl;
  }
  sprite.setTexture(*enemyTexture);
}

void Enemy::draw(sf::RenderTarget& window) {
    window.draw(sprite);
}

sf::Rect<float> Enemy::getGlobalBounds() {
    return sprite.getGlobalBounds();
}

sf::Rect<float> Enemy::getPlatDetection() {
    return sf::Rect<float>(0.0, 0.0, 0.0, 0.0);
}

void Enemy::setSprite(std::string newSprite) {}

// HorizontalEnemy Implementation
HorizontalEnemy::HorizontalEnemy(float x, float y) 
  : Enemy(x, y) {}

void HorizontalEnemy::update() {
    if (sprite.getPosition().x > 570) {
        direction = -1;
    }
    else if (sprite.getPosition().x < 0) {
        direction = 1;
    }
    sprite.move(direction, 0);
}

void HorizontalEnemy::collision(Entity &ent) {
  if (!ent.hasShield) {
    ent.isAlive = false;
    ent.setAccel(0);
  } else {
    sprite.setPosition(-100.0, 1000.0);
    this->isAlive = false;
    ent.hasShield = false;
  }
}

// PlatformEnemy Implementation
PlatformEnemy::PlatformEnemy(float x, float y)
  : Enemy(x, y) {}

void PlatformEnemy::update() {}

void PlatformEnemy::collision(Entity &ent) {
  sf::FloatRect enemyBounds = sprite.getGlobalBounds();
  sf::FloatRect entityBounds = ent.getGlobalBounds();
  
  if (entityBounds.top + entityBounds.height <= enemyBounds.top + 10) {
    ent.setPos(sf::Vector2f(ent.getPos().x, enemyBounds.top - entityBounds.height));
    ent.setAccel(-15);
    this->isAlive = false; 
  } else {
    if (!ent.hasShield) {
      ent.isAlive = false;
      ent.setAccel(0);
    } else {
      sprite.setPosition(-100.0, 1000.0);
      this->isAlive = false;
      ent.hasShield = false;
    }
  }
}

// FallingEnemy Implementation
FallingEnemy::FallingEnemy(float x, float y)
  : Enemy(x, y, "falling_enemy") {}

void FallingEnemy::update() {
    sprite.move(0, 1);  
    if (sprite.getPosition().y > 960) {
        isAlive = false;
    }
}

void FallingEnemy::collision(Entity &ent) {
  if (ent.getID() == "platform" || ent.getID() == "blue_platform" || ent.getID() == "red_platform") {
    ent.isAlive = false;
  } 
}
