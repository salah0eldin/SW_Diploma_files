#ifndef ADMINISTRATORWINDOW_H
#define ADMINISTRATORWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>

class AdministratorWindow : public QWidget {
    Q_OBJECT

private:
    QTabWidget* tabWidget;
    QString adminId;
    
    // Tables
    QTableWidget* usersTable;
    QTableWidget* flightsTable;
    QTableWidget* aircraftTable;
    QTableWidget* crewTable;
    QTextEdit* reportsTextEdit;
    
    // Private helper methods
    void setupUi();
    void setupUsersTab();
    void setupFlightsTab();
    void setupAircraftTab();
    void setupCrewTab();
    void setupReportsTab(QWidget* reportsWidget);
    void loadData();
    
private slots:
    void refreshUsersTable();
    void refreshFlightsTable();
    void refreshAircraftTable();
    void refreshCrewTable();
    void onDeleteUser();
    void onDeleteFlight();
    void onDeleteAircraft();
    void onDeleteCrew();
    void generateFlightReport();
    void generateRevenueReport();
    void generatePassengerReport();
    
public:
    explicit AdministratorWindow(QWidget *parent = nullptr);
    ~AdministratorWindow();
};

#endif // ADMINISTRATORWINDOW_H
