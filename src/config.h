#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/System.hpp>

#define BASE_PATH "../../"

#define TILE_SZ 16
#define WIN_W (TILE_SZ * 32)
#define WIN_H (TILE_SZ * 28)

#define FPS sf::seconds(1.f / 60.f)
#define TPS sf::seconds(1)

#endif // CONFIG_H