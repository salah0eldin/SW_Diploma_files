#include "PassengerWindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QHeaderView>

PassengerWindow::PassengerWindow(const QString& passengerId, QWidget *parent)
    : QWidget(parent), passengerId(passengerId) {
    setupUi();
    loadData();
}

PassengerWindow::~PassengerWindow() {
}

void PassengerWindow::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // Dashboard header
    QWidget* headerWidget = new QWidget(this);
    headerWidget->setStyleSheet(
        "QWidget { "
        "   background: white; "
        "   border-radius: 8px; "
        "   padding: 15px; "
        "}"
    );
    QHBoxLayout* headerLayout = new QHBoxLayout(headerWidget);
    
    QLabel* titleLabel = new QLabel("🧳 Passenger Dashboard", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #0f4c75; background: transparent;");
    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    
    mainLayout->addWidget(headerWidget);
    mainLayout->addSpacing(15);
    
    tabWidget = new QTabWidget(this);
    
    // Search Flights Tab
    QWidget* searchWidget = new QWidget(this);
    setupSearchTab(searchWidget);
    tabWidget->addTab(searchWidget, "Search Flights");
    
    // My Reservations Tab
    myReservationsTable = new QTableWidget(this);
    setupReservationsTab();
    tabWidget->addTab(myReservationsTable, "My Reservations");
    
    // Check-In Tab
    QWidget* checkinWidget = new QWidget(this);
    setupCheckinTab(checkinWidget);
    tabWidget->addTab(checkinWidget, "Check-In");
    
    // Profile Tab
    QWidget* profileWidget = new QWidget(this);
    setupProfileTab(profileWidget);
    tabWidget->addTab(profileWidget, "Profile");
    
    // Loyalty Program Tab
    QWidget* loyaltyWidget = new QWidget(this);
    setupLoyaltyTab(loyaltyWidget);
    tabWidget->addTab(loyaltyWidget, "Loyalty Program");
    
    mainLayout->addWidget(tabWidget);
}

void PassengerWindow::setupSearchTab(QWidget* searchWidget) {
    QVBoxLayout* layout = new QVBoxLayout(searchWidget);
    
    // Search form
    QFormLayout* formLayout = new QFormLayout();
    
    originEdit = new QLineEdit(this);
    destinationEdit = new QLineEdit(this);
    dateEdit = new QDateEdit(QDate::currentDate(), this);
    dateEdit->setCalendarPopup(true);
    
    formLayout->addRow("Origin:", originEdit);
    formLayout->addRow("Destination:", destinationEdit);
    formLayout->addRow("Date:", dateEdit);
    
    QPushButton* searchBtn = new QPushButton("Search Flights", this);
    formLayout->addRow(searchBtn);
    
    layout->addLayout(formLayout);
    
    // Results table
    searchResultsTable = new QTableWidget(this);
    searchResultsTable->setColumnCount(7);
    searchResultsTable->setHorizontalHeaderLabels({
        "Flight Number", "Origin", "Destination", "Departure", "Arrival", "Available Seats", "Price"
    });
    searchResultsTable->horizontalHeader()->setStretchLastSection(true);
    searchResultsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    searchResultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    layout->addWidget(searchResultsTable);
    
    // Book button
    QPushButton* bookBtn = new QPushButton("Book Selected Flight", this);
    layout->addWidget(bookBtn);
    
    connect(searchBtn, &QPushButton::clicked, this, &PassengerWindow::onSearchFlights);
    connect(bookBtn, &QPushButton::clicked, this, &PassengerWindow::onBookFlight);
}

void PassengerWindow::setupReservationsTab() {
    QVBoxLayout* layout = new QVBoxLayout();
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    QPushButton* cancelBtn = new QPushButton("Cancel Reservation", this);
    
    buttonLayout->addWidget(refreshBtn);
    buttonLayout->addWidget(cancelBtn);
    buttonLayout->addStretch();
    
    myReservationsTable->setColumnCount(7);
    myReservationsTable->setHorizontalHeaderLabels({
        "Reservation ID", "Flight", "Seat", "Amount", "Status", "Booking Date", "Payment Method"
    });
    myReservationsTable->horizontalHeader()->setStretchLastSection(true);
    myReservationsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    myReservationsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    connect(refreshBtn, &QPushButton::clicked, this, &PassengerWindow::refreshMyReservations);
    connect(cancelBtn, &QPushButton::clicked, this, &PassengerWindow::onCancelReservation);
}

void PassengerWindow::setupCheckinTab(QWidget* checkinWidget) {
    QVBoxLayout* layout = new QVBoxLayout(checkinWidget);
    
    QLabel* infoLabel = new QLabel("Enter your reservation ID to check in:", this);
    layout->addWidget(infoLabel);
    
    QFormLayout* formLayout = new QFormLayout();
    
    reservationIdEdit = new QLineEdit(this);
    formLayout->addRow("Reservation ID:", reservationIdEdit);
    
    QPushButton* checkinBtn = new QPushButton("Check In", this);
    formLayout->addRow(checkinBtn);
    
    layout->addLayout(formLayout);
    
    boardingPassText = new QTextEdit(this);
    boardingPassText->setReadOnly(true);
    layout->addWidget(boardingPassText);
    
    layout->addStretch();
    
    connect(checkinBtn, &QPushButton::clicked, this, &PassengerWindow::onCheckin);
}

void PassengerWindow::setupProfileTab(QWidget* profileWidget) {
    QVBoxLayout* layout = new QVBoxLayout(profileWidget);
    
    profileForm = new QFormLayout();
    
    fullNameEdit = new QLineEdit(this);
    emailEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    
    profileForm->addRow("Full Name:", fullNameEdit);
    profileForm->addRow("Email:", emailEdit);
    profileForm->addRow("Phone:", phoneEdit);
    
    QPushButton* updateBtn = new QPushButton("Update Profile", this);
    profileForm->addRow(updateBtn);
    
    layout->addLayout(profileForm);
    layout->addStretch();
    
    connect(updateBtn, &QPushButton::clicked, this, &PassengerWindow::onUpdateProfile);
}

void PassengerWindow::setupLoyaltyTab(QWidget* loyaltyWidget) {
    QVBoxLayout* layout = new QVBoxLayout(loyaltyWidget);
    
    loyaltyInfoText = new QTextEdit(this);
    loyaltyInfoText->setReadOnly(true);
    
    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    
    layout->addWidget(refreshBtn);
    layout->addWidget(loyaltyInfoText);
    
    connect(refreshBtn, &QPushButton::clicked, this, &PassengerWindow::updateLoyaltyInfo);
}

void PassengerWindow::loadData() {
    loadProfile();
    refreshMyReservations();
    updateLoyaltyInfo();
}

void PassengerWindow::loadProfile() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto user = db->getUser(passengerId);
    
    if (user) {
        Passenger* passenger = dynamic_cast<Passenger*>(user.get());
        if (passenger) {
            fullNameEdit->setText(passenger->getFullName());
            emailEdit->setText(passenger->getEmail());
            phoneEdit->setText(passenger->getPhone());
        }
    }
}

void PassengerWindow::onSearchFlights() {
    QString origin = originEdit->text().trimmed();
    QString destination = destinationEdit->text().trimmed();
    QDate date = dateEdit->date();
    
    if (origin.isEmpty() || destination.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter both origin and destination.");
        return;
    }
    
    DatabaseManager* db = DatabaseManager::getInstance();
    QVector<Flight> flights = db->searchFlights(origin, destination, date);
    
    searchResultsTable->setRowCount(flights.size());
    
    for (int i = 0; i < flights.size(); ++i) {
        const Flight& flight = flights[i];
        searchResultsTable->setItem(i, 0, new QTableWidgetItem(flight.getFlightNumber()));
        searchResultsTable->setItem(i, 1, new QTableWidgetItem(flight.getOrigin()));
        searchResultsTable->setItem(i, 2, new QTableWidgetItem(flight.getDestination()));
        searchResultsTable->setItem(i, 3, new QTableWidgetItem(
            flight.getDepartureDateTime().toString("yyyy-MM-dd HH:mm")));
        searchResultsTable->setItem(i, 4, new QTableWidgetItem(
            flight.getArrivalDateTime().toString("yyyy-MM-dd HH:mm")));
        searchResultsTable->setItem(i, 5, new QTableWidgetItem(
            QString::number(flight.getAvailableSeats())));
        searchResultsTable->setItem(i, 6, new QTableWidgetItem(
            QString("$%1").arg(flight.getBasePrice(), 0, 'f', 2)));
    }
    
    if (flights.isEmpty()) {
        QMessageBox::information(this, "No Results", "No flights found matching your criteria.");
    }
}

void PassengerWindow::onBookFlight() {
    int row = searchResultsTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a flight to book.");
        return;
    }
    
    QString flightNumber = searchResultsTable->item(row, 0)->text();
    
    DatabaseManager* db = DatabaseManager::getInstance();
    Flight* flight = db->getFlight(flightNumber);
    auto user = db->getUser(passengerId);
    
    if (!flight || !user) {
        QMessageBox::warning(this, "Error", "Flight or user not found.");
        return;
    }
    
    Passenger* passenger = dynamic_cast<Passenger*>(user.get());
    if (!passenger) {
        QMessageBox::warning(this, "Error", "Invalid passenger account.");
        return;
    }
    
    // Ask for seat number
    bool ok;
    QString seatNumber = QInputDialog::getText(this, "Seat Selection",
                                               "Enter seat number (e.g., 12A):",
                                               QLineEdit::Normal, "", &ok);
    
    if (!ok || seatNumber.isEmpty()) return;
    
    if (!flight->bookSeat(seatNumber)) {
        QMessageBox::warning(this, "Error", "Seat is not available or invalid.");
        return;
    }
    
    // Payment method
    QStringList methods = {"Credit Card", "Debit Card", "PayPal", "Bank Transfer"};
    QString paymentMethod = QInputDialog::getItem(this, "Payment Method",
                                                   "Select payment method:",
                                                   methods, 0, false, &ok);
    if (!ok) {
        flight->releaseSeat(seatNumber);
        return;
    }
    
    Reservation reservation;
    reservation.setReservationId(db->generateUniqueId("RES"));
    reservation.setPassengerId(passengerId);
    reservation.setPassengerName(passenger->getFullName());
    reservation.setFlightNumber(flightNumber);
    reservation.setSeatNumber(seatNumber);
    reservation.setBookingDateTime(QDateTime::currentDateTime());
    reservation.setPaymentAmount(flight->getBasePrice());
    
    // Convert payment method string to enum
    PaymentMethod pmEnum = PaymentMethod::CreditCard;
    if (paymentMethod == "Debit Card") pmEnum = PaymentMethod::DebitCard;
    else if (paymentMethod == "PayPal") pmEnum = PaymentMethod::PayPal;
    else if (paymentMethod == "Bank Transfer") pmEnum = PaymentMethod::Cash;
    
    reservation.setPaymentMethod(pmEnum);
    reservation.setStatus(ReservationStatus::Confirmed);
    
    if (db->addReservation(reservation)) {
        db->updateFlight(*flight);
        
        // Add loyalty points (1 point per $10 spent)
        int points = static_cast<int>(flight->getBasePrice() / 10);
        passenger->addLoyaltyPoints(points);
        passenger->addToTravelHistory(flightNumber);
        db->updateUser(user);
        
        QMessageBox::information(this, "Success", 
            QString("Booking confirmed!\nReservation ID: %1\nTotal: $%2\nLoyalty Points Earned: %3")
            .arg(reservation.getReservationId())
            .arg(reservation.getPaymentAmount(), 0, 'f', 2)
            .arg(points));
        
        refreshMyReservations();
        updateLoyaltyInfo();
    } else {
        flight->releaseSeat(seatNumber);
        QMessageBox::warning(this, "Error", "Failed to create reservation.");
    }
}

void PassengerWindow::refreshMyReservations() {
    DatabaseManager* db = DatabaseManager::getInstance();
    QVector<Reservation> reservations = db->getReservationsByPassenger(passengerId);
    
    myReservationsTable->setRowCount(reservations.size());
    
    for (int i = 0; i < reservations.size(); ++i) {
        const Reservation& res = reservations[i];
        myReservationsTable->setItem(i, 0, new QTableWidgetItem(res.getReservationId()));
        myReservationsTable->setItem(i, 1, new QTableWidgetItem(res.getFlightNumber()));
        myReservationsTable->setItem(i, 2, new QTableWidgetItem(res.getSeatNumber()));
        myReservationsTable->setItem(i, 3, new QTableWidgetItem(
            QString("$%1").arg(res.getPaymentAmount(), 0, 'f', 2)));
        myReservationsTable->setItem(i, 4, new QTableWidgetItem(
            Reservation::statusToString(res.getStatus())));
        myReservationsTable->setItem(i, 5, new QTableWidgetItem(
            res.getBookingDateTime().toString("yyyy-MM-dd HH:mm")));
        myReservationsTable->setItem(i, 6, new QTableWidgetItem(res.getPaymentMethodString()));
    }
}

void PassengerWindow::onCancelReservation() {
    int row = myReservationsTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a reservation to cancel.");
        return;
    }
    
    QString reservationId = myReservationsTable->item(row, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Cancellation",
        "Are you sure you want to cancel this reservation?\nRefund will be processed according to policy.",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        DatabaseManager* db = DatabaseManager::getInstance();
        Reservation* res = db->getReservation(reservationId);
        
        if (res) {
            res->cancel();
            
            // Release seat
            Flight* flight = db->getFlight(res->getFlightNumber());
            if (flight) {
                flight->releaseSeat(res->getSeatNumber());
                db->updateFlight(*flight);
            }
            
            db->updateReservation(*res);
            
            QMessageBox::information(this, "Success", "Reservation cancelled successfully.");
            refreshMyReservations();
        }
    }
}

void PassengerWindow::onCheckin() {
    QString reservationId = reservationIdEdit->text().trimmed();
    
    if (reservationId.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a reservation ID.");
        return;
    }
    
    DatabaseManager* db = DatabaseManager::getInstance();
    Reservation* res = db->getReservation(reservationId);
    
    if (!res || res->getPassengerId() != passengerId) {
        QMessageBox::warning(this, "Error", "Reservation not found or does not belong to you.");
        return;
    }
    
    if (res->getStatus() != ReservationStatus::Confirmed) {
        QMessageBox::warning(this, "Error", 
            QString("Cannot check in. Current status: %1")
            .arg(Reservation::statusToString(res->getStatus())));
        return;
    }
    
    Flight* flight = db->getFlight(res->getFlightNumber());
    if (!flight) {
        QMessageBox::warning(this, "Error", "Flight not found.");
        return;
    }
    
    res->checkIn();
    db->updateReservation(*res);
    
    // Generate boarding pass
    QString boardingPass = "<h2>Boarding Pass</h2>";
    boardingPass += "<hr>";
    boardingPass += QString("<p><b>Passenger:</b> %1</p>").arg(res->getPassengerName());
    boardingPass += QString("<p><b>Flight:</b> %1</p>").arg(res->getFlightNumber());
    boardingPass += QString("<p><b>From:</b> %1</p>").arg(flight->getOrigin());
    boardingPass += QString("<p><b>To:</b> %1</p>").arg(flight->getDestination());
    boardingPass += QString("<p><b>Departure:</b> %1</p>")
                    .arg(flight->getDepartureDateTime().toString("yyyy-MM-dd HH:mm"));
    boardingPass += QString("<p><b>Seat:</b> %1</p>").arg(res->getSeatNumber());
    boardingPass += QString("<p><b>Gate:</b> %1</p>").arg(flight->getGate());
    boardingPass += "<hr>";
    boardingPass += "<p><i>Please arrive at the gate 30 minutes before departure.</i></p>";
    
    boardingPassText->setHtml(boardingPass);
    
    QMessageBox::information(this, "Success", "Check-in successful! Your boarding pass is displayed below.");
    refreshMyReservations();
}

void PassengerWindow::onUpdateProfile() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto user = db->getUser(passengerId);
    
    if (!user) {
        QMessageBox::warning(this, "Error", "User not found.");
        return;
    }
    
    Passenger* passenger = dynamic_cast<Passenger*>(user.get());
    if (!passenger) {
        QMessageBox::warning(this, "Error", "Invalid passenger account.");
        return;
    }
    
    passenger->setFullName(fullNameEdit->text().trimmed());
    passenger->setEmail(emailEdit->text().trimmed());
    passenger->setPhone(phoneEdit->text().trimmed());
    
    if (db->updateUser(user)) {
        QMessageBox::information(this, "Success", "Profile updated successfully.");
    } else {
        QMessageBox::warning(this, "Error", "Failed to update profile.");
    }
}

void PassengerWindow::updateLoyaltyInfo() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto user = db->getUser(passengerId);
    
    if (!user) return;
    
    Passenger* passenger = dynamic_cast<Passenger*>(user.get());
    if (!passenger) return;
    
    QString info = "<h2>Loyalty Program</h2>";
    info += QString("<p><b>Current Points:</b> %1</p>").arg(passenger->getLoyaltyPoints());
    
    // Determine tier
    int points = passenger->getLoyaltyPoints();
    QString tier;
    if (points < 1000) tier = "Silver";
    else if (points < 5000) tier = "Gold";
    else tier = "Platinum";
    
    info += QString("<p><b>Membership Tier:</b> %1</p>").arg(tier);
    info += "<hr>";
    info += "<h3>Travel History:</h3><ul>";
    
    for (const QString& flight : passenger->getTravelHistory()) {
        info += QString("<li>%1</li>").arg(flight);
    }
    
    info += "</ul>";
    info += "<hr>";
    info += "<p><i>Earn 1 point for every $10 spent on flights!</i></p>";
    
    loyaltyInfoText->setHtml(info);
}
