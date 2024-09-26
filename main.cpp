#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>

#include "a_star.h"
#include "bfs.h"
#include "bidirectional.h"
#include "dfs.h"
#include "dijkstra.h"
#include "grid.h"

using namespace std;

void visualizeAlgorithm(Grid& grid, int algorithmChoice) {
  const int windowWidth = 800;
  const int windowHeight = 800;
  sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight),
                          "Pathfinding Visualizer");

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    window.clear();
    grid.drawGrid(window);
    window.display();

    this_thread::sleep_for(chrono::milliseconds(1000));

    /* Performance Analysis
    auto start = chrono::high_resolution_clock::now();
    */

    switch (algorithmChoice) {
      case 1:
        dijkstra(grid, window);
        break;
      case 2:
        aStar(grid, window);
        break;
      case 3:
        bfs(grid, window);
        break;
      case 4:
        dfs(grid, window);
        break;
      case 5:
        bidirectionalSearch(grid, window);
        break;
      default:
        break;
    }
    /* Performance Analysis
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Algorithm execution time: " << duration.count() << " seconds"
         << endl;
    this_thread::sleep_for(chrono::seconds(10));
    */
  }
}

int main() {
  int rows, cols;
  cout << "Enter the grid size (rows and columns): ";
  cin >> rows >> cols;

  Grid grid(rows, cols);

  int startX, startY, endX, endY;
  cout << "Enter Start Point (x y): ";
  cin >> startX >> startY;
  grid.setStart(startX, startY);

  cout << "Enter End Point (x y): ";
  cin >> endX >> endY;
  grid.setEnd(endX, endY);

  char generateMaze;
  cout << "Do you want to generate a random maze? (y/n): ";
  cin >> generateMaze;

  if (generateMaze == 'y') {
    grid.generateRandomMaze();
  }

  int algorithmChoice;
  cout << "Choose Algorithm:\n1 - Dijkstra\n2 - A*\n3 - BFS\n4 - DFS\n5 - "
          "Bidirectional\n";
  cin >> algorithmChoice;

  visualizeAlgorithm(grid, algorithmChoice);

  return 0;
}