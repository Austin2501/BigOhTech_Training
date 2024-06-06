CXX = g++
CXXFLAGS = -std=c++20 -Iinclude
LDFLAGS =

SRC_DIR = src
OBJ_DIR = obj

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))

TARGET = Day5

all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(OBJ_DIR)/main.o
	$(CXX) $(LDFLAGS) -o $@ $(OBJ_FILES) $(OBJ_DIR)/main.o

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OBJ_DIR)/main.o: main.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
