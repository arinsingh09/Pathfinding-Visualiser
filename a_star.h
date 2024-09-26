#ifndef A_STAR_H
#define A_STAR_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <cmath>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "grid.h"

void aStar(Grid& grid, sf::RenderWindow& window);

#endif