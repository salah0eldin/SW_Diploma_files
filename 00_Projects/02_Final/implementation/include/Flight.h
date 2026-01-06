#ifndef FLIGHT_H
#define FLIGHT_H

#include <QString>
#include <QDateTime>
#include <QSet>
#include <QMap>

enum class FlightStatus {
    Scheduled,
    Boarding,
    Departed,
    Delayed,
    Canceled,
    Completed
};

class Flight {
private:
    QString flightNumber;
    QString origin;
    QString destination;
    QDateTime departureDateTime;
    QDateTime arrivalDateTime;
    QString aircraftId;
    QString aircraftType;
    int totalSeats;
    FlightStatus status;
    QSet<QString> occupiedSeats;
    QString pilotId;
    QString coPilotId;
    QStringList attendantIds;
    QString gate;
    double economyPrice;
    double businessPrice;
    double firstClassPrice;
    QMap<QString, QString> seatClass; // seat -> class mapping

public:
    Flight(const QString& flightNumber = "", const QString& origin = "",
           const QString& destination = "", const QDateTime& departure = QDateTime(),
           const QDateTime& arrival = QDateTime());
    
    // Getters
    QString getFlightNumber() const { return flightNumber; }
    QString getOrigin() const { return origin; }
    QString getDestination() const { return destination; }
    QDateTime getDepartureDateTime() const { return departureDateTime; }
    QDateTime getArrivalDateTime() const { return arrivalDateTime; }
    QString getAircraftId() const { return aircraftId; }
    QString getAircraftType() const { return aircraftType; }
    int getTotalSeats() const { return totalSeats; }
    FlightStatus getStatus() const { return status; }
    QString getPilotId() const { return pilotId; }
    QString getCoPilotId() const { return coPilotId; }
    QStringList getAttendantIds() const { return attendantIds; }
    QString getGate() const { return gate; }
    double getEconomyPrice() const { return economyPrice; }
    double getBusinessPrice() const { return businessPrice; }
    double getFirstClassPrice() const { return firstClassPrice; }
    int getAvailableSeats() const { return totalSeats - occupiedSeats.size(); }
    QSet<QString> getOccupiedSeats() const { return occupiedSeats; }
    
    // Setters
    void setFlightNumber(const QString& number) { flightNumber = number; }
    void setOrigin(const QString& orig) { origin = orig; }
    void setDestination(const QString& dest) { destination = dest; }
    void setDepartureDateTime(const QDateTime& departure) { departureDateTime = departure; }
    void setArrivalDateTime(const QDateTime& arrival) { arrivalDateTime = arrival; }
    void setAircraftId(const QString& id) { aircraftId = id; }
    void setAircraftType(const QString& type) { aircraftType = type; }
    void setTotalSeats(int seats) { totalSeats = seats; }
    void setStatus(FlightStatus stat) { status = stat; }
    void setPilotId(const QString& id) { pilotId = id; }
    void setCoPilotId(const QString& id) { coPilotId = id; }
    void addAttendant(const QString& id) { attendantIds.append(id); }
    void setGate(const QString& g) { gate = g; }
    void setEconomyPrice(double price) { economyPrice = price; }
    void setBusinessPrice(double price) { businessPrice = price; }
    void setFirstClassPrice(double price) { firstClassPrice = price; }
    
    // Seat management
    bool isSeatAvailable(const QString& seatNumber) const;
    bool occupySeat(const QString& seatNumber, const QString& seatClass);
    bool bookSeat(const QString& seat);
    bool releaseSeat(const QString& seatNumber);
    QString getSeatClass(const QString& seatNumber) const;
    double getSeatPrice(const QString& seatNumber) const;
    double getBasePrice() const { return economyPrice; }
    
    // Utility
    static QString statusToString(FlightStatus status);
    QString getStatusString() const;
    int getFlightDuration() const;
    QString toJson() const;
    static Flight fromJson(const QString& json);
};

#endif // FLIGHT_H
