#include "Petris.h"
#include "Petromino.h"
#include "config.h"
#include <cmath>

#define EMPTY_MAT_CELL 4

sf::Time calculateMoveDownTime(int level) {
  float moveDownTime = std::pow(0.8f - 0.007f * (level - 1), level - 1);
  return sf::seconds(moveDownTime);
}

Petris::Petris() {
  for (int y = 0; y < MAT_H; y++) {
    for (int x = 0; x < MAT_W; x++)
      matrix[y][x] = EMPTY_MAT_CELL;
    matrix[y][MAT_W] = 0; // petris byte
  }

  state = GAMEPLAY;
  level = 1;
  score = 0;
  petromino = new Petromino;

  moveDownClock.start();
  moveDownTime = calculateMoveDownTime(level);
}

void Petris::processEvent(const sf::Event &event) {

}

void Petris::update() {
  switch (state) {
  case GAMEPLAY:
    if (moveDownClock.getElapsedTime() < moveDownTime)
      break;
    petromino->position.y++;
    if (!hasPetrominoCollided())
      break;
    petromino->position.y--;
    petromino->iterate([&](int x, int y) {
      matrix[y][x] = petromino->paletteIndex;
    });
    break;
  case PETRIS:
    for (int y = 0; y < MAT_H; y++) {
      if (!matrix[y][MAT_W])
        continue;
      // process here
    }
    for (int y = 0; y < MAT_H; y++) {
      if (matrix[y][MAT_W])
        return;
    }
    
    break;
  }
}

void Petris::draw(sf::RenderTarget &target, sf::Texture &texture) const {
  petromino->draw(target, texture, level);

  sf::Sprite sprite(texture);
  sprite.setScale(0.125f * sf::Vector2f(TILE_SZ, TILE_SZ));

  for (int y = 0; y < MAT_H; y++) {
    for (int x = 0; x < MAT_W; x++) {
      if (matrix[y][x] == EMPTY_MAT_CELL)
        continue;

      sprite.setTextureRect(sf::IntRect({matrix[y][x] * 8, level * 8}, {8, 8}));
      sprite.setPosition(sf::Vector2f(x * TILE_SZ, y * TILE_SZ));
      target.draw(sprite);
    }
  }
}

void Petris::rotatePetromino(int dr) {
  petromino->rotate(dr);
  if (hasPetrominoCollided())
    petromino->rotate(-dr);
}

void Petris::movePetromino(int dx) {
  petromino->position.x += dx;
  if (hasPetrominoCollided())
    petromino->position.x -= dx;
}

bool Petris::hasPetrominoCollided() const {
  assert(petromino);

  int collisions = 0;
  petromino->iterate([&](int x, int y) {
    bool outOfBounds = 0 > x || x >= MAT_W || y >= MAT_H;
    bool occupied = y >= 0 && matrix[y][x] != EMPTY_MAT_CELL;
    if (outOfBounds || occupied)
      collisions++;
  });
  return collisions > 0;
}
