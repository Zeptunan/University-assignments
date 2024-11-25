#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include "GameState.h"
#include "Menu.h"
#include <vector>

class GameOverState : public GameState {
public:
    GameOverState(sf::Font &font);
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

    bool isRetryClicked(const sf::Vector2f &mousePos);
    bool isExitClicked(const sf::Vector2f &mousePos);

private:
    sf::Text gameOverText;
    std::vector<MenuItem> gameOverItems;
};

#endif // GAMEOVERSTATE_H
