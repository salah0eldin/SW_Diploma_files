#include "BookingAgent.h"
#include <QJsonObject>
#include <QJsonDocument>

BookingAgent::BookingAgent(const QString& userId, const QString& username,
                           const QString& password, const QString& agentId)
    : User(userId, username, password, UserRole::BookingAgent),
      agentId(agentId), totalBookings(0), commissionRate(0.05) {
}

QString BookingAgent::toJson() const {
    QJsonDocument doc = QJsonDocument::fromJson(User::toJson().toUtf8());
    QJsonObject json = doc.object();
    
    json["type"] = "BookingAgent";
    json["agentId"] = agentId;
    json["agencyName"] = agencyName;
    json["totalBookings"] = totalBookings;
    json["commissionRate"] = commissionRate;
    
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

BookingAgent* BookingAgent::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    BookingAgent* agent = new BookingAgent();
    agent->userId = json["userId"].toString();
    agent->username = json["username"].toString();
    agent->password = json["password"].toString();
    agent->role = UserRole::BookingAgent;
    agent->createdAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    agent->isActive = json["isActive"].toBool();
    agent->agentId = json["agentId"].toString();
    agent->agencyName = json["agencyName"].toString();
    agent->totalBookings = json["totalBookings"].toInt();
    agent->commissionRate = json["commissionRate"].toDouble();
    
    return agent;
}
