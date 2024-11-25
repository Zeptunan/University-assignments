#include "MenuState.h"

MenuState::MenuState(sf::Font &font) {
    menuItems.push_back(MenuItem("Play", font, 50, sf::Vector2f(270, 400)));
    menuItems.push_back(MenuItem("Exit", font, 50, sf::Vector2f(270, 500)));
}

void MenuState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    // tom
}

void MenuState::update(sf::RenderWindow &window) {
    for (auto &item : menuItems) {
        item.isMouseOver(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }
}

void MenuState::draw(sf::RenderWindow &window) {
    for (auto &item : menuItems) {
        item.draw(window);
    }
}

bool MenuState::isPlayClicked(const sf::Vector2f &mousePos) {
    return menuItems[0].isClicked(mousePos);
}

bool MenuState::isExitClicked(const sf::Vector2f &mousePos) {
    return menuItems[1].isClicked(mousePos);
}
