#ifndef _PETRIS_H_
#define _PETRIS_H_

#include "Petromino.h"
#include "config.h"
#include <SFML/System.hpp>
#include <cstdint>

class Petris {
public:
  Petris();

  void processEvent(const sf::Event &event);
  void update();
  void draw(sf::RenderTarget &target, sf::Texture &texture) const;

private:
  void rotatePetromino(int dr);
  void movePetromino(int dx);
  bool hasPetrominoCollided() const;

  // general

  enum { GAMEPLAY, PETRIS } state;
  uint8_t matrix[MAT_H][MAT_W + 1];
  uint8_t level;
  uint32_t score;
  Petromino *petromino;

  // gameplay

  sf::Clock moveDownClock;
  sf::Time moveDownTime;
};

#endif // _PETRIS_H_
