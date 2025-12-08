# Configurable Data Processing System in C++

## Project Overview

This is a sophisticated C++ application that demonstrates core C++ concepts including:
- **Object-Oriented Programming (OOP)**: Abstraction, Inheritance, Polymorphism
- **Design Patterns**: Factory Pattern for object creation
- **Standard Template Library (STL)**: `std::map`, `std::vector`, `std::unique_ptr`
- **Templates**: Generic data processing
- **File Handling**: Configuration file parsing
- **Exception Handling**: Robust error management

## Features

1. **Dynamic Configuration Parsing**
   - Reads text-based configuration files
   - Supports nested structures using dot notation (e.g., `Processor.Options.Type`)
   - Dynamically selects processor type based on configuration

2. **Processor Abstraction**
   - Abstract base class `Processor` with virtual methods
   - Four specialized processors:
     - `TextProcessor`: Handles text operations (word count, case conversion)
     - `NumericProcessor`: Performs numeric calculations (sum, average, min, max)
     - `ImageProcessor`: Simulates image processing operations
     - `AudioProcessor`: Simulates audio processing operations

3. **Factory Design Pattern**
   - `ProcessorFactory` creates processor instances dynamically
   - Decouples object creation from application logic

4. **Exception Handling**
   - Handles invalid configurations gracefully
   - Manages missing files and unsupported processor types

## Project Structure

```
ConfigurableProcessor/
├── include/
│   ├── Processor.hpp           # Abstract base class and derived processors
│   ├── ProcessorFactory.hpp    # Factory pattern implementation
│   ├── Configuration.hpp       # Configuration file parser
│   └── Utilities.hpp           # Helper functions
├── src/
│   ├── Processor.cpp           # Processor implementations
│   ├── ProcessorFactory.cpp    # Factory implementation
│   ├── Configuration.cpp       # Configuration parser implementation
│   ├── Utilities.cpp           # Utility functions implementation
│   └── main.cpp                # Main application entry point
├── config/
│   └── settings.txt            # Configuration file
├── Makefile                    # Build system
└── README.md                   # This file
```

## Building the Project

### Prerequisites
- C++ compiler with C++11 support (g++, clang++)
- Make utility

### Compile
```bash
make
```

This will create the executable `ConfigurableProcessor` in the project root directory.

## Running the Project

### Basic Run
```bash
make run
```

### Testing Different Processors

Test with **Text Processor**:
```bash
make test-text
```

Test with **Numeric Processor**:
```bash
make test-numeric
```

Test with **Image Processor**:
```bash
make test-image
```

Test with **Audio Processor**:
```bash
make test-audio
```

### Direct Execution
```bash
./ConfigurableProcessor
```

## Configuration File Format

The `config/settings.txt` file uses a simple key=value format:

```ini
# Comments start with #
Processor.Options.Type=Image
Processor.Options.Threshold=0.5
Processor.Options.MaxRetries=3
```

### Supported Processor Types
- `Text` - Text processing operations
- `Numeric` - Numeric calculations
- `Image` - Image processing simulation
- `Audio` - Audio processing simulation

## Example Output

### Image Processor
```
========================================
  Configurable Data Processing System
========================================

Loading configuration from config/settings.txt...
Selected Processor Type: Image
Configuration Options:
  - Threshold: 0.5
  - Max Retries: 3

Creating processor...
Processor created successfully: ImageProcessor

========================================
  Processing Data
========================================

ImageProcessor: Processing 3 image items
------------------------------------
Image 1: Processing image data: "image001.jpg"
  -> Applying filters to image
  -> Adjusting brightness and contrast
  -> Applying threshold
  -> Image processed successfully
...
```

## Learning Objectives

By studying this project, you will learn:

1. **OOP Principles**
   - Abstraction using abstract base classes
   - Inheritance and polymorphism
   - Virtual functions and dynamic binding

2. **Design Patterns**
   - Factory Pattern for object creation
   - Separation of concerns

3. **STL Usage**
   - `std::map` for key-value storage
   - `std::vector` for collections
   - `std::unique_ptr` for memory management

4. **File I/O**
   - Reading and parsing text files
   - Error handling for file operations

5. **Exception Handling**
   - Using try-catch blocks
   - Throwing and catching standard exceptions
   - Creating robust applications

6. **Build Systems**
   - Writing Makefiles
   - Managing compilation dependencies

## Cleaning Up

Remove compiled files:
```bash
make clean
```

## Extending the Project

### Adding a New Processor

1. **Create the Processor Class** in `include/Processor.hpp`:
   ```cpp
   class VideoProcessor : public Processor {
   public:
       void process(const std::vector<std::string>& data) override;
       void processSingle(const std::string& item) override;
       std::string getType() const override;
   };
   ```

2. **Implement the Processor** in `src/Processor.cpp`:
   ```cpp
   void VideoProcessor::process(const std::vector<std::string>& data) {
       // Implementation
   }
   ```

3. **Update the Factory** in `src/ProcessorFactory.cpp`:
   ```cpp
   if (lowerType == "video") {
       return new VideoProcessor();
   }
   ```

4. **Update Configuration** in `config/settings.txt`:
   ```ini
   Processor.Options.Type=Video
   ```

## Troubleshooting

**Issue**: Compilation errors
- Ensure you have g++ with C++11 support
- Check that all header files are in the `include/` directory

**Issue**: Configuration file not found
- Ensure `config/settings.txt` exists
- Check the file path in `main.cpp`

**Issue**: Unsupported processor type
- Verify the processor type in `settings.txt` is one of: Text, Numeric, Image, Audio
- Check spelling and capitalization (case-insensitive)

## Author

Created as part of the SW Diploma program - Edges For Training

## License

Educational project - Free to use and modify
