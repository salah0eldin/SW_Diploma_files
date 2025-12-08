# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -Iinclude
LDFLAGS = 

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Target executable
TARGET = $(BUILD_DIR)/numeric_demo

# Source files
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(SOURCES:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Main source
MAIN_SRC = main.cpp
MAIN_OBJ = $(OBJ_DIR)/main.o

# All objects
ALL_OBJECTS = $(OBJECTS) $(MAIN_OBJ)

# Default target
all: $(TARGET)

# Create build directories
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Build target executable
$(TARGET): $(OBJ_DIR) $(ALL_OBJECTS)
	@echo "Linking $@..."
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(ALL_OBJECTS) $(LDFLAGS) -o $@
	@echo "Build successful! Run with: ./$(TARGET)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile main
$(MAIN_OBJ): $(MAIN_SRC)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	@echo "Cleaning build artifacts..."
	rm -rf $(BUILD_DIR)
	@echo "Clean complete!"

# Run the program
run: $(TARGET)
	@echo "\nRunning the program:\n"
	@./$(TARGET)

# Rebuild everything
rebuild: clean all

# Help target
help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  clean    - Remove build artifacts"
	@echo "  run      - Build and run the program"
	@echo "  rebuild  - Clean and build"
	@echo "  help     - Show this help message"

.PHONY: all clean run rebuild help
