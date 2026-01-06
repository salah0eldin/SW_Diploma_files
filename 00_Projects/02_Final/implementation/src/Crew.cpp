#include "Crew.h"
#include <QJsonObject>
#include <QJsonDocument>

Crew::Crew(const QString& id, const QString& name, CrewType type)
    : crewId(id), name(name), type(type), totalFlightHours(0),
      maxFlightHours(1000), isAvailable(true) {
}

QString Crew::getTypeString() const {
    return typeToString(type);
}

QString Crew::typeToString(CrewType type) {
    switch (type) {
        case CrewType::Pilot: return "Pilot";
        case CrewType::CoPilot: return "Co-Pilot";
        case CrewType::FlightAttendant: return "Flight Attendant";
        default: return "Unknown";
    }
}

QString Crew::toJson() const {
    QJsonObject json;
    json["crewId"] = crewId;
    json["name"] = name;
    json["type"] = static_cast<int>(type);
    json["totalFlightHours"] = totalFlightHours;
    json["maxFlightHours"] = maxFlightHours;
    json["licenseNumber"] = licenseNumber;
    json["isAvailable"] = isAvailable;
    
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Crew Crew::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    Crew crew;
    crew.crewId = json["crewId"].toString();
    crew.name = json["name"].toString();
    crew.type = static_cast<CrewType>(json["type"].toInt());
    crew.totalFlightHours = json["totalFlightHours"].toInt();
    crew.maxFlightHours = json["maxFlightHours"].toInt();
    crew.licenseNumber = json["licenseNumber"].toString();
    crew.isAvailable = json["isAvailable"].toBool();
    
    return crew;
}
