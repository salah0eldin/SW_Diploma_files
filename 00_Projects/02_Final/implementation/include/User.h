#ifndef USER_H
#define USER_H

#include <QString>
#include <QDateTime>

enum class UserRole {
    Administrator,
    BookingAgent,
    Passenger
};

class User {
protected:
    QString userId;
    QString username;
    QString password;
    UserRole role;
    QDateTime createdAt;
    bool isActive;

public:
    User(const QString& userId = "", const QString& username = "", 
         const QString& password = "", UserRole role = UserRole::Passenger);
    virtual ~User() = default;
    
    // Getters
    QString getUserId() const { return userId; }
    QString getUsername() const { return username; }
    QString getPassword() const { return password; }
    UserRole getRole() const { return role; }
    QDateTime getCreatedAt() const { return createdAt; }
    bool getIsActive() const { return isActive; }
    
    // Setters
    void setUserId(const QString& id) { userId = id; }
    void setUsername(const QString& name) { username = name; }
    void setPassword(const QString& pass) { password = pass; }
    void setRole(UserRole r) { role = r; }
    void setIsActive(bool active) { isActive = active; }
    
    QString getRoleString() const;
    static QString roleToString(UserRole role);
    virtual QString toJson() const;
    static User* fromJson(const QString& json);
};

#endif // USER_H
