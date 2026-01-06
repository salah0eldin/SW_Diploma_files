#ifndef AIRCRAFT_H
#define AIRCRAFT_H

#include <QString>
#include <QDateTime>

class Aircraft {
private:
    QString aircraftId;
    QString aircraftType;
    QString manufacturer;
    int totalSeats;
    int economySeats;
    int businessSeats;
    int firstClassSeats;
    QDateTime lastMaintenanceDate;
    QDateTime nextMaintenanceDate;
    QString status; // Available, In Maintenance, In Flight
    int totalFlightHours;

public:
    Aircraft(const QString& id = "", const QString& type = "",
             const QString& manufacturer = "", int totalSeats = 0);
    
    // Getters
    QString getAircraftId() const { return aircraftId; }
    QString getAircraftType() const { return aircraftType; }
    QString getManufacturer() const { return manufacturer; }
    int getTotalSeats() const { return totalSeats; }
    int getEconomySeats() const { return economySeats; }
    int getBusinessSeats() const { return businessSeats; }
    int getFirstClassSeats() const { return firstClassSeats; }
    QDateTime getLastMaintenanceDate() const { return lastMaintenanceDate; }
    QDateTime getNextMaintenanceDate() const { return nextMaintenanceDate; }
    QString getStatus() const { return status; }
    int getTotalFlightHours() const { return totalFlightHours; }
    
    // Setters
    void setAircraftId(const QString& id) { aircraftId = id; }
    void setAircraftType(const QString& type) { aircraftType = type; }
    void setManufacturer(const QString& mfg) { manufacturer = mfg; }
    void setTotalSeats(int seats) { totalSeats = seats; }
    void setEconomySeats(int seats) { economySeats = seats; }
    void setBusinessSeats(int seats) { businessSeats = seats; }
    void setFirstClassSeats(int seats) { firstClassSeats = seats; }
    void setLastMaintenanceDate(const QDateTime& date) { lastMaintenanceDate = date; }
    void setNextMaintenanceDate(const QDateTime& date) { nextMaintenanceDate = date; }
    void setStatus(const QString& stat) { status = stat; }
    void addFlightHours(int hours) { totalFlightHours += hours; }
    
    bool needsMaintenance() const;
    QString toJson() const;
    static Aircraft fromJson(const QString& json);
};

#endif // AIRCRAFT_H
