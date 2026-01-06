#include "Reservation.h"
#include <QJsonObject>
#include <QJsonDocument>

Reservation::Reservation(const QString& reservationId, const QString& passengerId,
                         const QString& passengerName, const QString& flightNumber,
                         const QString& seatNumber)
    : reservationId(reservationId), passengerId(passengerId),
      passengerName(passengerName), flightNumber(flightNumber),
      seatNumber(seatNumber), totalCost(0.0),
      paymentMethod(PaymentMethod::CreditCard),
      status(ReservationStatus::Confirmed), boardingPassIssued(false) {
    bookingDateTime = QDateTime::currentDateTime();
}

void Reservation::checkIn() {
    status = ReservationStatus::CheckedIn;
    checkInDateTime = QDateTime::currentDateTime();
    boardingPassIssued = true;
}

QString Reservation::getBoardingPass() const {
    QString pass;
    pass += "========================================\n";
    pass += "         BOARDING PASS\n";
    pass += "========================================\n";
    pass += QString("Reservation ID: %1\n").arg(reservationId);
    pass += QString("Passenger: %1\n").arg(passengerName);
    pass += QString("Flight: %1\n").arg(flightNumber);
    pass += QString("Seat: %1 (%2)\n").arg(seatNumber).arg(seatClass);
    pass += QString("Check-In: %1\n").arg(checkInDateTime.toString("yyyy-MM-dd HH:mm"));
    pass += "========================================\n";
    return pass;
}

QString Reservation::getStatusString() const {
    switch (status) {
        case ReservationStatus::Confirmed: return "Confirmed";
        case ReservationStatus::CheckedIn: return "Checked In";
        case ReservationStatus::Canceled: return "Canceled";
        case ReservationStatus::Completed: return "Completed";
        default: return "Unknown";
    }
}

void Reservation::cancel() {
    status = ReservationStatus::Canceled;
}

QString Reservation::statusToString(ReservationStatus status) {
    switch (status) {
        case ReservationStatus::Confirmed: return "Confirmed";
        case ReservationStatus::CheckedIn: return "Checked In";
        case ReservationStatus::Canceled: return "Canceled";
        case ReservationStatus::Completed: return "Completed";
        default: return "Unknown";
    }
}

QString Reservation::getPaymentMethodString() const {
    switch (paymentMethod) {
        case PaymentMethod::CreditCard: return "Credit Card";
        case PaymentMethod::DebitCard: return "Debit Card";
        case PaymentMethod::Cash: return "Cash";
        case PaymentMethod::PayPal: return "PayPal";
        default: return "Unknown";
    }
}

QString Reservation::toJson() const {
    QJsonObject json;
    json["reservationId"] = reservationId;
    json["passengerId"] = passengerId;
    json["passengerName"] = passengerName;
    json["flightNumber"] = flightNumber;
    json["seatNumber"] = seatNumber;
    json["seatClass"] = seatClass;
    json["totalCost"] = totalCost;
    json["paymentMethod"] = static_cast<int>(paymentMethod);
    json["paymentDetails"] = paymentDetails;
    json["status"] = static_cast<int>(status);
    json["bookingDateTime"] = bookingDateTime.toString(Qt::ISODate);
    json["checkInDateTime"] = checkInDateTime.toString(Qt::ISODate);
    json["bookingAgentId"] = bookingAgentId;
    json["boardingPassIssued"] = boardingPassIssued;
    
    return QJsonDocument(json).toJson(QJsonDocument::Compact);
}

Reservation Reservation::fromJson(const QString& jsonString) {
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    QJsonObject json = doc.object();
    
    Reservation res;
    res.reservationId = json["reservationId"].toString();
    res.passengerId = json["passengerId"].toString();
    res.passengerName = json["passengerName"].toString();
    res.flightNumber = json["flightNumber"].toString();
    res.seatNumber = json["seatNumber"].toString();
    res.seatClass = json["seatClass"].toString();
    res.totalCost = json["totalCost"].toDouble();
    res.paymentMethod = static_cast<PaymentMethod>(json["paymentMethod"].toInt());
    res.paymentDetails = json["paymentDetails"].toString();
    res.status = static_cast<ReservationStatus>(json["status"].toInt());
    res.bookingDateTime = QDateTime::fromString(json["bookingDateTime"].toString(), Qt::ISODate);
    res.checkInDateTime = QDateTime::fromString(json["checkInDateTime"].toString(), Qt::ISODate);
    res.bookingAgentId = json["bookingAgentId"].toString();
    res.boardingPassIssued = json["boardingPassIssued"].toBool();
    
    return res;
}
