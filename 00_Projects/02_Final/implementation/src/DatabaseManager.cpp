#include "DatabaseManager.h"
#include "Passenger.h"
#include "Administrator.h"
#include "BookingAgent.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QDir>
#include <QCoreApplication>

DatabaseManager* DatabaseManager::instance = nullptr;

DatabaseManager::DatabaseManager() {
    dataDir = QCoreApplication::applicationDirPath() + "/data";
    QDir dir;
    if (!dir.exists(dataDir)) {
        dir.mkpath(dataDir);
    }
}

DatabaseManager* DatabaseManager::getInstance() {
    if (!instance) {
        instance = new DatabaseManager();
    }
    return instance;
}

DatabaseManager::~DatabaseManager() {
    saveAll();
}

void DatabaseManager::loadAll() {
    loadUsers();
    loadFlights();
    loadAircraft();
    loadCrew();
    loadReservations();
}

void DatabaseManager::saveAll() {
    saveUsers();
    saveFlights();
    saveAircraft();
    saveCrew();
    saveReservations();
}

void DatabaseManager::loadUsers() {
    QFile file(dataDir + "/users.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    
    for (const QJsonValue& val : array) {
        QJsonObject json = val.toObject();
        QString type = json["type"].toString();
        
        std::shared_ptr<User> user;
        if (type == "Passenger") {
            user = std::shared_ptr<User>(Passenger::fromJson(QJsonDocument(json).toJson()));
            passengers[user->getUserId()] = std::static_pointer_cast<Passenger>(user);
        } else if (type == "Administrator") {
            user = std::shared_ptr<User>(Administrator::fromJson(QJsonDocument(json).toJson()));
            administrators[user->getUserId()] = std::static_pointer_cast<Administrator>(user);
        } else if (type == "BookingAgent") {
            user = std::shared_ptr<User>(BookingAgent::fromJson(QJsonDocument(json).toJson()));
            bookingAgents[user->getUserId()] = std::static_pointer_cast<BookingAgent>(user);
        }
        if (user) {
            users[user->getUserId()] = user;
        }
    }
}

void DatabaseManager::saveUsers() {
    QJsonArray array;
    for (auto it = users.begin(); it != users.end(); ++it) {
        QJsonDocument doc = QJsonDocument::fromJson(it.value()->toJson().toUtf8());
        array.append(doc.object());
    }
    
    QFile file(dataDir + "/users.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void DatabaseManager::loadFlights() {
    QFile file(dataDir + "/flights.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    
    for (const QJsonValue& val : array) {
        Flight flight = Flight::fromJson(QJsonDocument(val.toObject()).toJson());
        flights[flight.getFlightNumber()] = flight;
    }
}

void DatabaseManager::saveFlights() {
    QJsonArray array;
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        QJsonDocument doc = QJsonDocument::fromJson(it.value().toJson().toUtf8());
        array.append(doc.object());
    }
    
    QFile file(dataDir + "/flights.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void DatabaseManager::loadAircraft() {
    QFile file(dataDir + "/aircraft.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    
    for (const QJsonValue& val : array) {
        Aircraft ac = Aircraft::fromJson(QJsonDocument(val.toObject()).toJson());
        aircraft[ac.getAircraftId()] = ac;
    }
}

void DatabaseManager::saveAircraft() {
    QJsonArray array;
    for (auto it = aircraft.begin(); it != aircraft.end(); ++it) {
        QJsonDocument doc = QJsonDocument::fromJson(it.value().toJson().toUtf8());
        array.append(doc.object());
    }
    
    QFile file(dataDir + "/aircraft.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void DatabaseManager::loadCrew() {
    QFile file(dataDir + "/crew.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    
    for (const QJsonValue& val : array) {
        Crew crew = Crew::fromJson(QJsonDocument(val.toObject()).toJson());
        crewMembers[crew.getCrewId()] = crew;
    }
}

void DatabaseManager::saveCrew() {
    QJsonArray array;
    for (auto it = crewMembers.begin(); it != crewMembers.end(); ++it) {
        QJsonDocument doc = QJsonDocument::fromJson(it.value().toJson().toUtf8());
        array.append(doc.object());
    }
    
    QFile file(dataDir + "/crew.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void DatabaseManager::loadReservations() {
    QFile file(dataDir + "/reservations.json");
    if (!file.open(QIODevice::ReadOnly)) return;
    
    QByteArray data = file.readAll();
    file.close();
    
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonArray array = doc.array();
    
    for (const QJsonValue& val : array) {
        Reservation res = Reservation::fromJson(QJsonDocument(val.toObject()).toJson());
        reservations[res.getReservationId()] = res;
    }
}

void DatabaseManager::saveReservations() {
    QJsonArray array;
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        QJsonDocument doc = QJsonDocument::fromJson(it.value().toJson().toUtf8());
        array.append(doc.object());
    }
    
    QFile file(dataDir + "/reservations.json");
    if (file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(array).toJson(QJsonDocument::Indented));
        file.close();
    }
}

void DatabaseManager::initializeDefaultData() {
    // This is called if data files don't exist - they're already created
}

bool DatabaseManager::addUser(std::shared_ptr<User> user) {
    if (users.count(user->getUserId()) > 0) return false;
    users[user->getUserId()] = user;
    saveUsers();
    return true;
}

bool DatabaseManager::updateUser(std::shared_ptr<User> user) {
    if (users.count(user->getUserId()) == 0) return false;
    users[user->getUserId()] = user;
    saveUsers();
    return true;
}

bool DatabaseManager::deleteUser(const QString& userId) {
    if (users.remove(userId) > 0) {
        saveUsers();
        return true;
    }
    return false;
}

std::shared_ptr<User> DatabaseManager::getUser(const QString& userId) {
    auto it = users.find(userId);
    return (it != users.end()) ? it.value() : nullptr;
}

std::shared_ptr<User> DatabaseManager::getUserByUsername(const QString& username) {
    for (auto it = users.begin(); it != users.end(); ++it) {
        if (it.value()->getUsername() == username) {
            return it.value();
        }
    }
    return nullptr;
}

QVector<std::shared_ptr<User>> DatabaseManager::getAllUsers() {
    QVector<std::shared_ptr<User>> result;
    for (auto it = users.begin(); it != users.end(); ++it) {
        result.append(it.value());
    }
    return result;
}

QVector<std::shared_ptr<Passenger>> DatabaseManager::getAllPassengers() {
    QVector<std::shared_ptr<Passenger>> result;
    for (auto it = passengers.begin(); it != passengers.end(); ++it) {
        result.append(it.value());
    }
    return result;
}

bool DatabaseManager::addFlight(const Flight& flight) {
    if (flights.count(flight.getFlightNumber()) > 0) return false;
    flights[flight.getFlightNumber()] = flight;
    saveFlights();
    return true;
}

bool DatabaseManager::updateFlight(const Flight& flight) {
    if (flights.count(flight.getFlightNumber()) == 0) return false;
    flights[flight.getFlightNumber()] = flight;
    saveFlights();
    return true;
}

bool DatabaseManager::deleteFlight(const QString& flightNumber) {
    if (flights.remove(flightNumber) > 0) {
        saveFlights();
        return true;
    }
    return false;
}

Flight* DatabaseManager::getFlight(const QString& flightNumber) {
    if (!flights.contains(flightNumber)) return nullptr;
    return &flights[flightNumber];
}

QVector<Flight> DatabaseManager::getAllFlights() {
    QVector<Flight> result;
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        result.append(it.value());
    }
    return result;
}

QVector<Flight> DatabaseManager::searchFlights(const QString& origin, 
                                                const QString& destination,
                                                const QDate& date) {
    QVector<Flight> result;
    for (auto it = flights.begin(); it != flights.end(); ++it) {
        const Flight& flight = it.value();
        if (flight.getOrigin().contains(origin, Qt::CaseInsensitive) &&
            flight.getDestination().contains(destination, Qt::CaseInsensitive) &&
            flight.getDepartureDateTime().date() == date) {
            result.append(flight);
        }
    }
    return result;
}

bool DatabaseManager::addAircraft(const Aircraft& ac) {
    if (aircraft.count(ac.getAircraftId()) > 0) return false;
    aircraft[ac.getAircraftId()] = ac;
    saveAircraft();
    return true;
}

bool DatabaseManager::updateAircraft(const Aircraft& ac) {
    if (aircraft.count(ac.getAircraftId()) == 0) return false;
    aircraft[ac.getAircraftId()] = ac;
    saveAircraft();
    return true;
}

bool DatabaseManager::deleteAircraft(const QString& aircraftId) {
    if (aircraft.remove(aircraftId) > 0) {
        saveAircraft();
        return true;
    }
    return false;
}

Aircraft* DatabaseManager::getAircraft(const QString& aircraftId) {
    if (!aircraft.contains(aircraftId)) return nullptr;
    return &aircraft[aircraftId];
}

QVector<Aircraft> DatabaseManager::getAllAircraft() {
    QVector<Aircraft> result;
    for (auto it = aircraft.begin(); it != aircraft.end(); ++it) {
        result.append(it.value());
    }
    return result;
}

QVector<Aircraft> DatabaseManager::getAvailableAircraft() {
    QVector<Aircraft> result;
    for (auto it = aircraft.begin(); it != aircraft.end(); ++it) {
        if (it.value().getStatus() == "Available") {
            result.append(it.value());
        }
    }
    return result;
}

bool DatabaseManager::addCrew(const Crew& crew) {
    if (crewMembers.count(crew.getCrewId()) > 0) return false;
    crewMembers[crew.getCrewId()] = crew;
    saveCrew();
    return true;
}

bool DatabaseManager::updateCrew(const Crew& crew) {
    if (crewMembers.count(crew.getCrewId()) == 0) return false;
    crewMembers[crew.getCrewId()] = crew;
    saveCrew();
    return true;
}

bool DatabaseManager::deleteCrew(const QString& crewId) {
    if (crewMembers.remove(crewId) > 0) {
        saveCrew();
        return true;
    }
    return false;
}

Crew* DatabaseManager::getCrew(const QString& crewId) {
    if (!crewMembers.contains(crewId)) return nullptr;
    return &crewMembers[crewId];
}

QVector<Crew> DatabaseManager::getAllCrew() {
    QVector<Crew> result;
    for (auto it = crewMembers.begin(); it != crewMembers.end(); ++it) {
        result.append(it.value());
    }
    return result;
}

QVector<Crew> DatabaseManager::getAvailableCrew(CrewType type) {
    QVector<Crew> result;
    for (auto it = crewMembers.begin(); it != crewMembers.end(); ++it) {
        if (it.value().getType() == type && it.value().getIsAvailable()) {
            result.append(it.value());
        }
    }
    return result;
}

bool DatabaseManager::addReservation(const Reservation& res) {
    if (reservations.count(res.getReservationId()) > 0) return false;
    reservations[res.getReservationId()] = res;
    saveReservations();
    return true;
}

bool DatabaseManager::updateReservation(const Reservation& res) {
    if (reservations.count(res.getReservationId()) == 0) return false;
    reservations[res.getReservationId()] = res;
    saveReservations();
    return true;
}

bool DatabaseManager::deleteReservation(const QString& reservationId) {
    if (reservations.remove(reservationId) > 0) {
        saveReservations();
        return true;
    }
    return false;
}

Reservation* DatabaseManager::getReservation(const QString& reservationId) {
    if (!reservations.contains(reservationId)) return nullptr;
    return &reservations[reservationId];
}

QVector<Reservation> DatabaseManager::getAllReservations() {
    QVector<Reservation> result;
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        result.append(it.value());
    }
    return result;
}

QVector<Reservation> DatabaseManager::getReservationsByPassenger(const QString& passengerId) {
    QVector<Reservation> result;
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it.value().getPassengerId() == passengerId) {
            result.append(it.value());
        }
    }
    return result;
}

QVector<Reservation> DatabaseManager::getReservationsByFlight(const QString& flightNumber) {
    QVector<Reservation> result;
    for (auto it = reservations.begin(); it != reservations.end(); ++it) {
        if (it.value().getFlightNumber() == flightNumber) {
            result.append(it.value());
        }
    }
    return result;
}

QString DatabaseManager::generateUniqueId(const QString& prefix) {
    static int counter = 1000;
    return QString("%1%2").arg(prefix).arg(++counter);
}
