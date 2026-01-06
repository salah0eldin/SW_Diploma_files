#include "BookingAgentWindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QInputDialog>

BookingAgentWindow::BookingAgentWindow(const QString& agentId, QWidget *parent)
    : QWidget(parent), agentId(agentId) {
    setupUi();
    loadData();
}

BookingAgentWindow::~BookingAgentWindow() {
}

void BookingAgentWindow::setupUi() {
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
    
    QLabel* titleLabel = new QLabel("🎫 Booking Agent Dashboard", this);
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
    
    // Book Flight Tab
    QWidget* bookWidget = new QWidget(this);
    setupBookTab(bookWidget);
    tabWidget->addTab(bookWidget, "Book Flight");
    
    // Reservations Tab
    reservationsTable = new QTableWidget(this);
    setupReservationsTab();
    tabWidget->addTab(reservationsTable, "All Reservations");
    
    // Statistics Tab
    QWidget* statsWidget = new QWidget(this);
    setupStatisticsTab(statsWidget);
    tabWidget->addTab(statsWidget, "Statistics");
    
    mainLayout->addWidget(tabWidget);
}

void BookingAgentWindow::setupSearchTab(QWidget* searchWidget) {
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
    
    connect(searchBtn, &QPushButton::clicked, this, &BookingAgentWindow::onSearchFlights);
}

void BookingAgentWindow::setupBookTab(QWidget* bookWidget) {
    QVBoxLayout* layout = new QVBoxLayout(bookWidget);
    
    QFormLayout* formLayout = new QFormLayout();
    
    passengerNameEdit = new QLineEdit(this);
    flightNumberEdit = new QLineEdit(this);
    seatNumberEdit = new QLineEdit(this);
    paymentMethodCombo = new QComboBox(this);
    paymentMethodCombo->addItems({"Credit Card", "Debit Card", "Cash", "Bank Transfer"});
    
    formLayout->addRow("Passenger Name:", passengerNameEdit);
    formLayout->addRow("Flight Number:", flightNumberEdit);
    formLayout->addRow("Seat Number:", seatNumberEdit);
    formLayout->addRow("Payment Method:", paymentMethodCombo);
    
    QPushButton* bookBtn = new QPushButton("Book Flight", this);
    formLayout->addRow(bookBtn);
    
    layout->addLayout(formLayout);
    layout->addStretch();
    
    connect(bookBtn, &QPushButton::clicked, this, &BookingAgentWindow::onBookFlight);
}

void BookingAgentWindow::setupReservationsTab() {
    QVBoxLayout* layout = new QVBoxLayout();
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    QPushButton* cancelBtn = new QPushButton("Cancel Reservation", this);
    
    buttonLayout->addWidget(refreshBtn);
    buttonLayout->addWidget(cancelBtn);
    buttonLayout->addStretch();
    
    reservationsTable->setColumnCount(7);
    reservationsTable->setHorizontalHeaderLabels({
        "Reservation ID", "Passenger", "Flight", "Seat", "Amount", "Status", "Booking Date"
    });
    reservationsTable->horizontalHeader()->setStretchLastSection(true);
    reservationsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    reservationsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    connect(refreshBtn, &QPushButton::clicked, this, &BookingAgentWindow::refreshReservations);
    connect(cancelBtn, &QPushButton::clicked, this, &BookingAgentWindow::onCancelReservation);
}

void BookingAgentWindow::setupStatisticsTab(QWidget* statsWidget) {
    QVBoxLayout* layout = new QVBoxLayout(statsWidget);
    
    statsTextEdit = new QTextEdit(this);
    statsTextEdit->setReadOnly(true);
    
    QPushButton* refreshBtn = new QPushButton("Refresh Statistics", this);
    
    layout->addWidget(refreshBtn);
    layout->addWidget(statsTextEdit);
    
    connect(refreshBtn, &QPushButton::clicked, this, &BookingAgentWindow::updateStatistics);
}

void BookingAgentWindow::loadData() {
    refreshReservations();
    updateStatistics();
}

void BookingAgentWindow::onSearchFlights() {
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

void BookingAgentWindow::onBookFlight() {
    QString passengerName = passengerNameEdit->text().trimmed();
    QString flightNumber = flightNumberEdit->text().trimmed();
    QString seatNumber = seatNumberEdit->text().trimmed();
    QString paymentMethod = paymentMethodCombo->currentText();
    
    if (passengerName.isEmpty() || flightNumber.isEmpty() || seatNumber.isEmpty()) {
        QMessageBox::warning(this, "Invalid Input", "Please fill in all fields.");
        return;
    }
    
    DatabaseManager* db = DatabaseManager::getInstance();
    Flight* flight = db->getFlight(flightNumber);
    
    if (!flight) {
        QMessageBox::warning(this, "Error", "Flight not found.");
        return;
    }
    
    if (!flight->bookSeat(seatNumber)) {
        QMessageBox::warning(this, "Error", "Seat is not available or invalid.");
        return;
    }
    
    // Find passenger by name or create temporary passenger ID
    QString passengerId = "TEMP_" + QString::number(QDateTime::currentSecsSinceEpoch());
    
    Reservation reservation;
    reservation.setReservationId(db->generateUniqueId("RES"));
    reservation.setPassengerId(passengerId);
    reservation.setPassengerName(passengerName);
    reservation.setFlightNumber(flightNumber);
    reservation.setSeatNumber(seatNumber);
    reservation.setBookingDateTime(QDateTime::currentDateTime());
    reservation.setPaymentAmount(flight->getBasePrice());
    
    // Convert payment method string to enum
    PaymentMethod pmEnum = PaymentMethod::CreditCard;
    if (paymentMethod == "Debit Card") pmEnum = PaymentMethod::DebitCard;
    else if (paymentMethod == "Cash") pmEnum = PaymentMethod::Cash;
    else if (paymentMethod == "Bank Transfer") pmEnum = PaymentMethod::PayPal;
    
    reservation.setPaymentMethod(pmEnum);
    reservation.setStatus(ReservationStatus::Confirmed);
    
    if (db->addReservation(reservation)) {
        db->updateFlight(*flight);
        
        // Update agent statistics
        auto agent = std::static_pointer_cast<BookingAgent>(db->getUser(agentId));
        if (agent) {
            agent->recordBooking(flight->getBasePrice());
            db->updateUser(agent);
        }
        
        QMessageBox::information(this, "Success", 
            QString("Booking confirmed!\nReservation ID: %1\nTotal: $%2")
            .arg(reservation.getReservationId())
            .arg(reservation.getPaymentAmount(), 0, 'f', 2));
        
        // Clear form
        passengerNameEdit->clear();
        flightNumberEdit->clear();
        seatNumberEdit->clear();
        
        refreshReservations();
        updateStatistics();
    } else {
        flight->releaseSeat(seatNumber);
        QMessageBox::warning(this, "Error", "Failed to create reservation.");
    }
}

void BookingAgentWindow::refreshReservations() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto reservations = db->getAllReservations();
    
    reservationsTable->setRowCount(reservations.size());
    
    for (int i = 0; i < reservations.size(); ++i) {
        const Reservation& res = reservations[i];
        reservationsTable->setItem(i, 0, new QTableWidgetItem(res.getReservationId()));
        reservationsTable->setItem(i, 1, new QTableWidgetItem(res.getPassengerName()));
        reservationsTable->setItem(i, 2, new QTableWidgetItem(res.getFlightNumber()));
        reservationsTable->setItem(i, 3, new QTableWidgetItem(res.getSeatNumber()));
        reservationsTable->setItem(i, 4, new QTableWidgetItem(
            QString("$%1").arg(res.getPaymentAmount(), 0, 'f', 2)));
        reservationsTable->setItem(i, 5, new QTableWidgetItem(
            Reservation::statusToString(res.getStatus())));
        reservationsTable->setItem(i, 6, new QTableWidgetItem(
            res.getBookingDateTime().toString("yyyy-MM-dd HH:mm")));
    }
}

void BookingAgentWindow::onCancelReservation() {
    int row = reservationsTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a reservation to cancel.");
        return;
    }
    
    QString reservationId = reservationsTable->item(row, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Cancellation",
        "Are you sure you want to cancel this reservation?",
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
            refreshReservations();
        }
    }
}

void BookingAgentWindow::updateStatistics() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto agent = std::static_pointer_cast<BookingAgent>(db->getUser(agentId));
    
    if (!agent) return;
    
    auto allReservations = db->getAllReservations();
    int agentBookings = 0;
    double totalRevenue = 0;
    
    for (const Reservation& res : allReservations) {
        if (res.getStatus() != ReservationStatus::Canceled) {
            agentBookings++;
            totalRevenue += res.getPaymentAmount();
        }
    }
    
    QString stats = "<h2>Agent Statistics</h2>";
    stats += QString("<p><b>Agent ID:</b> %1</p>").arg(agent->getAgentId());
    stats += QString("<p><b>Agency:</b> %1</p>").arg(agent->getAgencyName());
    stats += QString("<p><b>Total Bookings:</b> %1</p>").arg(agent->getTotalBookings());
    stats += QString("<p><b>Commission Rate:</b> %1%</p>").arg(agent->getCommissionRate(), 0, 'f', 2);
    stats += QString("<p><b>Total Commission:</b> $%1</p>")
             .arg(agent->getTotalBookings() * agent->getCommissionRate() / 100, 0, 'f', 2);
    stats += "<hr>";
    stats += QString("<p><b>All Bookings in System:</b> %1</p>").arg(agentBookings);
    stats += QString("<p><b>Total System Revenue:</b> $%1</p>").arg(totalRevenue, 0, 'f', 2);
    
    statsTextEdit->setHtml(stats);
}
