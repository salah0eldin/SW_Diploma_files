#include "Flight.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

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

bool Flight::bookSeat(const QString& seatNumber) {
    return occupySeat(seatNumber, "Economy");
}

QString Flight::statusToString(FlightStatus status) {
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
    return departureDateTime.secsTo(arrivalDateTime) / 60;
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
