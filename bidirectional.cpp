#include "bidirectional.h"

using namespace std;

void bidirectionalSearch(Grid& grid, sf::RenderWindow& window) {
  int rows = grid.getRows();
  int cols = grid.getCols();

  vector<vector<bool>> visitedFromStart(rows, vector<bool>(cols, false));
  vector<vector<bool>> visitedFromEnd(rows, vector<bool>(cols, false));
  vector<vector<pair<int, int>>> parentListFromStart(
      rows, vector<pair<int, int>>(cols, {-1, -1}));
  vector<vector<pair<int, int>>> parentListFromEnd(
      rows, vector<pair<int, int>>(cols, {-1, -1}));

  int startX = grid.getStartX(), startY = grid.getStartY();
  int endX = grid.getEndX(), endY = grid.getEndY();

  queue<pair<int, int>> qStart, qEnd;
  qStart.push({startX, startY});
  qEnd.push({endX, endY});
  visitedFromStart[startX][startY] = true;
  visitedFromEnd[endX][endY] = true;

  pair<int, int> meetingPoint;

  while (!qStart.empty() && !qEnd.empty()) {
    // Expand from start
    auto [xStart, yStart] = qStart.front();
    qStart.pop();

    if (visitedFromEnd[xStart][yStart]) {
      meetingPoint = {xStart, yStart};
      break;
    }

    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        int newX = xStart + dx;
        int newY = yStart + dy;
        if (grid.isWalkable(newX, newY) && !visitedFromStart[newX][newY]) {
          visitedFromStart[newX][newY] = true;
          qStart.push({newX, newY});
          parentListFromStart[newX][newY] = {xStart, yStart};
          grid.markPath(newX, newY, PATH_EXPLORED);

          this_thread::sleep_for(chrono::milliseconds(100));
          window.clear();
          grid.drawGrid(window);
          window.display();
        }
      }
    }

    // Expand from end
    auto [xEnd, yEnd] = qEnd.front();
    qEnd.pop();

    if (visitedFromStart[xEnd][yEnd]) {
      meetingPoint = {xEnd, yEnd};
      break;
    }

    for (int dx = -1; dx <= 1; ++dx) {
      for (int dy = -1; dy <= 1; ++dy) {
        int newX = xEnd + dx, newY = yEnd + dy;
        if (grid.isWalkable(newX, newY) && !visitedFromEnd[newX][newY]) {
          visitedFromEnd[newX][newY] = true;
          qEnd.push({newX, newY});
          parentListFromEnd[newX][newY] = {xEnd, yEnd};
          grid.markPath(newX, newY, PATH_EXPLORED);

          this_thread::sleep_for(chrono::milliseconds(100));
          window.clear();
          grid.drawGrid(window);
          window.display();
        }
      }
    }
  }

  // Mark the final path
  if (!qStart.empty() || !qEnd.empty()) {
    // Backtrack from start to meeting point
    int currX = meetingPoint.first, currY = meetingPoint.second;
    while (make_pair(currX, currY) != make_pair(startX, startY)) {
      grid.markPath(currX, currY, PATH_FINAL);
      auto parent = parentListFromStart[currX][currY];
      currX = parent.first;
      currY = parent.second;
    }
    grid.markPath(startX, startY, START);

    // Backtrack from end to meeting point
    currX = meetingPoint.first;
    currY = meetingPoint.second;
    while (make_pair(currX, currY) != make_pair(endX, endY)) {
      grid.markPath(currX, currY, PATH_FINAL);
      auto parent = parentListFromEnd[currX][currY];
      currX = parent.first;
      currY = parent.second;
    }
    grid.markPath(endX, endY, END);

    cout << "Path found!" << endl;
  } else {
    cout << "No path found." << endl;
  }
}
