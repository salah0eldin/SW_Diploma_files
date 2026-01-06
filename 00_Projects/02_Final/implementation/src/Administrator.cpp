#include "Administrator.h"
#include <QJsonObject>
#include <QJsonDocument>

Administrator::Administrator(const QString& userId, const QString& username,
                             const QString& password, const QString& department)
    : User(userId, username, password, UserRole::Administrator),
      department(department), accessLevel("Full") {
}

QString Administrator::toJson() const {
    QJsonDocument doc = QJsonDocument::fromJson(User::toJson().toUtf8());
    QJsonObject json = doc.object();
    
    json["type"] = "Administrator";
    json["department"] = department;
    json["accessLevel"] = accessLevel;
    
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Administrator* Administrator::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    Administrator* admin = new Administrator();
    admin->userId = json["userId"].toString();
    admin->username = json["username"].toString();
    admin->password = json["password"].toString();
    admin->role = UserRole::Administrator;
    admin->createdAt = QDateTime::fromString(json["createdAt"].toString(), Qt::ISODate);
    admin->isActive = json["isActive"].toBool();
    admin->department = json["department"].toString();
    admin->accessLevel = json["accessLevel"].toString();
    
    return admin;
}
