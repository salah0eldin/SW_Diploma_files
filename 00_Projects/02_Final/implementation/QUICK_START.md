# Quick Start Guide

## For Developers - Implementation Quick Reference

### 1. Build the Project (First Time)

```bash
cd implementation
mkdir build && cd build
cmake ..
make
```

### 2. Project Files Overview

**Headers (include/)**:
- User hierarchy: User.h → Passenger.h, Administrator.h, BookingAgent.h
- Business objects: Flight.h, Aircraft.h, Crew.h, Reservation.h
- Manager: DatabaseManager.h (Singleton)
- UI: LoginWindow.h, MainWindow.h, [Role]Window.h

**Implementation (src/)**: Create corresponding .cpp files

**Data (data/)**: JSON files (auto-loaded on startup)

### 3. Implementation Order

```
1. Model Classes
   └─ User.cpp → Passenger.cpp, Administrator.cpp, BookingAgent.cpp
   └─ Flight.cpp, Aircraft.cpp, Crew.cpp, Reservation.cpp

2. Data Manager
   └─ DatabaseManager.cpp (Singleton + JSON I/O)

3. UI Classes
   └─ LoginWindow.cpp
   └─ MainWindow.cpp
   └─ AdministratorWindow.cpp, BookingAgentWindow.cpp, PassengerWindow.cpp
```

### 4. Essential Code Patterns

**JSON Serialization**:
```cpp
QString MyClass::toJson() const {
    QJsonObject json;
    json["field1"] = value1;
    json["field2"] = value2;
    return QJsonDocument(json).toJson();
}

MyClass MyClass::fromJson(const QString& jsonStr) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonStr.toUtf8());
    QJsonObject json = doc.object();
    MyClass obj;
    obj.field1 = json["field1"].toString();
    obj.field2 = json["field2"].toInt();
    return obj;
}
```

**Qt UI Setup**:
```cpp
void MyWindow::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout();
    QPushButton* button = new QPushButton("Click Me");
    layout->addWidget(button);
    
    connect(button, &QPushButton::clicked, this, &MyWindow::onButtonClicked);
    
    setLayout(layout);
}
```

**DatabaseManager Usage**:
```cpp
DatabaseManager* db = DatabaseManager::getInstance();
Flight* flight = db->getFlight("AA123");
db->addReservation(reservation);
db->saveAll();
```

### 5. Testing Credentials

| Role | Username | Password |
|------|----------|----------|
| Admin | admin | admin123 |
| Agent | agent | agent123 |
| Passenger | passenger | pass123 |

### 6. Key Qt Includes

```cpp
// Core
#include <QString>
#include <QDateTime>
#include <QVector>
#include <QMap>
#include <QSet>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

// Widgets
#include <QWidget>
#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
```

### 7. Common Tasks

**Add a new flight**:
```cpp
Flight flight("AA100", "NYC", "LAX", depTime, arrTime);
flight.setAircraftId("AC001");
flight.setEconomyPrice(350.0);
DatabaseManager::getInstance()->addFlight(flight);
```

**Search flights**:
```cpp
QVector<Flight> results = db->searchFlights("NYC", "LAX", QDate(2025, 12, 15));
```

**Create reservation**:
```cpp
Reservation res("R123", "P456", "John Doe", "AA123", "12A");
res.setTotalCost(350.0);
res.setPaymentMethod(PaymentMethod::CreditCard);
db->addReservation(res);
```

**Check-in**:
```cpp
Reservation* res = db->getReservation("R123");
if (res) {
    res->checkIn();
    QString boardingPass = res->getBoardingPass();
}
```

### 8. File Locations

```
implementation/
├── CMakeLists.txt          ← Build config
├── README.md               ← Full documentation
├── BUILD.md                ← Build instructions
├── FEATURES.md             ← Feature list
├── IMPLEMENTATION_GUIDE.md ← Code patterns
├── PROJECT_OVERVIEW.md     ← Architecture
├── QUICK_START.md          ← This file
├── data/*.json             ← Data files
├── include/*.h             ← Headers (15 files)
└── src/*.cpp               ← Implementations (to create)
```

### 9. Documentation Files

- **README.md** - User guide, features, usage
- **BUILD.md** - Platform-specific build instructions  
- **FEATURES.md** - Complete feature documentation
- **IMPLEMENTATION_GUIDE.md** - Code patterns and examples
- **PROJECT_OVERVIEW.md** - Architecture and status
- **QUICK_START.md** - This quick reference

### 10. Debugging Tips

**Qt Creator**:
- Open CMakeLists.txt
- Configure with Qt6 kit
- Build → Run

**Command Line**:
```bash
# Debug build
cmake .. -DCMAKE_BUILD_TYPE=Debug
make
gdb ./AirlineReservationSystem

# Check data files
cat data/users.json | jq .
```

**Common Issues**:
- Qt6 not found → Set CMAKE_PREFIX_PATH
- C++17 not supported → Update compiler
- JSON parse error → Validate JSON files

### 11. Adding New Features

1. Add method to header file
2. Implement in .cpp file
3. Update DatabaseManager if needed
4. Add UI controls if needed
5. Test thoroughly
6. Update documentation

### 12. Code Quality Checklist

- [ ] All pointers use smart pointers
- [ ] All strings use QString
- [ ] JSON serialization implemented
- [ ] Error handling with try-catch
- [ ] Input validation
- [ ] Qt naming conventions
- [ ] Comments for complex logic
- [ ] Memory leaks checked

---

**Quick Links**:
- Full Docs → README.md
- Build Help → BUILD.md
- Features → FEATURES.md
- Code Examples → IMPLEMENTATION_GUIDE.md
- Architecture → PROJECT_OVERVIEW.md

**Status**: Complete architecture, ready for implementation  
**Last Updated**: December 31, 2025
