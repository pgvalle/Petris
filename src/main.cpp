#include "Petris.h"
#include "config.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

sf::RenderWindow window;
sf::Clock frameClock, tickClock;
sf::Time frameTime;
sf::Texture texture;
Petris petris;

void processEvent(const sf::Event &event);
void update();
void draw();

int main() {
  srand(time(NULL));
  window.create(sf::VideoMode({WINDOW_W, WINDOW_H}), "Petris");
  frameClock.start();
  tickClock.start();
  texture.loadFromFile("../../pieces.png");

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

  auto keypressed = event.getIf<sf::Event::KeyPressed>();
  if (keypressed) {
    switch (keypressed->code) {
    case sf::Keyboard::Key::A:
      petris.rotatePetronimo(1);
      break;
    case sf::Keyboard::Key::S:
      petris.rotatePetronimo(-1);
      break;
    case sf::Keyboard::Key::Left:
      petris.movePetronimoX(-1);
      break;
    case sf::Keyboard::Key::Right:
      petris.movePetronimoX(1);
      break;
    case sf::Keyboard::Key::Down:
      petris.movePetronimoDown();
      break;
    default:
      break;
    }

    return;
  }
}

void update() {
  if (tickClock.getElapsedTime() < TPS)
    return;

  petris.movePetronimoDown();
  tickClock.restart();
}
