#ifndef BIDIRECTIONAL_H
#define BIDIRECTIONAL_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "grid.h"

void bidirectionalSearch(Grid& grid, sf::RenderWindow& window);

#endif