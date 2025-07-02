#include "Petris.h"
#include "Petromino.h"

#define EMPTY_MATRIX_CELL 4

Petris::Petris() {
  for (int y = 0; y < LEVEL_H; y++) {
    for (int x = 0; x < LEVEL_W; x++)
      matrix[y][x] = EMPTY_MATRIX_CELL;
  }

  level = 4;
  score = 0;
  petronimo = new Petronimo;
}

void Petris::rotatePetronimo(int dr) {
  dr /= abs(dr);

  petronimo->orientation = (petronimo->orientation + dr) % 4;
  if (petronimo->orientation < 0)
    petronimo->orientation += 4;

  if (hasPetronimoCollided()) {
    petronimo->orientation = (petronimo->orientation - dr) % 4;
    if (petronimo->orientation < 0)
      petronimo->orientation += 4;
  }
}

void Petris::movePetronimoX(int dx) {
  dx /= abs(dx);

  petronimo->position.x += dx;
  if (hasPetronimoCollided())
    petronimo->position.x -= dx;
}

void Petris::movePetronimoDown() {
  petronimo->position.y++;
  if (hasPetronimoCollided()) {
    petronimo->position.y--;
    petronimo->iterate([&](int x, int y) {
      matrix[y][x] = petronimo->paletteIndex;
    });

    delete petronimo;
    petronimo = new Petronimo;
  }
}

void Petris::draw(sf::RenderTarget &target, sf::Texture &texture) const {
  petronimo->draw(target, texture, level);

  sf::Sprite sprite(texture);
  sprite.setScale(0.125f * sf::Vector2f(TILE_SZ, TILE_SZ));

  for (int y = 0; y < LEVEL_H; y++) {
    for (int x = 0; x < LEVEL_W; x++) {
      if (matrix[y][x] == EMPTY_MATRIX_CELL)
        continue;

      sprite.setTextureRect(sf::IntRect({matrix[y][x] * 8, level * 8}, {8, 8}));
      sprite.setPosition(sf::Vector2f(x * TILE_SZ, y * TILE_SZ));
      target.draw(sprite);
    }
  }
}

bool Petris::hasPetronimoCollided() const {
  int collisions = 0;
  petronimo->iterate([&](int x, int y) {
    bool outOfBounds = 0 > x || x >= LEVEL_W || y >= LEVEL_H;
    if (outOfBounds || matrix[y][x] != EMPTY_MATRIX_CELL) {
      collisions++;
    }
  });

  return collisions > 0;
}