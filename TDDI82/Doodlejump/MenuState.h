#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "GameState.h"
#include "Menu.h"
#include <vector>

class MenuState : public GameState {
public:
    MenuState(sf::Font &font);
    void handleEvent(sf::RenderWindow &window, sf::Event &event) override;
    void update(sf::RenderWindow &window) override;
    void draw(sf::RenderWindow &window) override;

    bool isPlayClicked(const sf::Vector2f &mousePos);
    bool isExitClicked(const sf::Vector2f &mousePos);

private:
    std::vector<MenuItem> menuItems;
};

#endif // MENUSTATE_H
