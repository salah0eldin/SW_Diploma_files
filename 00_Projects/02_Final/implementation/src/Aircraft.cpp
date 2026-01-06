#include "Aircraft.h"
#include <QJsonObject>
#include <QJsonDocument>

Aircraft::Aircraft(const QString& id, const QString& type,
                   const QString& manufacturer, int totalSeats)
    : aircraftId(id), aircraftType(type), manufacturer(manufacturer),
      totalSeats(totalSeats), economySeats(0), businessSeats(0),
      firstClassSeats(0), status("Available"), totalFlightHours(0) {
}

bool Aircraft::needsMaintenance() const {
    QDateTime now = QDateTime::currentDateTime();
    return now >= nextMaintenanceDate;
}

QString Aircraft::toJson() const {
    QJsonObject json;
    json["aircraftId"] = aircraftId;
    json["aircraftType"] = aircraftType;
    json["manufacturer"] = manufacturer;
    json["totalSeats"] = totalSeats;
    json["economySeats"] = economySeats;
    json["businessSeats"] = businessSeats;
    json["firstClassSeats"] = firstClassSeats;
    json["lastMaintenanceDate"] = lastMaintenanceDate.toString(Qt::ISODate);
    json["nextMaintenanceDate"] = nextMaintenanceDate.toString(Qt::ISODate);
    json["status"] = status;
    json["totalFlightHours"] = totalFlightHours;
    
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Aircraft Aircraft::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    Aircraft aircraft;
    aircraft.aircraftId = json["aircraftId"].toString();
    aircraft.aircraftType = json["aircraftType"].toString();
    aircraft.manufacturer = json["manufacturer"].toString();
    aircraft.totalSeats = json["totalSeats"].toInt();
    aircraft.economySeats = json["economySeats"].toInt();
    aircraft.businessSeats = json["businessSeats"].toInt();
    aircraft.firstClassSeats = json["firstClassSeats"].toInt();
    aircraft.lastMaintenanceDate = QDateTime::fromString(json["lastMaintenanceDate"].toString(), Qt::ISODate);
    aircraft.nextMaintenanceDate = QDateTime::fromString(json["nextMaintenanceDate"].toString(), Qt::ISODate);
    aircraft.status = json["status"].toString();
    aircraft.totalFlightHours = json["totalFlightHours"].toInt();
    
    return aircraft;
}
