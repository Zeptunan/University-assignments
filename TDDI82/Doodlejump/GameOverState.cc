#include "GameOverState.h"

GameOverState::GameOverState(sf::Font &font) {
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(200, 200);

    gameOverItems.push_back(MenuItem("Retry", font, 50, sf::Vector2f(270, 400)));
    gameOverItems.push_back(MenuItem("Exit", font, 50, sf::Vector2f(270, 500)));
}

void GameOverState::handleEvent(sf::RenderWindow &window, sf::Event &event) {
    // tom
}

void GameOverState::update(sf::RenderWindow &window) {
    for (auto &item : gameOverItems) {
        item.isMouseOver(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
    }
}

void GameOverState::draw(sf::RenderWindow &window) {
    window.draw(gameOverText);
    for (auto &item : gameOverItems) {
        item.draw(window);
    }
}

bool GameOverState::isRetryClicked(const sf::Vector2f &mousePos) {
    return gameOverItems[0].isClicked(mousePos);
}

bool GameOverState::isExitClicked(const sf::Vector2f &mousePos) {
    return gameOverItems[1].isClicked(mousePos);
}
