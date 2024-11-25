#include "PlayingState.h"

PlayingState::PlayingState() : world(), gameOver(false) {}

void PlayingState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
  if (gameOver) {
    return;
      }
}

void PlayingState::update(sf::RenderWindow &window) {
    world.update();
    world.testCollision();

    if (!world.playerAlive()) {
        gameOver = true;
    }
}

bool PlayingState::isGameOver() const {
    return gameOver;
}


void PlayingState::draw(sf::RenderWindow &window) {
    world.draw(window);
}

