#ifndef BFS_H
#define BFS_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "grid.h"

void bfs(Grid& grid, sf::RenderWindow& window);

#endif