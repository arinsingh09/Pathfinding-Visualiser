#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <queue>
#include <thread>
#include <vector>

#include "grid.h"

void dijkstra(Grid& grid, sf::RenderWindow& window);

#endif