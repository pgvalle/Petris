#include "Petris.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

sf::RenderWindow window;
sf::Clock frameClock;
sf::Time frameTime;
sf::Texture texture;
sf::Font font;
Petris petris;

void processEvent(const sf::Event &event);
void update();
void draw();

int main() {
  srand(time(NULL));
  window.create(sf::VideoMode({WIN_W, WIN_H}), "Petris");
  window.setFramerateLimit(60);
  frameClock.start();
  assert(texture.loadFromFile(BASE_PATH "res/pieces.png"));
  assert(font.openFromFile(BASE_PATH "res/font.otf"));

  while (window.isOpen()) {
    while (frameClock.getElapsedTime() < FPS) {
      if (auto event = window.pollEvent()) {
        processEvent(event.value());
      }
    }

    window.clear(sf::Color::Black);
    update();
    petris.draw(window, texture);
    window.display();

    frameTime = frameClock.getElapsedTime();
    frameClock.restart();
  }

  window.close();
  return 0;
}

void processEvent(const sf::Event &event) {
  if (event.is<sf::Event::Closed>()) {
    window.close();
    return;
  }

  
}

void update() {
  
}
