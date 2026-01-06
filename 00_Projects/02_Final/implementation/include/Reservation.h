#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDateTime>

enum class ReservationStatus {
    Confirmed,
    CheckedIn,
    Canceled,
    Completed
};

enum class PaymentMethod {
    CreditCard,
    DebitCard,
    Cash,
    PayPal
};

class Reservation {
private:
    QString reservationId;
    QString passengerId;
    QString passengerName;
    QString flightNumber;
    QString seatNumber;
    QString seatClass;
    double totalCost;
    PaymentMethod paymentMethod;
    QString paymentDetails;
    ReservationStatus status;
    QDateTime bookingDateTime;
    QDateTime checkInDateTime;
    QString bookingAgentId;
    bool boardingPassIssued;

public:
    Reservation(const QString& reservationId = "", const QString& passengerId = "",
                const QString& passengerName = "", const QString& flightNumber = "",
                const QString& seatNumber = "");
    
    // Getters
    QString getReservationId() const { return reservationId; }
    QString getPassengerId() const { return passengerId; }
    QString getPassengerName() const { return passengerName; }
    QString getFlightNumber() const { return flightNumber; }
    QString getSeatNumber() const { return seatNumber; }
    QString getSeatClass() const { return seatClass; }
    double getTotalCost() const { return totalCost; }
    PaymentMethod getPaymentMethod() const { return paymentMethod; }
    QString getPaymentDetails() const { return paymentDetails; }
    ReservationStatus getStatus() const { return status; }
    QDateTime getBookingDateTime() const { return bookingDateTime; }
    QDateTime getCheckInDateTime() const { return checkInDateTime; }
    QString getBookingAgentId() const { return bookingAgentId; }
    bool getBoardingPassIssued() const { return boardingPassIssued; }
    
    // Setters
    void setReservationId(const QString& id) { reservationId = id; }
    void setPassengerId(const QString& id) { passengerId = id; }
    void setPassengerName(const QString& name) { passengerName = name; }
    void setFlightNumber(const QString& number) { flightNumber = number; }
    void setSeatNumber(const QString& seat) { seatNumber = seat; }
    void setSeatClass(const QString& sClass) { seatClass = sClass; }
    void setTotalCost(double cost) { totalCost = cost; }
    void setPaymentMethod(PaymentMethod method) { paymentMethod = method; }
    void setPaymentDetails(const QString& details) { paymentDetails = details; }
    void setStatus(ReservationStatus stat) { status = stat; }
    void setBookingDateTime(const QDateTime& dateTime) { bookingDateTime = dateTime; }
    void setCheckInDateTime(const QDateTime& dateTime) { checkInDateTime = dateTime; }
    void setBookingAgentId(const QString& id) { bookingAgentId = id; }
    void setBoardingPassIssued(bool issued) { boardingPassIssued = issued; }
    
    // Methods
    void checkIn();
    void cancel();
    QString getBoardingPass() const;
    double getPaymentAmount() const { return totalCost; }
    void setPaymentAmount(double amount) { totalCost = amount; }
    
    QString getStatusString() const;
    QString getPaymentMethodString() const;
    static QString statusToString(ReservationStatus status);
    QString toJson() const;
    static Reservation fromJson(const QString& json);
};

#endif // RESERVATION_H
