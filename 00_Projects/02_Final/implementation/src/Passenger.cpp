#include "Passenger.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

Passenger::Passenger(const QString& userId, const QString& username,
                     const QString& password, const QString& fullName,
                     const QString& email, const QString& phone)
    : User(userId, username, password, UserRole::Passenger),
      fullName(fullName), email(email), phone(phone), loyaltyPoints(0) {
}

void Passenger::addToTravelHistory(const QString& flightNumber) {
    travelHistory.append(flightNumber);
}

QString Passenger::toJson() const {
    QJsonDocument doc = QJsonDocument::fromJson(User::toJson().toUtf8());
    QJsonObject json = doc.object();
    
    json["type"] = "Passenger";
    json["fullName"] = fullName;
    json["email"] = email;
    json["phone"] = phone;
    json["address"] = address;
    json["loyaltyPoints"] = loyaltyPoints;
    
    QJsonArray history;
    for (const QString& flight : travelHistory) {
        history.append(flight);
    }
    json["travelHistory"] = history;
    
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Passenger* Passenger::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    Passenger* passenger = new Passenger();
    passenger->userId = json["userId"].toString();
    passenger->username = json["username"].toString();
    passenger->password = json["password"].toString();
    passenger->role = UserRole::Passenger;
    passenger->createdAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    passenger->isActive = json["isActive"].toBool();
    passenger->fullName = json["fullName"].toString();
    passenger->email = json["email"].toString();
    passenger->phone = json["phone"].toString();
    passenger->address = json["address"].toString();
    passenger->loyaltyPoints = json["loyaltyPoints"].toInt();
    
    QJsonArray history = json["travelHistory"].toArray();
    for (const QJsonValue& val : history) {
        passenger->travelHistory.append(val.toString());
    }
    
    return passenger;
}
