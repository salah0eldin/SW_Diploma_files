#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QVector>
#include <QMap>
#include <memory>
#include "User.h"
#include "Passenger.h"
#include "Administrator.h"
#include "BookingAgent.h"
#include "Flight.h"
#include "Aircraft.h"
#include "Crew.h"
#include "Reservation.h"

class DatabaseManager : public QObject {
    Q_OBJECT

private:
    static DatabaseManager* instance;
    QString dataDir;
    
    QMap<QString, std::shared_ptr<User>> users;
    QMap<QString, std::shared_ptr<Passenger>> passengers;
    QMap<QString, std::shared_ptr<Administrator>> administrators;
    QMap<QString, std::shared_ptr<BookingAgent>> bookingAgents;
    QMap<QString, Flight> flights;
    QMap<QString, Aircraft> aircraft;
    QMap<QString, Crew> crewMembers;
    QMap<QString, Reservation> reservations;
    
    DatabaseManager();
    
    void loadUsers();
    void loadFlights();
    void loadAircraft();
    void loadCrew();
    void loadReservations();
    
    void saveUsers();
    void saveFlights();
    void saveAircraft();
    void saveCrew();
    void saveReservations();
    
public:
    static DatabaseManager* getInstance();
    ~DatabaseManager();
    
    void loadAll();
    void saveAll();
    void initializeDefaultData();
    
    // User operations
    bool addUser(std::shared_ptr<User> user);
    bool updateUser(std::shared_ptr<User> user);
    bool deleteUser(const QString& userId);
    std::shared_ptr<User> getUser(const QString& userId);
    std::shared_ptr<User> getUserByUsername(const QString& username);
    QVector<std::shared_ptr<User>> getAllUsers();
    QVector<std::shared_ptr<Passenger>> getAllPassengers();
    
    // Flight operations
    bool addFlight(const Flight& flight);
    bool updateFlight(const Flight& flight);
    bool deleteFlight(const QString& flightNumber);
    Flight* getFlight(const QString& flightNumber);
    QVector<Flight> getAllFlights();
    QVector<Flight> searchFlights(const QString& origin, const QString& destination, 
                                   const QDate& date);
    
    // Aircraft operations
    bool addAircraft(const Aircraft& aircraft);
    bool updateAircraft(const Aircraft& aircraft);
    bool deleteAircraft(const QString& aircraftId);
    Aircraft* getAircraft(const QString& aircraftId);
    QVector<Aircraft> getAllAircraft();
    QVector<Aircraft> getAvailableAircraft();
    
    // Crew operations
    bool addCrew(const Crew& crew);
    bool updateCrew(const Crew& crew);
    bool deleteCrew(const QString& crewId);
    Crew* getCrew(const QString& crewId);
    QVector<Crew> getAllCrew();
    QVector<Crew> getAvailableCrew(CrewType type);
    
    // Reservation operations
    bool addReservation(const Reservation& reservation);
    bool updateReservation(const Reservation& reservation);
    bool deleteReservation(const QString& reservationId);
    Reservation* getReservation(const QString& reservationId);
    QVector<Reservation> getAllReservations();
    QVector<Reservation> getReservationsByPassenger(const QString& passengerId);
    QVector<Reservation> getReservationsByFlight(const QString& flightNumber);
    
    // Utility
    QString generateUniqueId(const QString& prefix);
};

#endif // DATABASEMANAGER_H
