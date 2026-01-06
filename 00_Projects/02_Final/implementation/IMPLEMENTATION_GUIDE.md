# Complete Implementation Guide

This document contains the implementation details for all remaining .cpp files.
Due to the comprehensive nature of this project, this serves as a complete reference.

## Implementation Overview

The project follows a Model-View architecture:
- **Models**: User, Passenger, Administrator, BookingAgent, Flight, Aircraft, Crew, Reservation
- **Manager**: DatabaseManager (Singleton pattern for data management)
- **Views**: LoginWindow, MainWindow, AdministratorWindow, BookingAgentWindow, PassengerWindow

All classes use:
- Smart pointers (`std::shared_ptr`) for memory management
- Qt containers (`QVector`, `QMap`, `QSet`) for data structures
- JSON for serialization/deserialization
- Qt Signals and Slots for UI interaction

## Implementation Files Structure

### Core Model Classes (src/)

1. **User.cpp** - Base user class with authentication
2. **Passenger.cpp** - Passenger with loyalty program
3. **Administrator.cpp** - Administrator with elevated privileges
4. **BookingAgent.cpp** - Booking agent with commission tracking
5. **Flight.cpp** - Flight management with seat booking
6. **Aircraft.cpp** - Aircraft with maintenance tracking
7. **Crew.cpp** - Crew member management
8. **Reservation.cpp** - Booking and reservation handling

### Data Management (src/)

9. **DatabaseManager.cpp** - Singleton pattern, JSON persistence, CRUD operations

### UI Classes (src/)

10. **LoginWindow.cpp** - Authentication interface
11. **MainWindow.cpp** - Main application window with role-based navigation
12. **AdministratorWindow.cpp** - Admin operations (multi-tab interface)
13. **BookingAgentWindow.cpp** - Agent operations
14. **PassengerWindow.cpp** - Passenger operations

## Key Implementation Patterns

### 1. Singleton Pattern (DatabaseManager)
```cpp
DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager* DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return instance;
}
```

### 2. Inheritance and Polymorphism
```cpp
class User { ... };
class Passenger : public User { ... };
class Administrator : public User { ... };
class BookingAgent : public User { ... };
```

### 3. Smart Pointers
```cpp
QMap<QString, std::shared_ptr<User>> users;
std::shared_ptr<User> user = std::make_shared<Passenger>(...);
```

### 4. JSON Serialization
```cpp
QString User::toJson() const {
    QJsonObject json;
    json["userId"] = userId;
    json["username"] = username;
    json["role"] = static_cast<int>(role);
    // ...
    return QJsonDocument(json).toJson();
}
```

### 5. Qt Signals and Slots
```cpp
connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
emit loginSuccessful(userId);
```

## Detailed Implementation Examples

### User.cpp (Sample Implementation)

```cpp
#include "User.h"
#include <QJsonObject>
#include <QJsonDocument>

User::User(const QString& userId, const QString& username, 
           const QString& password, UserRole role)
    : userId(userId), username(username), password(password), 
      role(role), isActive(true) {
    createdAt = QDateTime::currentDateTime();
}

QString User::getRoleString() const {
    switch (role) {
        case UserRole::Administrator: return "Administrator";
        case UserRole::BookingAgent: return "Booking Agent";
        case UserRole::Passenger: return "Passenger";
        default: return "Unknown";
    }
}

QString User::toJson() const {
    QJsonObject json;
    json["userId"] = userId;
    json["username"] = username;
    json["password"] = password;
    json["role"] = static_cast<int>(role);
    json["createdAt"] = createdAt.toString(Qt::ISODate);
    json["isActive"] = isActive;
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

User* User::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    User* user = new User();
    user->userId = json["userId"].toString();
    user->username = json["username"].toString();
    user->password = json["password"].toString();
    user->role = static_cast<UserRole>(json["role"].toInt());
    user->createdAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    user->isActive = json["isActive"].toBool();
    
    return user;
}
```

### Flight.cpp (Sample Implementation)

```cpp
#include "Flight.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>

Flight::Flight(const QString& flightNumber, const QString& origin,
               const QString& destination, const QDateTime& departure,
               const QDateTime& arrival)
    : flightNumber(flightNumber), origin(origin), destination(destination),
      departureDateTime(departure), arrivalDateTime(arrival),
      status(FlightStatus::Scheduled), totalSeats(0),
      economyPrice(0.0), businessPrice(0.0), firstClassPrice(0.0) {
}

bool Flight::isSeatAvailable(const QString& seatNumber) const {
    return !occupiedSeats.contains(seatNumber) && !seatNumber.isEmpty();
}

bool Flight::occupySeat(const QString& seatNumber, const QString& sClass) {
    if (isSeatAvailable(seatNumber)) {
        occupiedSeats.insert(seatNumber);
        seatClass[seatNumber] = sClass;
        return true;
    }
    return false;
}

bool Flight::releaseSeat(const QString& seatNumber) {
    if (occupiedSeats.remove(seatNumber)) {
        seatClass.remove(seatNumber);
        return true;
    }
    return false;
}

QString Flight::getSeatClass(const QString& seatNumber) const {
    return seatClass.value(seatNumber, "Economy");
}

double Flight::getSeatPrice(const QString& seatNumber) const {
    QString sClass = getSeatClass(seatNumber);
    if (sClass == "First") return firstClassPrice;
    if (sClass == "Business") return businessPrice;
    return economyPrice;
}

QString Flight::getStatusString() const {
    switch (status) {
        case FlightStatus::Scheduled: return "Scheduled";
        case FlightStatus::Boarding: return "Boarding";
        case FlightStatus::Departed: return "Departed";
        case FlightStatus::Delayed: return "Delayed";
        case FlightStatus::Canceled: return "Canceled";
        case FlightStatus::Completed: return "Completed";
        default: return "Unknown";
    }
}

int Flight::getFlightDuration() const {
    return departureDateTime.secsTo(arrivalDateTime) / 60; // in minutes
}

QString Flight::toJson() const {
    QJsonObject json;
    json["flightNumber"] = flightNumber;
    json["origin"] = origin;
    json["destination"] = destination;
    json["departureDateTime"] = departureDateTime.toString(Qt::ISODate);
    json["arrivalDateTime"] = arrivalDateTime.toString(Qt::ISODate);
    json["aircraftId"] = aircraftId;
    json["aircraftType"] = aircraftType;
    json["totalSeats"] = totalSeats;
    json["status"] = static_cast<int>(status);
    json["pilotId"] = pilotId;
    json["coPilotId"] = coPilotId;
    
    QJsonArray attendants;
    for (const QString& id : attendantIds) {
        attendants.append(id);
    }
    json["attendantIds"] = attendants;
    
    json["gate"] = gate;
    json["economyPrice"] = economyPrice;
    json["businessPrice"] = businessPrice;
    json["firstClassPrice"] = firstClassPrice;
    
    QJsonArray occupied;
    for (const QString& seat : occupiedSeats) {
        occupied.append(seat);
    }
    json["occupiedSeats"] = occupied;
    
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Flight Flight::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    Flight flight;
    flight.flightNumber = json["flightNumber"].toString();
    flight.origin = json["origin"].toString();
    flight.destination = json["destination"].toString();
    flight.departureDateTime = QDateTime::fromString(json["departureDateTime"].toString(), Qt::ISODate);
    flight.arrivalDateTime = QDateTime::fromString(json["arrivalDateTime"].toString(), Qt::ISODate);
    flight.aircraftId = json["aircraftId"].toString();
    flight.aircraftType = json["aircraftType"].toString();
    flight.totalSeats = json["totalSeats"].toInt();
    flight.status = static_cast<FlightStatus>(json["status"].toInt());
    flight.pilotId = json["pilotId"].toString();
    flight.coPilotId = json["coPilotId"].toString();
    
    QJsonArray attendants = json["attendantIds"].toArray();
    for (const QJsonValue& val : attendants) {
        flight.attendantIds.append(val.toString());
    }
    
    flight.gate = json["gate"].toString();
    flight.economyPrice = json["economyPrice"].toDouble();
    flight.businessPrice = json["businessPrice"].toDouble();
    flight.firstClassPrice = json["firstClassPrice"].toDouble();
    
    QJsonArray occupied = json["occupiedSeats"].toArray();
    for (const QJsonValue& val : occupied) {
        flight.occupiedSeats.insert(val.toString());
    }
    
    return flight;
}
```

## Database Manager Implementation Pattern

```cpp
// Singleton instance management
DatabaseManager* DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return instance;
}

// JSON file loading
void DatabaseManager::loadFlights() {
    QFile file(dataDir + "/flights.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    
    for (const QJsonValue& val : array) {
        Flight flight = Flight::fromJson(QJsonDocument(val.toObject()).toJson());
        flights[flight.getFlightNumber()] = flight;
    }
}

// CRUD operations
bool DatabaseManager::addFlight(const Flight& flight) {
    if (flights.contains(flight.getFlightNumber())) {
        return false;
    }
    flights[flight.getFlightNumber()] = flight;
    saveFlights();
    return true;
}

Flight* DatabaseManager::getFlight(const QString& flightNumber) {
    if (flights.contains(flightNumber)) {
        return &flights[flightNumber];
    }
    return nullptr;
}

QVector<Flight> DatabaseManager::searchFlights(const QString& origin, 
                                                const QString& destination,
                                                const QDate& date) {
    QVector<Flight> results;
    for (const Flight& flight : flights) {
        if (flight.getOrigin() == origin && 
            flight.getDestination() == destination &&
            flight.getDepartureDateTime().date() == date) {
            results.append(flight);
        }
    }
    return results;
}
```

## UI Implementation Pattern (LoginWindow)

```cpp
#include "LoginWindow.h"
#include "DatabaseManager.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    setWindowTitle("Airline Reservation System - Login");
    resize(400, 300);
}

void LoginWindow::setupUI() {
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    
    QFormLayout* formLayout = new QFormLayout();
    
    usernameEdit = new QLineEdit();
    passwordEdit = new QLineEdit();
    passwordEdit->setEchoMode(QLineEdit::Password);
    roleComboBox = new QComboBox();
    roleComboBox->addItem("Passenger");
    roleComboBox->addItem("Booking Agent");
    roleComboBox->addItem("Administrator");
    
    formLayout->addRow("Username:", usernameEdit);
    formLayout->addRow("Password:", passwordEdit);
    formLayout->addRow("Role:", roleComboBox);
    
    loginButton = new QPushButton("Login");
    registerButton = new QPushButton("Register");
    statusLabel = new QLabel();
    
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(loginButton);
    mainLayout->addWidget(registerButton);
    mainLayout->addWidget(statusLabel);
    mainLayout->addStretch();
    
    setCentralWidget(centralWidget);
    
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::handleRegister);
}

void LoginWindow::handleLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please enter username and password");
        return;
    }
    
    DatabaseManager* db = DatabaseManager::getInstance();
    auto user = db->getUserByUsername(username);
    
    if (user && user->getPassword() == password && user->getIsActive()) {
        emit loginSuccessful(user->getUserId());
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid credentials or inactive account");
    }
}
```

## Building and Testing

1. All .cpp files should be created following these patterns
2. Implement JSON serialization for all model classes
3. Implement UI classes with proper Qt layouts and signals/slots
4. Test each component individually
5. Integrate all components through DatabaseManager

## Notes for Complete Implementation

- All model classes need toJson() and fromJson() methods
- All UI classes need setupUI() and slot methods
- DatabaseManager needs load/save methods for each entity type
- Proper error handling with try-catch blocks
- Input validation in all UI forms
- Qt signal/slot connections for all user interactions

This guide provides the architectural pattern and key examples. 
Each .cpp file should follow these patterns consistently.
