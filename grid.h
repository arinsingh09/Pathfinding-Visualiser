#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stack>
#include <vector>

enum CellType {
  EMPTY = 0,
  OBSTACLE = 1,
  START = 2,
  END = 3,
  PATH_EXPLORED = 4,
  PATH_FINAL = 5
};

#define INF 1e9

class Grid {
 public:
  Grid(int rows, int cols);

  void setStart(int x, int y);
  void setEnd(int x, int y);
  void addObstacle(int x, int y);
  void clearObstacle(int x, int y);

  bool isWalkable(int x, int y) const;
  void displayGrid() const;
  void generateRandomMaze();
  void markPath(int x, int y, int pathType);

  int getRows() const;
  int getCols() const;
  int getStartX() const;
  int getStartY() const;
  int getEndX() const;
  int getEndY() const;
  int getGridValue(int x, int y) const;

  void drawGrid(sf::RenderWindow& window);

  std::vector<std::vector<int>> grid;

 private:
  int rows, cols;
  int startX, startY;
  int endX, endY;

  bool isValidCell(int x, int y) const;
};

#endif