#include "Petris.h"

#define MAT_EMPTY_CELL 4

sf::Time calculateFallInterval(int level) {
  float fallInterval = std::pow(0.8f - 0.007f * level, level);
  return sf::seconds(fallInterval);
}

Petris::Petris() {
  state = GAMEPLAY;
  level = 0;
  score = 0;
  petromino = new Petromino;
  fallClock.start();
  fallInterval = calculateFallInterval(level);
}

void Petris::processEvent(const sf::Event &event) {
  switch (state) {
  case GAMEPLAY: {
    auto kbDn = event.getIf<sf::Event::KeyPressed>();
    if (kbDn && kbDn->code == sf::Keyboard::Key::Down)
      fallInterval = sf::seconds(0);
    if (kbDn && kbDn->code == sf::Keyboard::Key::Z)
      rotatePetromino(-1);
    if (kbDn && kbDn->code == sf::Keyboard::Key::X)
      rotatePetromino(1);
    if (kbDn && kbDn->code == sf::Keyboard::Key::Left)
      movePetromino(-1);
    if (kbDn && kbDn->code == sf::Keyboard::Key::Right)
      movePetromino(1);

    auto kbUp = event.getIf<sf::Event::KeyReleased>();
    if (kbUp && kbUp->code == sf::Keyboard::Key::Down)
      fallInterval = calculateFallInterval(level);
  } break;
  case PETRIS:
    break;
  case COMPACT:
    break;
  }
}

void Petris::update() {
  switch (state) {
  case GAMEPLAY:
    if (fallClock.getElapsedTime() < fallInterval)
      break;
    fallClock.restart();
    // try moving it
    petromino->position.y++;
    if (!matrix.collidePetromino(petromino))
      break;
    // failed, so go back to previous position and place it there
    petromino->position.y--;
    matrix.placePetromino(petromino);
    // this petronimo is done now
    delete petromino;
    petromino = new Petromino;
    // check for a tetris
    if (matrix.hasPetrisRow())
      state = PETRIS;
    break;
  case PETRIS:
    matrix.updatePetrisRows();
    if (!matrix.hasPetrisRow())
      state = COMPACT;
    break;
  case COMPACT:
    printf("here2!\n");
    matrix.compact();
    state = GAMEPLAY;
    fallClock.restart();
    fallInterval = calculateFallInterval(level);
    break;
  }
}

void Petris::draw(sf::RenderTarget &target, sf::Texture &texture) const {
  if (state == GAMEPLAY)
    petromino->draw(target, texture, level);

  matrix.draw(target, texture, level);
}

void Petris::rotatePetromino(int dr) {
  petromino->rotate(dr);
  if (matrix.collidePetromino(petromino))
    petromino->rotate(-dr);
}

void Petris::movePetromino(int dx) {
  petromino->position.x += dx;
  if (matrix.collidePetromino(petromino))
    petromino->position.x -= dx;
}
