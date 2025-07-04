#ifndef CONFIG_H
#define CONFIG_H

#include <SFML/System.hpp>

#define BASE_PATH "../../"

#define TILE_SZ 16
#define MAT_W 10
#define MAT_H 20
#define WIN_W (TILE_SZ * MAT_W)
#define WIN_H (TILE_SZ * MAT_H)

#define FPS sf::seconds(1.f / 60.f)
#define TPS sf::seconds(1)

#endif // CONFIG_H