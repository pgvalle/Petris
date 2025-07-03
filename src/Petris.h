#ifndef _PETRIS_H_
#define _PETRIS_H_

#include "Petromino.h"
#include "config.h"
#include <SFML/System.hpp>
#include <cstdint>

#define H_OFF 2

class Petris {
public:
  Petris();

  void rotatePetromino(int dr);
  void movePetromino(int dx);
  void movePetrominoDown();
  void draw(sf::RenderTarget &target, sf::Texture &texture) const;

private:
  bool hasPetrominoCollided() const;

  uint8_t matrix[LEVEL_H + H_OFF][LEVEL_W];
  uint8_t level;
  uint32_t score;
  Petromino *petromino;
};

#endif // _PETRIS_H_
