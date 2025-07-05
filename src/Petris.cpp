#include "Petris.h"

#define MAT_EMPTY_CELL 4

sf::Time calculateInterval(int level) {
  float interval = std::pow(0.8f - 0.007f * level, level);
  return sf::seconds(interval);
}

Petris::Petris() {
  state = GAMEPLAY;
  level = 0;
  score = 0;
  petromino = new Petromino();
  fallTime = sf::seconds(0);
  fallInterval = calculateInterval(level);
}

void Petris::processEvent(const sf::Event &event) {
  switch (state) {
  case GAMEPLAY:
    GameplayProcessEvent(event);
    break;
  case PETRIS:
    break;
  case COMPACT:
    break;
  }
}

void Petris::update(const sf::Time &delta) {
  switch (state) {
  case GAMEPLAY:
    GameplayUpdate(delta);
    break;
  case PETRIS:
    matrix.updatePetrisRows();
    if (!matrix.hasPetrisRow())
      state = COMPACT;
    break;
  case COMPACT:
    matrix.compact();
    state = GAMEPLAY;
    break;
  }
}

void Petris::draw(sf::RenderTarget &target, sf::Texture &texture) const {
  if (state == GAMEPLAY)
    petromino->draw(target, texture, level);

  matrix.draw(target, texture, level);
}

void Petris::GameplayProcessEvent(const sf::Event &event) {
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
    fallInterval = calculateInterval(level);
}

void Petris::GameplayUpdate(const sf::Time &delta) {
  fallTime += delta;
  if (fallTime < fallInterval)
    return;
  fallTime -= fallInterval;
  // try moving it
  petromino->position.y++;
  if (!matrix.collidePetromino(petromino))
    return;
  // failed, so go back to previous position and place it there
  petromino->position.y--;
  matrix.placePetromino(petromino);
  // this petronimo is done now
  delete petromino;
  petromino = new Petromino();
  // check for a tetris
  if (matrix.hasPetrisRow())
    state = PETRIS;
  // stop falling fast
  fallTime = sf::seconds(0);
  fallInterval = calculateInterval(level);
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
