#include "Petris.h"
#include "Petromino.h"

#define EMPTY_MATRIX_CELL 4

Petris::Petris() {
  for (int y = 0; y < LEVEL_H + H_OFF; y++) {
    for (int x = 0; x < LEVEL_W; x++)
      matrix[y][x] = EMPTY_MATRIX_CELL;
  }

  level = 4;
  score = 0;
  petromino = new Petromino;
}

void Petris::rotatePetromino(int dr) {
  dr /= abs(dr);

  petromino->orientation = (petromino->orientation + dr) % 4;
  if (petromino->orientation < 0)
    petromino->orientation += 4;

  if (hasPetrominoCollided()) {
    petromino->orientation = (petromino->orientation - dr) % 4;
    if (petromino->orientation < 0)
      petromino->orientation += 4;
  }
}

void Petris::movePetrominoX(int dx) {
  dx /= abs(dx);

  petromino->position.x += dx;
  if (hasPetrominoCollided())
    petromino->position.x -= dx;
}

void Petris::movePetrominoDown() {
  petromino->position.y++;
  if (hasPetrominoCollided()) {
    petromino->position.y--;
    petromino->iterate([&](int x, int y) {
      matrix[y + H_OFF][x] = petromino->paletteIndex;
    });

    delete petromino;
    petromino = new Petromino;
  }
}

void Petris::draw(sf::RenderTarget &target, sf::Texture &texture) const {
  petromino->draw(target, texture, level);

  sf::Sprite sprite(texture);
  sprite.setScale(0.125f * sf::Vector2f(TILE_SZ, TILE_SZ));

  for (int y = 0; y < LEVEL_H; y++) {
    for (int x = 0; x < LEVEL_W; x++) {
      if (matrix[y + H_OFF][x] == EMPTY_MATRIX_CELL)
        continue;

      sprite.setTextureRect(sf::IntRect({matrix[y + H_OFF][x] * 8, level * 8}, {8, 8}));
      sprite.setPosition(sf::Vector2f(x * TILE_SZ, y * TILE_SZ));
      target.draw(sprite);
    }
  }
}

bool Petris::hasPetrominoCollided() const {
  int collisions = 0;
  petromino->iterate([&](int x, int y) {
    bool outOfBounds = 0 > x || x >= LEVEL_W || y >= LEVEL_H;
    if (outOfBounds || matrix[y + H_OFF][x] != EMPTY_MATRIX_CELL) {
      collisions++;
    }
  });

  return collisions > 0;
}
