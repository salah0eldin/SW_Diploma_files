#ifndef PASSENGER_H
#define PASSENGER_H

#include "User.h"
#include <QString>

class Passenger : public User {
private:
    QString fullName;
    QString email;
    QString phone;
    QString address;
    int loyaltyPoints;
    QStringList travelHistory;

public:
    Passenger(const QString& userId = "", const QString& username = "",
              const QString& password = "", const QString& fullName = "",
              const QString& email = "", const QString& phone = "");
    
    // Getters
    QString getFullName() const { return fullName; }
    QString getEmail() const { return email; }
    QString getPhone() const { return phone; }
    QString getAddress() const { return address; }
    int getLoyaltyPoints() const { return loyaltyPoints; }
    QStringList getTravelHistory() const { return travelHistory; }
    
    // Setters
    void setFullName(const QString& name) { fullName = name; }
    void setEmail(const QString& mail) { email = mail; }
    void setPhone(const QString& ph) { phone = ph; }
    void setAddress(const QString& addr) { address = addr; }
    void setLoyaltyPoints(int points) { loyaltyPoints = points; }
    
    // Methods
    void addLoyaltyPoints(int points) { loyaltyPoints += points; }
    void addToTravelHistory(const QString& flightNumber);
    
    QString toJson() const override;
    static Passenger* fromJson(const QString& json);
};

#endif // PASSENGER_H
