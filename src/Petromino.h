#ifndef _PETRONIMO_H_
#define _PETRONIMO_H_

#include <SFML/Graphics.hpp>
#include <cstdint>
#include <functional>

struct Petronimo {
  enum Type { O, I, S, Z, L, J, T } type;
  int8_t orientation;
  uint8_t paletteIndex;
  sf::Vector2i position;

  Petronimo();

  void iterate(const std::function<void(int, int)> &callback) const;
  void draw(sf::RenderTarget &target, sf::Texture &texture, int level) const;
};

#endif // _PETRONIMO_H_