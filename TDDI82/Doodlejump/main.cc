#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "MenuState.h"
#include "PlayingState.h"
#include "GameOverState.h"

#include <memory>
#include <iostream>

int main() {
  sf::RenderWindow window(sf::VideoMode(640, 960), "Doodle Jump");
  window.setFramerateLimit(60);

  
  sf::Texture background;
  background.loadFromFile("resources/background.png"); 
  sf::Sprite backgroundSprite;
  backgroundSprite.setTexture(background);

  // Loada font
  sf::Font font;
  if (!font.loadFromFile("resources/comic_sans.ttf")) {
    std::cerr << "Error loading font";
    return -1;
  }

  std::unique_ptr<GameState> state = std::make_unique<MenuState>(font);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
	window.close();
      }

      state->handleEvent(window, event);

      // state change
      if (auto menuState = dynamic_cast<MenuState*>(state.get())) {
	if (event.type == sf::Event::MouseButtonPressed) {
	  sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	  if (menuState->isPlayClicked(mousePos)) {
	    state = std::make_unique<PlayingState>();
	    break;
	  } else if (menuState->isExitClicked(mousePos)) {
	    window.close();
	  }
	}
      
      } else if (auto gameOverState = dynamic_cast<GameOverState*>(state.get())) {
	if (event.type == sf::Event::MouseButtonPressed) {
	  sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
	  if (gameOverState->isRetryClicked(mousePos)) {
	    state = std::make_unique<PlayingState>();
	    break;
	  } else if (gameOverState->isExitClicked(mousePos)) {
	    window.close();
	  }
	}
      }
    }
    if (auto playingState = dynamic_cast<PlayingState*>(state.get())) {
        
      if (playingState->isGameOver()) {
	state = std::make_unique<GameOverState>(font);
	 
      }
    }
    window.clear(sf::Color::White);
    window.draw(backgroundSprite);

    state->update(window);
    state->draw(window);

    window.display();
  }

  return 0;
}
