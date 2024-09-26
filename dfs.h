#ifndef DFS_H
#define DFS_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <stack>
#include <thread>
#include <vector>

#include "grid.h"

void dfs(Grid& grid, sf::RenderWindow& window);

#endif