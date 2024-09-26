#include "grid.h"

// Grid constructor
Grid::Grid(int rows, int cols)
    : rows(rows), cols(cols), startX(-1), startY(-1), endX(-1), endY(-1) {
  grid.resize(rows, std::vector<int>(cols, EMPTY));

  // Generate random obstacles
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      if (rand() % 5 == 0) {
        grid[i][j] = OBSTACLE;
      }
    }
  }
}

// Check if cell doesn't cross boundary of grid
bool Grid::isValidCell(int x, int y) const {
  return x >= 0 && x < rows && y >= 0 && y < cols;
}

// Set start point
void Grid::setStart(int x, int y) {
  if (isValidCell(x, y)) {
    startX = x;
    startY = y;
    grid[x][y] = START;
    if (x != 0 || y != 0) {
      grid[0][0] = 0;
    }
  }
}

// Set end point
void Grid::setEnd(int x, int y) {
  if (isValidCell(x, y)) {
    endX = x;
    endY = y;
    grid[x][y] = END;
    if (x != rows - 1 || y != cols - 1) {
      grid[rows - 1][cols - 1] = 0;
    }
  }
}

// Add an obstacle
void Grid::addObstacle(int x, int y) {
  if (isValidCell(x, y)) {
    grid[x][y] = OBSTACLE;
  }
}

// Clear an obstacle
void Grid::clearObstacle(int x, int y) {
  if (isValidCell(x, y)) {
    grid[x][y] = EMPTY;
  }
}

// Check if a cell is walkable
bool Grid::isWalkable(int x, int y) const {
  return isValidCell(x, y) && grid[x][y] != OBSTACLE;
}

// Display the grid (for debugging)
void Grid::displayGrid() const {
  for (const auto& row : grid) {
    for (int cell : row) {
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }
}

int Grid::getRows() const { return rows; }
int Grid::getCols() const { return cols; }
int Grid::getStartX() const { return startX; }
int Grid::getStartY() const { return startY; }
int Grid::getEndX() const { return endX; }
int Grid::getEndY() const { return endY; }

// Get the grid value at a specific cell
int Grid::getGridValue(int x, int y) const {
  if (isValidCell(x, y)) {
    return grid[x][y];
  }
  return -1;  // Invalid cell
}

void Grid::markPath(int x, int y, int pathType) {
  if (isValidCell(x, y)) {
    grid[x][y] = pathType;
  }
}

void Grid::drawGrid(sf::RenderWindow& window) {
  int rows = getRows();
  int cols = getCols();

  const int windowWidth = 800;
  const int windowHeight = 800;
  const float cellSize = std::min(windowWidth / static_cast<float>(cols),
                                  windowHeight / static_cast<float>(rows));

  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
      cell.setPosition(j * cellSize, i * cellSize);

      switch (getGridValue(i, j)) {
        case OBSTACLE:
          cell.setFillColor(sf::Color::Black);
          break;
        case START:
          cell.setFillColor(sf::Color::Green);
          break;
        case END:
          cell.setFillColor(sf::Color::Red);
          break;
        case PATH_EXPLORED:
          cell.setFillColor(sf::Color::Yellow);
          break;
        case PATH_FINAL:
          cell.setFillColor(sf::Color::Magenta);
          break;
        default:  // Empty
          cell.setFillColor(sf::Color::White);
          break;
      }

      window.draw(cell);

      // Draw border
      sf::RectangleShape border(sf::Vector2f(cellSize, cellSize));
      border.setPosition(j * cellSize, i * cellSize);
      border.setOutlineColor(sf::Color(128, 128, 128));
      border.setOutlineThickness(2);
      border.setFillColor(sf::Color::Transparent);
      window.draw(border);
    }
  }
}

// Generate a random maze (using dfs) (ensuring there always exists a path)
void Grid::generateRandomMaze() {
  // Initialize the whole grid with walls
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      grid[i][j] = OBSTACLE;
    }
  }

  int startX = getStartX();
  int startY = getStartY();
  grid[startX][startY] = EMPTY;

  std::stack<std::pair<int, int>> stack;
  stack.push({startX, startY});

  std::vector<std::pair<int, int>> directions = {
      {0, 2}, {0, -2}, {2, 0}, {-2, 0}};

  while (!stack.empty()) {
    auto [x, y] = stack.top();
    stack.pop();

    // Randomly shuffle directions
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(directions.begin(), directions.end(), g);

    for (const auto& direction : directions) {
      int newX = x + direction.first;
      int newY = y + direction.second;

      if (isValidCell(newX, newY) && grid[newX][newY] == 1) {
        grid[(x + newX) / 2][(y + newY) / 2] = EMPTY;  // Clear the wall
        grid[newX][newY] = 0;  // Make the new cell walkable

        stack.push({newX, newY});
      }
    }
  }
}
