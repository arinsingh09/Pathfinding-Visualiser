#include "bfs.h"

using namespace std;

void bfs(Grid& grid, sf::RenderWindow& window) {
  int rows = grid.getRows();
  int cols = grid.getCols();

  vector<vector<bool>> visited(rows, vector<bool>(cols, false));
  vector<vector<pair<int, int>>> parentList(
      rows, vector<pair<int, int>>(cols, {-1, -1}));

  int startX = grid.getStartX(), startY = grid.getStartY();
  int endX = grid.getEndX(), endY = grid.getEndY();

  queue<pair<int, int>> q;
  q.push({startX, startY});
  visited[startX][startY] = true;

  while (!q.empty()) {
    auto [x, y] = q.front();
    q.pop();

    // Mark the final path
    if (x == endX && y == endY) {
      cout << "Path found!" << endl;
      grid.markPath(startX, startY, START);
      while (make_pair(x, y) != make_pair(startX, startY)) {
        grid.markPath(x, y, PATH_FINAL);
        auto parent = parentList[x][y];
        x = parent.first;
        y = parent.second;
      }
      grid.markPath(endX, endY, END);
      return;
    }

    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        int newX = x + dx;
        int newY = y + dy;

        if (grid.isWalkable(newX, newY) && !visited[newX][newY]) {
          visited[newX][newY] = true;
          q.push({newX, newY});
          parentList[newX][newY] = {x, y};
          grid.markPath(newX, newY, PATH_EXPLORED);
        }
      }
    }

    this_thread::sleep_for(chrono::milliseconds(100));
    window.clear();
    grid.drawGrid(window);
    window.display();
  }

  cout << "No Path Found" << endl;
}
