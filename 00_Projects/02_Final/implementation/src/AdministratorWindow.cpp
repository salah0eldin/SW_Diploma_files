#include "AdministratorWindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>
#include <QHeaderView>
#include <QInputDialog>

AdministratorWindow::AdministratorWindow(QWidget *parent)
    : QWidget(parent) {
    setupUi();
    loadData();
}

AdministratorWindow::~AdministratorWindow() {
}

void AdministratorWindow::setupUi() {
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
    
    QLabel* titleLabel = new QLabel("🎯 Administrator Dashboard", this);
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
    
    // Users Tab
    usersTable = new QTableWidget(this);
    setupUsersTab();
    tabWidget->addTab(usersTable, "Users");
    
    // Flights Tab
    flightsTable = new QTableWidget(this);
    setupFlightsTab();
    tabWidget->addTab(flightsTable, "Flights");
    
    // Aircraft Tab
    aircraftTable = new QTableWidget(this);
    setupAircraftTab();
    tabWidget->addTab(aircraftTable, "Aircraft");
    
    // Crew Tab
    crewTable = new QTableWidget(this);
    setupCrewTab();
    tabWidget->addTab(crewTable, "Crew");
    
    // Reports Tab
    QWidget* reportsWidget = new QWidget(this);
    setupReportsTab(reportsWidget);
    tabWidget->addTab(reportsWidget, "Reports");
    
    mainLayout->addWidget(tabWidget);
}

void AdministratorWindow::setupUsersTab() {
    QWidget* usersWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(usersWidget);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addUserBtn = new QPushButton("Add User", this);
    QPushButton* editUserBtn = new QPushButton("Edit User", this);
    QPushButton* deleteUserBtn = new QPushButton("Delete User", this);
    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    
    buttonLayout->addWidget(addUserBtn);
    buttonLayout->addWidget(editUserBtn);
    buttonLayout->addWidget(deleteUserBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshBtn);
    
    layout->addLayout(buttonLayout);
    
    // Table
    usersTable->setColumnCount(6);
    usersTable->setHorizontalHeaderLabels({"User ID", "Username", "Role", "Active", "Created At", "Type"});
    usersTable->horizontalHeader()->setStretchLastSection(true);
    usersTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    usersTable->setSelectionMode(QAbstractItemView::SingleSelection);
    usersTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    layout->addWidget(usersTable);
    
    connect(refreshBtn, &QPushButton::clicked, this, &AdministratorWindow::refreshUsersTable);
    connect(deleteUserBtn, &QPushButton::clicked, this, &AdministratorWindow::onDeleteUser);
}

void AdministratorWindow::setupFlightsTab() {
    QWidget* flightsWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(flightsWidget);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addFlightBtn = new QPushButton("Add Flight", this);
    QPushButton* editFlightBtn = new QPushButton("Edit Flight", this);
    QPushButton* deleteFlightBtn = new QPushButton("Delete Flight", this);
    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    
    buttonLayout->addWidget(addFlightBtn);
    buttonLayout->addWidget(editFlightBtn);
    buttonLayout->addWidget(deleteFlightBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshBtn);
    
    layout->addLayout(buttonLayout);
    
    // Table
    flightsTable->setColumnCount(8);
    flightsTable->setHorizontalHeaderLabels({
        "Flight Number", "Origin", "Destination", "Departure", "Arrival", "Status", "Aircraft", "Gate"
    });
    flightsTable->horizontalHeader()->setStretchLastSection(true);
    flightsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    flightsTable->setSelectionMode(QAbstractItemView::SingleSelection);
    flightsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    layout->addWidget(flightsTable);
    
    connect(refreshBtn, &QPushButton::clicked, this, &AdministratorWindow::refreshFlightsTable);
    connect(deleteFlightBtn, &QPushButton::clicked, this, &AdministratorWindow::onDeleteFlight);
}

void AdministratorWindow::setupAircraftTab() {
    QWidget* aircraftWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(aircraftWidget);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addAircraftBtn = new QPushButton("Add Aircraft", this);
    QPushButton* editAircraftBtn = new QPushButton("Edit Aircraft", this);
    QPushButton* deleteAircraftBtn = new QPushButton("Delete Aircraft", this);
    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    
    buttonLayout->addWidget(addAircraftBtn);
    buttonLayout->addWidget(editAircraftBtn);
    buttonLayout->addWidget(deleteAircraftBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshBtn);
    
    layout->addLayout(buttonLayout);
    
    // Table
    aircraftTable->setColumnCount(7);
    aircraftTable->setHorizontalHeaderLabels({
        "Aircraft ID", "Type", "Manufacturer", "Total Seats", "Last Maintenance", "Next Maintenance", "Status"
    });
    aircraftTable->horizontalHeader()->setStretchLastSection(true);
    aircraftTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    aircraftTable->setSelectionMode(QAbstractItemView::SingleSelection);
    aircraftTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    layout->addWidget(aircraftTable);
    
    connect(refreshBtn, &QPushButton::clicked, this, &AdministratorWindow::refreshAircraftTable);
    connect(deleteAircraftBtn, &QPushButton::clicked, this, &AdministratorWindow::onDeleteAircraft);
}

void AdministratorWindow::setupCrewTab() {
    QWidget* crewWidget = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(crewWidget);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* addCrewBtn = new QPushButton("Add Crew", this);
    QPushButton* editCrewBtn = new QPushButton("Edit Crew", this);
    QPushButton* deleteCrewBtn = new QPushButton("Delete Crew", this);
    QPushButton* refreshBtn = new QPushButton("Refresh", this);
    
    buttonLayout->addWidget(addCrewBtn);
    buttonLayout->addWidget(editCrewBtn);
    buttonLayout->addWidget(deleteCrewBtn);
    buttonLayout->addStretch();
    buttonLayout->addWidget(refreshBtn);
    
    layout->addLayout(buttonLayout);
    
    // Table
    crewTable->setColumnCount(6);
    crewTable->setHorizontalHeaderLabels({
        "Crew ID", "Name", "Type", "Flight Hours", "Max Hours", "Available"
    });
    crewTable->horizontalHeader()->setStretchLastSection(true);
    crewTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    crewTable->setSelectionMode(QAbstractItemView::SingleSelection);
    crewTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    layout->addWidget(crewTable);
    
    connect(refreshBtn, &QPushButton::clicked, this, &AdministratorWindow::refreshCrewTable);
    connect(deleteCrewBtn, &QPushButton::clicked, this, &AdministratorWindow::onDeleteCrew);
}

void AdministratorWindow::setupReportsTab(QWidget* reportsWidget) {
    QVBoxLayout* layout = new QVBoxLayout(reportsWidget);
    
    reportsTextEdit = new QTextEdit(this);
    reportsTextEdit->setReadOnly(true);
    
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* flightReportBtn = new QPushButton("Flight Report", this);
    QPushButton* revenueReportBtn = new QPushButton("Revenue Report", this);
    QPushButton* passengerReportBtn = new QPushButton("Passenger Report", this);
    
    buttonLayout->addWidget(flightReportBtn);
    buttonLayout->addWidget(revenueReportBtn);
    buttonLayout->addWidget(passengerReportBtn);
    buttonLayout->addStretch();
    
    layout->addLayout(buttonLayout);
    layout->addWidget(reportsTextEdit);
    
    connect(flightReportBtn, &QPushButton::clicked, this, &AdministratorWindow::generateFlightReport);
    connect(revenueReportBtn, &QPushButton::clicked, this, &AdministratorWindow::generateRevenueReport);
    connect(passengerReportBtn, &QPushButton::clicked, this, &AdministratorWindow::generatePassengerReport);
}

void AdministratorWindow::loadData() {
    refreshUsersTable();
    refreshFlightsTable();
    refreshAircraftTable();
    refreshCrewTable();
}

void AdministratorWindow::refreshUsersTable() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto users = db->getAllUsers();
    
    usersTable->setRowCount(users.size());
    
    for (int i = 0; i < users.size(); ++i) {
        const auto& user = users[i];
        usersTable->setItem(i, 0, new QTableWidgetItem(user->getUserId()));
        usersTable->setItem(i, 1, new QTableWidgetItem(user->getUsername()));
        usersTable->setItem(i, 2, new QTableWidgetItem(User::roleToString(user->getRole())));
        usersTable->setItem(i, 3, new QTableWidgetItem(user->getIsActive() ? "Yes" : "No"));
        usersTable->setItem(i, 4, new QTableWidgetItem(user->getCreatedAt().toString("yyyy-MM-dd HH:mm")));
        
        QString type = "User";
        if (dynamic_cast<Passenger*>(user.get())) type = "Passenger";
        else if (dynamic_cast<Administrator*>(user.get())) type = "Administrator";
        else if (dynamic_cast<BookingAgent*>(user.get())) type = "BookingAgent";
        
        usersTable->setItem(i, 5, new QTableWidgetItem(type));
    }
}

void AdministratorWindow::refreshFlightsTable() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto flights = db->getAllFlights();
    
    flightsTable->setRowCount(flights.size());
    
    for (int i = 0; i < flights.size(); ++i) {
        const Flight& flight = flights[i];
        flightsTable->setItem(i, 0, new QTableWidgetItem(flight.getFlightNumber()));
        flightsTable->setItem(i, 1, new QTableWidgetItem(flight.getOrigin()));
        flightsTable->setItem(i, 2, new QTableWidgetItem(flight.getDestination()));
        flightsTable->setItem(i, 3, new QTableWidgetItem(flight.getDepartureDateTime().toString("yyyy-MM-dd HH:mm")));
        flightsTable->setItem(i, 4, new QTableWidgetItem(flight.getArrivalDateTime().toString("yyyy-MM-dd HH:mm")));
        flightsTable->setItem(i, 5, new QTableWidgetItem(Flight::statusToString(flight.getStatus())));
        flightsTable->setItem(i, 6, new QTableWidgetItem(flight.getAircraftId()));
        flightsTable->setItem(i, 7, new QTableWidgetItem(flight.getGate()));
    }
}

void AdministratorWindow::refreshAircraftTable() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto aircraft = db->getAllAircraft();
    
    aircraftTable->setRowCount(aircraft.size());
    
    for (int i = 0; i < aircraft.size(); ++i) {
        const Aircraft& ac = aircraft[i];
        aircraftTable->setItem(i, 0, new QTableWidgetItem(ac.getAircraftId()));
        aircraftTable->setItem(i, 1, new QTableWidgetItem(ac.getAircraftType()));
        aircraftTable->setItem(i, 2, new QTableWidgetItem(ac.getManufacturer()));
        aircraftTable->setItem(i, 3, new QTableWidgetItem(QString::number(ac.getTotalSeats())));
        aircraftTable->setItem(i, 4, new QTableWidgetItem(ac.getLastMaintenanceDate().toString("yyyy-MM-dd")));
        aircraftTable->setItem(i, 5, new QTableWidgetItem(ac.getNextMaintenanceDate().toString("yyyy-MM-dd")));
        aircraftTable->setItem(i, 6, new QTableWidgetItem(ac.getStatus()));
    }
}

void AdministratorWindow::refreshCrewTable() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto crew = db->getAllCrew();
    
    crewTable->setRowCount(crew.size());
    
    for (int i = 0; i < crew.size(); ++i) {
        const Crew& c = crew[i];
        crewTable->setItem(i, 0, new QTableWidgetItem(c.getCrewId()));
        crewTable->setItem(i, 1, new QTableWidgetItem(c.getName()));
        crewTable->setItem(i, 2, new QTableWidgetItem(Crew::typeToString(c.getType())));
        crewTable->setItem(i, 3, new QTableWidgetItem(QString::number(c.getTotalFlightHours())));
        crewTable->setItem(i, 4, new QTableWidgetItem(QString::number(c.getMaxFlightHours())));
        crewTable->setItem(i, 5, new QTableWidgetItem(c.getIsAvailable() ? "Yes" : "No"));
    }
}

void AdministratorWindow::onDeleteUser() {
    int row = usersTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a user to delete.");
        return;
    }
    
    QString userId = usersTable->item(row, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Delete",
        QString("Are you sure you want to delete user '%1'?").arg(userId),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        DatabaseManager* db = DatabaseManager::getInstance();
        if (db->deleteUser(userId)) {
            QMessageBox::information(this, "Success", "User deleted successfully.");
            refreshUsersTable();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete user.");
        }
    }
}

void AdministratorWindow::onDeleteFlight() {
    int row = flightsTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a flight to delete.");
        return;
    }
    
    QString flightNumber = flightsTable->item(row, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Delete",
        QString("Are you sure you want to delete flight '%1'?").arg(flightNumber),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        DatabaseManager* db = DatabaseManager::getInstance();
        if (db->deleteFlight(flightNumber)) {
            QMessageBox::information(this, "Success", "Flight deleted successfully.");
            refreshFlightsTable();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete flight.");
        }
    }
}

void AdministratorWindow::onDeleteAircraft() {
    int row = aircraftTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select an aircraft to delete.");
        return;
    }
    
    QString aircraftId = aircraftTable->item(row, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Delete",
        QString("Are you sure you want to delete aircraft '%1'?").arg(aircraftId),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        DatabaseManager* db = DatabaseManager::getInstance();
        if (db->deleteAircraft(aircraftId)) {
            QMessageBox::information(this, "Success", "Aircraft deleted successfully.");
            refreshAircraftTable();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete aircraft.");
        }
    }
}

void AdministratorWindow::onDeleteCrew() {
    int row = crewTable->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "No Selection", "Please select a crew member to delete.");
        return;
    }
    
    QString crewId = crewTable->item(row, 0)->text();
    
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Confirm Delete",
        QString("Are you sure you want to delete crew member '%1'?").arg(crewId),
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        DatabaseManager* db = DatabaseManager::getInstance();
        if (db->deleteCrew(crewId)) {
            QMessageBox::information(this, "Success", "Crew member deleted successfully.");
            refreshCrewTable();
        } else {
            QMessageBox::warning(this, "Error", "Failed to delete crew member.");
        }
    }
}

void AdministratorWindow::generateFlightReport() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto flights = db->getAllFlights();
    
    QString report = "<h2>Flight Report</h2>";
    report += QString("<p>Total Flights: %1</p>").arg(flights.size());
    
    int scheduled = 0, departed = 0, completed = 0, delayed = 0, canceled = 0;
    
    for (const Flight& flight : flights) {
        switch (flight.getStatus()) {
            case FlightStatus::Scheduled: scheduled++; break;
            case FlightStatus::Departed: departed++; break;
            case FlightStatus::Completed: completed++; break;
            case FlightStatus::Delayed: delayed++; break;
            case FlightStatus::Canceled: canceled++; break;
            default: break;
        }
    }
    
    report += "<h3>Status Breakdown:</h3><ul>";
    report += QString("<li>Scheduled: %1</li>").arg(scheduled);
    report += QString("<li>Departed: %1</li>").arg(departed);
    report += QString("<li>Completed: %1</li>").arg(completed);
    report += QString("<li>Delayed: %1</li>").arg(delayed);
    report += QString("<li>Canceled: %1</li>").arg(canceled);
    report += "</ul>";
    
    reportsTextEdit->setHtml(report);
}

void AdministratorWindow::generateRevenueReport() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto reservations = db->getAllReservations();
    
    double totalRevenue = 0;
    int confirmedBookings = 0;
    
    for (const Reservation& res : reservations) {
        if (res.getStatus() == ReservationStatus::Confirmed || 
            res.getStatus() == ReservationStatus::CheckedIn ||
            res.getStatus() == ReservationStatus::Completed) {
            totalRevenue += res.getPaymentAmount();
            confirmedBookings++;
        }
    }
    
    QString report = "<h2>Revenue Report</h2>";
    report += QString("<p>Total Reservations: %1</p>").arg(reservations.size());
    report += QString("<p>Confirmed Bookings: %1</p>").arg(confirmedBookings);
    report += QString("<p>Total Revenue: $%1</p>").arg(totalRevenue, 0, 'f', 2);
    report += QString("<p>Average Booking Value: $%1</p>")
              .arg(confirmedBookings > 0 ? totalRevenue / confirmedBookings : 0, 0, 'f', 2);
    
    reportsTextEdit->setHtml(report);
}

void AdministratorWindow::generatePassengerReport() {
    DatabaseManager* db = DatabaseManager::getInstance();
    auto passengers = db->getAllPassengers();
    
    QString report = "<h2>Passenger Report</h2>";
    report += QString("<p>Total Passengers: %1</p>").arg(passengers.size());
    
    int totalLoyaltyPoints = 0;
    for (const auto& passenger : passengers) {
        totalLoyaltyPoints += passenger->getLoyaltyPoints();
    }
    
    report += QString("<p>Total Loyalty Points: %1</p>").arg(totalLoyaltyPoints);
    report += QString("<p>Average Loyalty Points: %1</p>")
              .arg(passengers.size() > 0 ? totalLoyaltyPoints / passengers.size() : 0);
    
    reportsTextEdit->setHtml(report);
}
