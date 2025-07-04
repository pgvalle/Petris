#ifndef _MATRIX_H_
#define _MATRIX_H_

#include "Petromino.h"
#include <array>
#include <vector>


struct Matrix {
  static const int W = 10, H = 20; // dimensions
  static const int8_t EMPTY_CELL = 4; // value to identify an empty cell
  std::vector<std::array<int8_t, W + 1>> matrix;

  Matrix();

  void compact();
  void updatePetrisRows();
  bool hasPetrisRow() const;
  void placePetromino(const Petromino *petromino);
  bool collidePetromino(const Petromino *petromino) const;
  void draw(sf::RenderTarget &target, sf::Texture &texture, int level) const;
};

#endif // _MATRIX_H_