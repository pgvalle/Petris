#include "Petris.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

sf::RenderWindow window;
sf::Texture texture;
sf::Font font;
Petris petris;

void processEvent(const sf::Event &event);
void update(const sf::Time &delta);
void draw();

int main() {
  window.create(sf::VideoMode({WIN_W, WIN_H}), "Petris");
  window.setFramerateLimit(30);
  window.setKeyRepeatEnabled(false);
  assert(texture.loadFromFile(BASE_PATH "res/pieces.png"));
  assert(font.openFromFile(BASE_PATH "res/font.otf"));

  sf::Clock frameClock;
  sf::Time frameDelta;

  while (window.isOpen()) {
    while (frameClock.getElapsedTime() < FPS) {
      if (std::optional event = window.pollEvent()) {
        processEvent(event.value());
      }
    }

    window.clear(sf::Color::Black);
    update(frameDelta);
    petris.draw(window, texture);
    window.display();

    frameDelta = frameClock.getElapsedTime();
    frameClock.restart();
  }

  window.close();
  return 0;
}

bool pause = false;

void processEvent(const sf::Event &event) {
  if (event.is<sf::Event::Closed>()) {
    window.close();
    return;
  }

  auto kbDn = event.getIf<sf::Event::KeyPressed>();
  if (kbDn && kbDn->code == sf::Keyboard::Key::Escape)
    pause = !pause;
  if (!pause)
    petris.processEvent(event);
}

void update(const sf::Time &delta) {
  if (!pause)
    petris.update(delta);
}
