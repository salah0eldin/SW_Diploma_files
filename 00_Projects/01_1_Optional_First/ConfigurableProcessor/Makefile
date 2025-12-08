# Makefile for Configurable Data Processing System
# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = .

# Source files
SRC = $(SRC_DIR)/Processor.cpp \
      $(SRC_DIR)/ProcessorFactory.cpp \
      $(SRC_DIR)/Configuration.cpp \
      $(SRC_DIR)/Utilities.cpp \
      $(SRC_DIR)/main.cpp

# Object files
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Target executable
TARGET = $(BIN_DIR)/ConfigurableProcessor

# Default target
all: $(TARGET)

# Create object directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link object files to create executable
$(TARGET): $(OBJ) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -o $@ $^
	@echo "Build successful! Executable: $(TARGET)"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the program
run: $(TARGET)
	@echo "Running ConfigurableProcessor..."
	@echo ""
	@./$(TARGET)

# Clean build artifacts
clean:
	rm -rf $(OBJ_DIR) $(TARGET)
	@echo "Clean complete"

# Run with Text processor
test-text:
	@echo "Processor.Options.Type=Text" > config/settings.txt
	@echo "Processor.Options.Threshold=0.5" >> config/settings.txt
	@echo "Processor.Options.MaxRetries=3" >> config/settings.txt
	@$(MAKE) run

# Run with Numeric processor
test-numeric:
	@echo "Processor.Options.Type=Numeric" > config/settings.txt
	@echo "Processor.Options.Threshold=0.5" >> config/settings.txt
	@echo "Processor.Options.MaxRetries=3" >> config/settings.txt
	@$(MAKE) run

# Run with Image processor
test-image:
	@echo "Processor.Options.Type=Image" > config/settings.txt
	@echo "Processor.Options.Threshold=0.5" >> config/settings.txt
	@echo "Processor.Options.MaxRetries=3" >> config/settings.txt
	@$(MAKE) run

# Run with Audio processor
test-audio:
	@echo "Processor.Options.Type=Audio" > config/settings.txt
	@echo "Processor.Options.Threshold=0.5" >> config/settings.txt
	@echo "Processor.Options.MaxRetries=3" >> config/settings.txt
	@$(MAKE) run

# Help target
help:
	@echo "Available targets:"
	@echo "  make          - Build the project"
	@echo "  make run      - Build and run the program"
	@echo "  make clean    - Remove build artifacts"
	@echo "  make test-text     - Test with Text processor"
	@echo "  make test-numeric  - Test with Numeric processor"
	@echo "  make test-image    - Test with Image processor"
	@echo "  make test-audio    - Test with Audio processor"
	@echo "  make help     - Show this help message"

.PHONY: all run clean test-text test-numeric test-image test-audio help
