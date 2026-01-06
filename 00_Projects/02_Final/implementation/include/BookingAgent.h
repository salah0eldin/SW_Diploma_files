#ifndef BOOKINGAGENT_H
#define BOOKINGAGENT_H

#include "User.h"

class BookingAgent : public User {
private:
    QString agentId;
    QString agencyName;
    int totalBookings;
    double commissionRate;

public:
    BookingAgent(const QString& userId = "", const QString& username = "",
                 const QString& password = "", const QString& agentId = "");
    
    QString getAgentId() const { return agentId; }
    QString getAgencyName() const { return agencyName; }
    int getTotalBookings() const { return totalBookings; }
    double getCommissionRate() const { return commissionRate; }
    
    void setAgentId(const QString& id) { agentId = id; }
    void setAgencyName(const QString& name) { agencyName = name; }
    void incrementBookings() { totalBookings++; }
    void setCommissionRate(double rate) { commissionRate = rate; }
    void recordBooking(double amount) { totalBookings++; }
    
    QString toJson() const override;
    static BookingAgent* fromJson(const QString& json);
};

#endif // BOOKINGAGENT_H
