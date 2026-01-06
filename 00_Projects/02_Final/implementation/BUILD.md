# Build and Setup Guide

## Quick Start

### 1. Install Prerequisites

#### Ubuntu/Debian
```bash
sudo apt update
sudo apt install build-essential cmake qt6-base-dev
```

#### Fedora
```bash
sudo dnf install gcc-c++ cmake qt6-qtbase-devel
```

#### macOS
```bash
brew install cmake qt@6
```

#### Windows
- Install Visual Studio 2019 or later
- Install CMake from https://cmake.org/download/
- Install Qt6 from https://www.qt.io/download-qt-installer

### 2. Clone/Download Project

```bash
cd /path/to/project
cd implementation
```

### 3. Build Project

#### Using CMake (Recommended)

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

#### Using Qt Creator
1. Open CMakeLists.txt in Qt Creator
2. Configure project with Qt6 kit
3. Build (Ctrl+B)
4. Run (Ctrl+R)

### 4. Run Application

```bash
# Linux/macOS
./AirlineReservationSystem

# Windows
AirlineReservationSystem.exe
```

## Detailed Build Instructions

### Linux

```bash
# Navigate to project
cd implementation

# Create build directory
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build
make -j$(nproc)

# Run
./AirlineReservationSystem
```

### macOS

```bash
cd implementation
mkdir build && cd build

# If Qt is installed via Homebrew
cmake .. -DCMAKE_PREFIX_PATH="/usr/local/opt/qt@6"

make -j$(sysctl -n hw.ncpu)
./AirlineReservationSystem
```

### Windows (Visual Studio)

```cmd
cd implementation
mkdir build
cd build

cmake .. -G "Visual Studio 16 2019" -A x64
cmake --build . --config Release

Release\AirlineReservationSystem.exe
```

### Windows (MinGW)

```cmd
cd implementation
mkdir build
cd build

cmake .. -G "MinGW Makefiles"
mingw32-make

AirlineReservationSystem.exe
```

## Troubleshooting

### Qt6 Not Found

**Problem**: CMake can't find Qt6

**Solution**:
```bash
# Set Qt6_DIR to Qt installation
cmake .. -DQt6_DIR="/path/to/Qt/6.x.x/gcc_64/lib/cmake/Qt6"

# Or set CMAKE_PREFIX_PATH
cmake .. -DCMAKE_PREFIX_PATH="/path/to/Qt/6.x.x/gcc_64"
```

### C++17 Not Supported

**Problem**: Compiler doesn't support C++17

**Solution**: Update your compiler
```bash
# Ubuntu
sudo apt install g++-7 or higher

# Check version
g++ --version
```

### Missing Qt Modules

**Problem**: Qt modules not found

**Solution**:
```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev

# Fedora
sudo dnf install qt6-qtbase-devel
```

## Project Structure After Build

```
implementation/
├── build/
│   ├── AirlineReservationSystem    # Executable
│   ├── data/                       # Data directory (copied from source)
│   ├── CMakeFiles/
│   └── ...
├── data/                           # Source data files
├── include/
├── src/
├── CMakeLists.txt
└── README.md
```

## Running Tests

The application initializes with default data for testing:

**Default Credentials**:
- Administrator: `admin` / `admin123`
- Booking Agent: `agent` / `agent123`
- Passenger: `passenger` / `pass123`

## Development Setup

### Using Qt Creator (Recommended for GUI Development)

1. Install Qt Creator
2. Open `CMakeLists.txt`
3. Configure project with Qt6 kit
4. Press "Configure Project"
5. Build and Run

### Using VS Code

1. Install C/C++ extension
2. Install CMake Tools extension
3. Open project folder
4. Configure CMake
5. Build and debug

### CLion

1. Open project (CLion auto-detects CMake)
2. Set CMake options if needed
3. Build and run

## Data Files

The system uses JSON files for data storage located in `data/` directory:

- `users.json` - User accounts
- `flights.json` - Flight schedules
- `aircraft.json` - Aircraft fleet
- `crew.json` - Crew members
- `reservations.json` - Booking records

**Note**: These files are automatically created with default data on first run if they don't exist.

## Clean Build

```bash
cd implementation
rm -rf build
mkdir build && cd build
cmake ..
cmake --build .
```

## Platform-Specific Notes

### Linux
- Ensure Qt6 development packages are installed
- May need to install additional dependencies

### macOS
- Use Homebrew for easy Qt installation
- May need to specify Qt path explicitly

### Windows
- Use Qt's online installer
- Add Qt bin directory to PATH
- Visual Studio or MinGW required

## Performance Optimization

### Release Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Release
```

### Debug Build
```bash
cmake .. -DCMAKE_BUILD_TYPE=Debug
```

## Additional Resources

- Qt Documentation: https://doc.qt.io/qt-6/
- CMake Documentation: https://cmake.org/documentation/
- C++17 Reference: https://en.cppreference.com/

## Support

For build issues:
1. Check Qt6 installation
2. Verify CMake version (3.16+)
3. Ensure C++17 compiler support
4. Review error messages carefully
