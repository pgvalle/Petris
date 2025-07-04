#include "Petromino.h"
#include "config.h"
#include <random>

Petromino::Petromino() {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  static std::uniform_int_distribution<uint8_t> distrib(0, 6);

  type = (Type)distrib(gen);
  orientation = 0;
  paletteIndex = rand() % 3;
  position = sf::Vector2i(5, 0);
}

void Petromino::rotate(int dr) {
  orientation += dr;
  orientation %= 4;
  if (orientation < 0)
    orientation += 4;
}

void Petromino::iterate(const std::function<void(int, int)> &callback) const {
  int a = orientation == 0 ? 1 : (orientation == 2 ? -1 : 0);
  int b = orientation == 1 ? 1 : (orientation == 3 ? -1 : 0);

  switch (type) {
  case O:
    callback(position.x, position.y + 1);
    callback(position.x - 1, position.y);
    callback(position.x - 1, position.y + 1);
    break;
  case I:
    if (a) {
      callback(position.x + 1, position.y);
      callback(position.x - 1, position.y);
      callback(position.x - 2, position.y);
    } else {
      callback(position.x, position.y + 1);
      callback(position.x, position.y - 1);
      callback(position.x, position.y - 2);
    }
    break;
  case S:
    a = abs(a);
    b = abs(b);
    callback(position.x + a, position.y - b);
    callback(position.x + b, position.y + a);
    callback(position.x - a + b, position.y + a + b);
    break;
  case Z:
    a = abs(a);
    b = abs(b);
    callback(position.x - a, position.y + b);
    callback(position.x + b, position.y + a);
    callback(position.x + a + b, position.y + a - b);
    break;
  case L:
    callback(position.x + a, position.y + b);
    callback(position.x - a, position.y - b);
    callback(position.x - a + b, position.y + a + b);
    break;
  case J:
    callback(position.x + a, position.y + b);
    callback(position.x - a, position.y - b);
    callback(position.x + a - b, position.y + a + b);
    break;
  case T:
    callback(position.x + a, position.y + b); // down
    callback(position.x - b, position.y + a); // top-left
    callback(position.x - a, position.y - b); // top-right
    break;
  }

  callback(position.x, position.y);
}

void Petromino::draw(sf::RenderTarget &target, sf::Texture &texture,
                     int level) const {
  sf::Sprite sprite(texture);
  sprite.setScale(0.125f * sf::Vector2f(TILE_SZ, TILE_SZ));
  sprite.setTextureRect(
      sf::IntRect({paletteIndex * 8, level % 10 * 8}, {8, 8}));

  iterate([&](int x, int y) {
    sprite.setPosition(sf::Vector2f(x * TILE_SZ, y * TILE_SZ));
    target.draw(sprite);
  });
}
