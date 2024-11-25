#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>

class GameState {
public:
    virtual ~GameState() {}
    virtual void handleEvent(sf::RenderWindow &window, sf::Event &event) = 0;
    virtual void update(sf::RenderWindow &window) = 0;
    virtual void draw(sf::RenderWindow &window) = 0;
};

#endif // GAMESTATE_H
