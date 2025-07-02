#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/System.hpp>

#define TILE_SZ 16                   // tile size
#define LEVEL_W 10                   // level width
#define LEVEL_H 20                   // level height
#define WINDOW_W (TILE_SZ * LEVEL_W) // window width
#define WINDOW_H (TILE_SZ * LEVEL_H) // window height

#define FPS sf::seconds(1.f / 60.f)
#define TPS sf::seconds(1)

#endif // CONFIG_H