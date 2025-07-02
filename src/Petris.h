#ifndef _PETRIS_H_
#define _PETRIS_H_

#include "Petromino.h"
#include "config.h"
#include <SFML/System.hpp>
#include <cstdint>

class Petris {
public:
  Petris();

  void rotatePetronimo(int dr);
  void movePetronimoX(int dx);
  void movePetronimoDown();
  void draw(sf::RenderTarget &target, sf::Texture &texture) const;

private:
  bool hasPetronimoCollided() const;

  uint8_t matrix[LEVEL_H][LEVEL_W];
  uint8_t level;
  uint32_t score;
  Petronimo *petronimo;
};

#endif // _PETRIS_H_