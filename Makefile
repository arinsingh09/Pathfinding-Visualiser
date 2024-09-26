CXX = g++
CXXFLAGS = -std=c++17 -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
SFML_DIR = /opt/homebrew/Cellar/sfml/2.6.1

# Include SFML library paths
LDFLAGS += -L$(SFML_DIR)/lib -I$(SFML_DIR)/include

SOURCES = main.cpp grid.cpp a_star.cpp dfs.cpp bidirectional.cpp bfs.cpp dijkstra.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = visualizer

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)