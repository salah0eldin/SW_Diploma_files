#ifndef CREW_H
#define CREW_H

#include <QString>

enum class CrewType {
    Pilot,
    CoPilot,
    FlightAttendant
};

class Crew {
private:
    QString crewId;
    QString name;
    CrewType type;
    int totalFlightHours;
    int maxFlightHours;
    QString licenseNumber;
    bool isAvailable;

public:
    Crew(const QString& id = "", const QString& name = "", 
         CrewType type = CrewType::Pilot);
    
    QString getCrewId() const { return crewId; }
    QString getName() const { return name; }
    CrewType getType() const { return type; }
    int getTotalFlightHours() const { return totalFlightHours; }
    int getMaxFlightHours() const { return maxFlightHours; }
    QString getLicenseNumber() const { return licenseNumber; }
    bool getIsAvailable() const { return isAvailable; }
    
    void setCrewId(const QString& id) { crewId = id; }
    void setName(const QString& n) { name = n; }
    void setType(CrewType t) { type = t; }
    void setLicenseNumber(const QString& license) { licenseNumber = license; }
    void setIsAvailable(bool available) { isAvailable = available; }
    void addFlightHours(int hours) { totalFlightHours += hours; }
    
    bool canFly() const { return isAvailable && totalFlightHours < maxFlightHours; }
    QString getTypeString() const;
    static QString typeToString(CrewType type);
    QString toJson() const;
    static Crew fromJson(const QString& json);
};

#endif // CREW_H
