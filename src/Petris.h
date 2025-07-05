#ifndef _PETRIS_H_
#define _PETRIS_H_

#include "Matrix.h"
#include "Petromino.h"
#include <SFML/System.hpp>
#include <cstdint>

class Petris {
public:
  Petris();

  void processEvent(const sf::Event &event);
  void update(const sf::Time &delta);
  void draw(sf::RenderTarget &target, sf::Texture &texture) const;

private:
  void GameplayProcessEvent(const sf::Event &event);
  void GameplayUpdate(const sf::Time &delta);
  void PetrisUpdate(const sf::Time &delta);

  void rotatePetromino(int dr);
  void movePetromino(int dx);

  // general

  enum { GAMEPLAY, PETRIS, COMPACT } state;
  Matrix matrix;
  uint8_t level;
  uint32_t score;
  Petromino *petromino;

  // gameplay

  sf::Time fallTime, fallInterval;
};

#endif // _PETRIS_H_
