# Airline Reservation and Management System

## Overview
A comprehensive Qt-based C++ application for managing airline operations, including flight scheduling, aircraft management, crew assignment, booking system, passenger management, check-in procedures, and maintenance tracking.

## Features

### 1. User Roles and Authentication
- **Administrator**: Full system access for managing flights, aircraft, users, and generating reports
- **Booking Agent**: Search flights, create/modify/cancel reservations, process payments
- **Passenger**: Search flights, book tickets, check-in online, view travel history, manage loyalty points

### 2. Flight Management
- Add, update, and remove flights with detailed information
- Assign crew (pilots, co-pilots, flight attendants) to flights
- Real-time flight status updates (Scheduled, Boarding, Departed, Delayed, Canceled, Completed)
- Gate assignment and boarding management

### 3. Aircraft Management
- Track aircraft specifications and fleet information
- Maintenance scheduling and tracking
- Aircraft availability status
- Flight hours logging

### 4. Booking System
- Advanced flight search by origin, destination, and date
- Interactive seat selection with class-based pricing (Economy, Business, First Class)
- Reservation creation, modification, and cancellation
- Multiple payment methods (Credit Card, Debit Card, Cash, PayPal)
- Refund processing for canceled bookings

### 5. Passenger Management
- Comprehensive passenger profiles
- Travel history tracking
- Loyalty points program
- Personalized booking experience

### 6. Check-In System
- Online check-in with boarding pass generation
- Reservation validation
- Seat confirmation

### 7. Crew Management
- Pilot and flight attendant assignment
- Flight hours tracking and regulation compliance
- Crew availability management

### 8. Maintenance Tracking
- Scheduled maintenance for aircraft
- Maintenance logs and history
- Aircraft status updates

### 9. Reporting and Analytics
- Operational reports (flight performance, statistics)
- Maintenance reports
- User activity reports
- Financial summaries

### 10. Data Persistence
- JSON-based file storage
- Automatic data loading and saving
- Data integrity and validation

## Project Structure

```
implementation/
├── CMakeLists.txt          # CMake build configuration
├── README.md               # This file
├── data/                   # JSON data files
│   ├── users.json
│   ├── flights.json
│   ├── aircraft.json
│   ├── crew.json
│   └── reservations.json
├── include/                # Header files
│   ├── User.h
│   ├── Passenger.h
│   ├── Administrator.h
│   ├── BookingAgent.h
│   ├── Flight.h
│   ├── Aircraft.h
│   ├── Crew.h
│   ├── Reservation.h
│   ├── DatabaseManager.h
│   ├── LoginWindow.h
│   ├── MainWindow.h
│   ├── AdministratorWindow.h
│   ├── BookingAgentWindow.h
│   └── PassengerWindow.h
└── src/                    # Implementation files
    ├── main.cpp
    ├── User.cpp
    ├── Passenger.cpp
    ├── Administrator.cpp
    ├── BookingAgent.cpp
    ├── Flight.cpp
    ├── Aircraft.cpp
    ├── Crew.cpp
    ├── Reservation.cpp
    ├── DatabaseManager.cpp
    ├── LoginWindow.cpp
    ├── MainWindow.cpp
    ├── AdministratorWindow.cpp
    ├── BookingAgentWindow.cpp
    └── PassengerWindow.cpp
```

## Technologies Used

- **C++17**: Modern C++ features including smart pointers, STL containers, lambda expressions
- **Qt6**: Cross-platform GUI framework (Core and Widgets modules)
- **CMake**: Build system
- **JSON**: Data persistence format

## Prerequisites

- C++ compiler with C++17 support (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.16 or higher
- Qt6 (Core and Widgets modules)

## Building the Project

### Linux/macOS

```bash
cd implementation
mkdir build
cd build
cmake ..
make
./AirlineReservationSystem
```

### Windows

```bash
cd implementation
mkdir build
cd build
cmake ..
cmake --build . --config Release
Release\AirlineReservationSystem.exe
```

## Default Users

The system comes with pre-configured default users for testing:

| Role | Username | Password |
|------|----------|----------|
| Administrator | admin | admin123 |
| Booking Agent | agent | agent123 |
| Passenger | passenger | pass123 |

## Usage Guide

### For Administrators

1. **Manage Flights**
   - Add new flights with flight number, origin, destination, times, aircraft
   - Update existing flight information
   - Delete flights
   - Assign crew members (pilots and attendants)

2. **Manage Aircraft**
   - Add aircraft to the fleet
   - Schedule and track maintenance
   - Monitor aircraft availability and flight hours

3. **Manage Users**
   - Create new user accounts (Admin, Agent, Passenger)
   - Update user information
   - Deactivate/delete users

4. **Generate Reports**
   - Operational reports: Flight statistics, on-time performance
   - Maintenance reports: Aircraft service history
   - User activity reports: Booking patterns and user engagement

### For Booking Agents

1. **Search Flights**
   - Search by origin, destination, and date
   - View available seats and pricing

2. **Book Flights**
   - Enter passenger information
   - Select seats and process payments
   - Generate booking confirmations

3. **Manage Reservations**
   - View all reservations
   - Modify existing bookings
   - Cancel reservations and process refunds

### For Passengers

1. **Search and Book**
   - Search for available flights
   - Select preferred seats
   - Complete booking with payment

2. **My Reservations**
   - View all current and past bookings
   - View booking details and status

3. **Check-In**
   - Online check-in 24 hours before departure
   - View and print boarding pass

4. **Profile**
   - View loyalty points
   - Track travel history
   - Update personal information

## Key Classes and Architecture

### Model Classes (OOP)

- **User** (Base class): Common user properties and authentication
  - **Passenger**: Inherits User, adds loyalty program and travel history
  - **Administrator**: Inherits User, adds department and access level
  - **BookingAgent**: Inherits User, adds agency information and commissions

- **Flight**: Flight scheduling, crew assignment, seat management
- **Aircraft**: Fleet management, maintenance tracking
- **Crew**: Crew member information and availability
- **Reservation**: Booking details, payment, check-in status

### Manager Classes

- **DatabaseManager** (Singleton): 
  - Centralized data management
  - JSON serialization/deserialization
  - CRUD operations for all entities
  - Data validation and integrity

### UI Classes (Qt Widgets)

- **LoginWindow**: User authentication interface
- **MainWindow**: Main application window with role-based navigation
- **AdministratorWindow**: Admin-specific operations (tabs for flights, aircraft, users, reports)
- **BookingAgentWindow**: Agent operations (search, book, manage reservations)
- **PassengerWindow**: Passenger operations (search/book, reservations, check-in, profile)

## Modern C++ Features Used

1. **Smart Pointers**: `std::shared_ptr<User>` for automatic memory management
2. **STL Containers**:
   - `QVector` / `std::vector` for lists
   - `QMap` / `std::map` for key-value storage
   - `QSet` / `std::set` for unique collections
3. **Lambda Expressions**: For sorting, filtering, and custom operations
4. **Enumerations**: Type-safe enums for roles, statuses, payment methods
5. **Inheritance and Polymorphism**: User hierarchy, virtual functions
6. **RAII**: Resource management through constructors/destructors

## Data Persistence

All data is stored in JSON format in the `data/` directory:
- **users.json**: All user accounts
- **flights.json**: Flight schedules and information
- **aircraft.json**: Fleet information
- **crew.json**: Crew member details
- **reservations.json**: All bookings and reservations

Data is automatically loaded on startup and saved on exit or after modifications.

## Error Handling

The system implements comprehensive error handling:
- Input validation for all user entries
- Exception handling with try-catch blocks
- User-friendly error messages
- Data integrity checks
- Graceful failure recovery

## Future Enhancements

1. **Multi-threading**: Concurrent booking processing with `std::thread` and `std::mutex`
2. **Real-time Notifications**: Qt signals/slots for flight status updates
3. **Advanced Analytics**: Data visualization with Qt Charts
4. **API Integration**: Real-time weather, flight tracking APIs
5. **Database Backend**: Migration to SQLite or PostgreSQL
6. **Web Interface**: REST API and web dashboard

## License

This project is created for educational purposes as part of the Software Engineering Diploma program.

## Authors

Software Engineering Diploma - Final Project

## Support

For issues, questions, or contributions, please refer to the project documentation or contact the development team.
