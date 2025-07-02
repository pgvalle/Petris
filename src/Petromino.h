#ifndef _PETROMINO_H_
#define _PETROMINO_H_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <functional>

struct Petromino {
  enum Type { O, I, S, Z, L, J, T } type;
  int8_t orientation;
  uint8_t paletteIndex;
  sf::Vector2i position;

  Petromino();

  void iterate(const std::function<void(int, int)> &callback) const;
  void draw(sf::RenderTarget &target, sf::Texture &texture, int level) const;
};

#endif // _PETROMINO_H_