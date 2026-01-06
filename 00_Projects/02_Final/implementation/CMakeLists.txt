cmake_minimum_required(VERSION 3.16)
project(AirlineReservationSystem VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES
    src/main.cpp
    src/User.cpp
    src/Passenger.cpp
    src/Administrator.cpp
    src/BookingAgent.cpp
    src/Flight.cpp
    src/Aircraft.cpp
    src/Crew.cpp
    src/Reservation.cpp
    src/DatabaseManager.cpp
    src/LoginWindow.cpp
    src/MainWindow.cpp
    src/AdministratorWindow.cpp
    src/BookingAgentWindow.cpp
    src/PassengerWindow.cpp
)

set(HEADERS
    include/User.h
    include/Passenger.h
    include/Administrator.h
    include/BookingAgent.h
    include/Flight.h
    include/Aircraft.h
    include/Crew.h
    include/Reservation.h
    include/DatabaseManager.h
    include/LoginWindow.h
    include/MainWindow.h
    include/AdministratorWindow.h
    include/BookingAgentWindow.h
    include/PassengerWindow.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Widgets)

# Copy data directory to build directory
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
