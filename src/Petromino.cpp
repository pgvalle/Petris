#include "Petromino.h"
#include "config.h"

Petronimo::Petronimo() {
  type = (Type)(rand() % 7);
  orientation = 0;
  paletteIndex = rand() % 3;
  position = sf::Vector2i(5, 0);
}

void Petronimo::iterate(const std::function<void(int, int)> &callback) const {
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

void Petronimo::draw(sf::RenderTarget &target, sf::Texture &texture,
                     int level) const {
  sf::Sprite sprite(texture);
  sprite.setScale(0.125f * sf::Vector2f(TILE_SZ, TILE_SZ));
  sprite.setTextureRect(sf::IntRect({paletteIndex * 8, level * 8}, {8, 8}));

  iterate([&](int x, int y) {
    sprite.setPosition(sf::Vector2f(x * TILE_SZ, y * TILE_SZ));
    target.draw(sprite);
  });
}
