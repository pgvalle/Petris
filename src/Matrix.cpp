#include "Matrix.h"
#include "config.h"

const int Matrix::W, Matrix::H;  // dimensions
const int8_t Matrix::EMPTY_CELL; // value to identify an empty cell

Matrix::Matrix() {
  for (int y = 0; y < H; y++) {
    matrix.push_back({0});
    matrix[y].fill(EMPTY_CELL);
    matrix[y][W] = 0; // filled cells counter
  }
}

void Matrix::compact() {
  for (int y = 0; y < matrix.size(); y++) {
    // check if row is empty
    bool emptyRow = true;
    for (int x = 0; x < W && emptyRow; x++) {
      if (matrix[y][x] != EMPTY_CELL)
        emptyRow = false;
    }
    // erase row if it is
    if (emptyRow)
      matrix.erase(matrix.begin() + y--);
  }
  // insert new empty rows in the beginning to restore height
  while (matrix.size() < H) {
    matrix.insert(matrix.begin(), {0});
    matrix[0].fill(EMPTY_CELL);
    matrix[0][W] = 0;
  }
}

void Matrix::updatePetrisRows() {
  for (int y = 0; y < H; y++) {
    // Skip rows that did not reach petris state yet
    if (matrix[y][W] < 10)
      continue;
    // Only reset petris state of already cleared rows
    if (matrix[y][W] == 15) {
      matrix[y][W] = 0;
      continue;
    }
    // clear rows from the middle to the edges
    int x = matrix[y][W] - 10;
    matrix[y][x + 5] = EMPTY_CELL;
    matrix[y][4 - x] = EMPTY_CELL;
    matrix[y][W]++;
  }
}

bool Matrix::hasPetrisRow() const {
  for (int y = 0; y < H; y++) {
    if (matrix[y][W] >= 10)
      return true;
  }
  return false;
}

void Matrix::placePetromino(const Petromino *petromino) {
  // place it on matrix
  petromino->iterate([&](int x, int y) {
    matrix[y][x] = petromino->paletteIndex;
    matrix[y][W]++; // row y got one more piece
  });
}

bool Matrix::collidePetromino(const Petromino *petromino) const {
  int collisions = 0;
  petromino->iterate([&](int x, int y) {
    // top y=0 can't restrict petromino placement/rotation
    bool outOfBounds = x < 0 || x >= W || y >= H;
    bool occupied = y >= 0 && matrix[y][x] != EMPTY_CELL;
    if (outOfBounds || occupied)
      collisions++;
  });
  return collisions > 0;
}

void Matrix::draw(sf::RenderTarget &target, sf::Texture &texture,
                  int level) const {
  sf::Sprite sprite(texture);
  sprite.setScale(0.125f * sf::Vector2f(TILE_SZ, TILE_SZ));

  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (matrix[y][x] == EMPTY_CELL)
        continue;
      sprite.setTextureRect(
          sf::IntRect({matrix[y][x] * 8, level % 10 * 8}, {8, 8}));
      sprite.setPosition(sf::Vector2f(x * TILE_SZ, y * TILE_SZ));
      target.draw(sprite);
    }
  }
}
