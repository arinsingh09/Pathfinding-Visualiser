#include "a_star.h"
using namespace std;

int diagonalDistance(int x1, int y1, int x2, int y2) {
  int dx = abs(x1 - x2);
  int dy = abs(y1 - y2);
  return dx + dy + (sqrt(2) - 2) * min(dx, dy);
}

void aStar(Grid& grid, sf::RenderWindow& window) {
  int rows = grid.getRows();
  int cols = grid.getCols();

  vector<vector<int>> gScore(rows, vector<int>(cols, INF));
  vector<vector<int>> fScore(rows, vector<int>(cols, INF));
  vector<vector<bool>> closedSet(rows, vector<bool>(cols, false));
  vector<vector<pair<int, int>>> parentList(
      rows, vector<pair<int, int>>(cols, {-1, -1}));

  int startX = grid.getStartX(), startY = grid.getStartY();
  int endX = grid.getEndX(), endY = grid.getEndY();

  gScore[startX][startY] = 0;
  fScore[startX][startY] = diagonalDistance(startX, startY, endX, endY);

  using PII = pair<int, pair<int, int>>;
  priority_queue<PII, vector<PII>, greater<PII>> openSet;
  openSet.push({fScore[startX][startY], {startX, startY}});

  while (!openSet.empty()) {
    auto [_, coords] = openSet.top();
    auto [x, y] = coords;
    openSet.pop();

    if (closedSet[x][y]) continue;
    closedSet[x][y] = true;

    // Mark the final path
    if (x == endX && y == endY) {
      cout << "Path found!" << endl;
      grid.markPath(startX, startY, START);
      while (coords != make_pair(startX, startY)) {
        grid.markPath(coords.first, coords.second, PATH_FINAL);
        coords = parentList[coords.first][coords.second];
      }
      grid.markPath(endX, endY, END);
      return;
    }

    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        if (dx == 0 && dy == 0) continue;  // Skip the current cell itself

        int newX = x + dx, newY = y + dy;

        if (grid.isWalkable(newX, newY) && !closedSet[newX][newY]) {
          // movement cost: 1 for straight moves, sqrt(2) for diagonal
          int moveCost = (dx != 0 && dy != 0) ? sqrt(2) : 1;
          int tentative_gScore = gScore[x][y] + moveCost;

          if (tentative_gScore < gScore[newX][newY]) {
            gScore[newX][newY] = tentative_gScore;
            fScore[newX][newY] =
                gScore[newX][newY] + diagonalDistance(newX, newY, endX, endY);
            openSet.push({fScore[newX][newY], {newX, newY}});
            parentList[newX][newY] = {x, y};
            grid.markPath(newX, newY, PATH_EXPLORED);
          }
        }
      }
    }

    this_thread::sleep_for(chrono::milliseconds(100));
    window.clear();
    grid.drawGrid(window);
    window.display();
  }

  cout << "No path found." << endl;
}