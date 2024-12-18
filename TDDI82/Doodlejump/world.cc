#include "world.h"

#include <random>
#include <algorithm>
#include <iostream>

World::World() 
    : entities{}, player(640/2, 960/2)
{
    entities.push_back(std::make_unique<Platform>(300, 800));
    entities.push_back(std::make_unique<Blue_Platform>(100, 600));
    entities.push_back(std::make_unique<Platform>(100, 400));
    entities.push_back(std::make_unique<Platform>(200, 500));
    entities.push_back(std::make_unique<Platform>(400, 100));

    if (!score_font.loadFromFile("resources/comic_sans.ttf")) {
        std::cout << "Score load failed" << std::endl;
        system("pause");
    }
    score_text.setFont(score_font);
    score_text.setCharacterSize(24);
    score_text.setPosition(0, 0);
    score_text.setFillColor(sf::Color::Black);
}

void World::draw(sf::RenderTarget &target)
{
    for ( auto &ent : entities)
    {
        ent->draw(target);
    }
    player.draw(target);
    target.draw(score_text);
}

void World::update()
{
    createPlatforms();
    destroyPlatforms();
    player.update();
    moveEntities();
    updateEntities();
    updateScore();
}

void World::testCollision() {
  for (auto &ent : entities) {
   
    if (testPlayerCollision(*ent)) {
      player.setAccel(playerAccel);
      player.collision(*ent);
      ent->collision(player);
      
      if (player.getAccel() != 0) {
	playerAccel = player.getAccel();
      }
    }
    
   
    if (ent->getID() == "falling_enemy") {
      for (auto &other : entities) {
	if (other->getID() == "platform" || other->getID() == "blue_platform" || other->getID() == "red_platform") {
	  if (ent->getGlobalBounds().intersects(other->getGlobalBounds())) {
	    ent->collision(*other);
	    other->collision(*ent);
	  }
	}
      }
    }
  }
}



bool World::playerAlive()
{
    return player.isAlive;
}

void World::createPlatforms()
{
  int plat_dist{80};
  
  std::random_device rng;
  std::mt19937 gen{rng()};
  std::uniform_int_distribution<int> xDis(1, 640-100);
  std::uniform_int_distribution<int> type(1, 100);
  
  if (entities.empty() || entities.back()->getPos().y > plat_dist)
    {
      int rnd_x = xDis(gen);
      int pType = type(gen);
      
      if (pType < 55) {
	entities.push_back(std::make_unique<Platform>(rnd_x, 0));
      } else if (pType < 80 && pType >= 55) {
	entities.push_back(std::make_unique<Blue_Platform>(rnd_x, 0));
      } else if (pType < 85 && pType >= 80) {
	entities.push_back(std::make_unique<Red_Platform>(rnd_x, 0));
      } else if (pType < 87 && pType >= 85) {
	entities.push_back(std::make_unique<HorizontalEnemy>(rnd_x, 0));
      } else if (pType < 90 && pType >= 87) {
	entities.push_back(std::make_unique<PlatformEnemy>(rnd_x, 0));
      } else if (pType < 92 && pType >= 90) {
	entities.push_back(std::make_unique<FallingEnemy>(rnd_x, 0));
      } else if (pType < 95 && pType >= 92) {
	entities.push_back(std::make_unique<Big_boost>(rnd_x, 0));
      } else if (pType <= 100 && pType >= 95) {
	entities.push_back(std::make_unique<Shield>(rnd_x, 0));
      }
    }
}


void World::destroyPlatforms()
{
    int screen_bottom{960};

    auto it = remove_if(entities.begin(), entities.end(), [screen_bottom](auto const& ent){return ent->getPos().y > screen_bottom;});
    entities.erase(it, entities.end());
}

void World::moveEntities() {
    playerAccel += 0.2;
    if (player.getPos().y < 450 && playerAccel < 0) {
        for (auto & ent : entities) {
            ent->move(0, -playerAccel);
        }
        score -= playerAccel;
    } else {
        player.move(0, playerAccel);
    }
}

void World::updateEntities() {
    auto it = entities.begin();
    while (it != entities.end()) {
        (*it)->update();
        if (!(*it)->isAlive) {
            it = entities.erase(it);
        } else {
            ++it;
        }
    }
}

bool World::testPlayerCollision(Entity &ent)
{
    if (player.getGlobalBounds().intersects(ent.getGlobalBounds()))
    {
        return true;
    }
    return false;
}

void World::updateScore()
{
    score_text.setString(std::to_string(score));
}
