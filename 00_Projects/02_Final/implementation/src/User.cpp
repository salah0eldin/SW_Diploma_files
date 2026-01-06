#include "User.h"
#include <QJsonObject>
#include <QJsonDocument>

User::User(const QString& userId, const QString& username, 
           const QString& password, UserRole role)
    : userId(userId), username(username), password(password), 
      role(role), isActive(true) {
    createdAt = QDateTime::currentDateTime();
}

QString User::getRoleString() const {
    return roleToString(role);
}

QString User::roleToString(UserRole role) {
    switch (role) {
        case UserRole::Administrator: return "Administrator";
        case UserRole::BookingAgent: return "Booking Agent";
        case UserRole::Passenger: return "Passenger";
        default: return "Unknown";
    }
}

QString User::toJson() const {
    QJsonObject json;
    json["userId"] = userId;
    json["username"] = username;
    json["password"] = password;
    json["role"] = static_cast<int>(role);
    json["createdAt"] = createdAt.toString(Qt::ISODate);
    json["isActive"] = isActive;
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

User* User::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    User* user = new User();
    user->userId = json["userId"].toString();
    user->username = json["username"].toString();
    user->password = json["password"].toString();
    user->role = static_cast<UserRole>(json["role"].toInt());
    user->createdAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    user->isActive = json["isActive"].toBool();
    
    return user;
}
