#include "dijkstra.h"

using namespace std;

void dijkstra(Grid& grid, sf::RenderWindow& window) {
  int rows = grid.getRows();
  int cols = grid.getCols();

  vector<vector<int>> distances(rows, vector<int>(cols, INF));
  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  vector<vector<pair<int, int>>> parentList(
      rows, vector<pair<int, int>>(cols, {-1, -1}));

  int startX = grid.getStartX(), startY = grid.getStartY();
  int endX = grid.getEndX(), endY = grid.getEndY();

  distances[startX][startY] = 0;

  using PII = pair<int, pair<int, int>>;
  priority_queue<PII, vector<PII>, greater<PII>> pq;
  pq.push({0, {startX, startY}});

  while (!pq.empty()) {
    auto [currentDist, coords] = pq.top();
    pq.pop();
    auto [x, y] = coords;

    if (visited[x][y]) continue;
    visited[x][y] = true;

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
        int newX = x + dx, newY = y + dy;

        if (grid.isWalkable(newX, newY)) {
          int newDist = currentDist + 1;  // Uniform cost for each step
          if (newDist < distances[newX][newY]) {
            distances[newX][newY] = newDist;
            pq.push({newDist, {newX, newY}});
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
