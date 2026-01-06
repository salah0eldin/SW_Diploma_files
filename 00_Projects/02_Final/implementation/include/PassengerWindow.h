#ifndef PASSENGERWINDOW_H
#define PASSENGERWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QLabel>
#include <QTextEdit>
#include <QFormLayout>
#include <QComboBox>
#include <QInputDialog>

class PassengerWindow : public QWidget {
    Q_OBJECT

private:
    QTabWidget* tabWidget;
    QString passengerId;
    
    // Search widgets
    QLineEdit* originEdit;
    QLineEdit* destinationEdit;
    QDateEdit* dateEdit;
    QTableWidget* searchResultsTable;
    
    // Reservations
    QTableWidget* myReservationsTable;
    
    // Check-in
    QLineEdit* reservationIdEdit;
    QTextEdit* boardingPassText;
    
    // Profile
    QFormLayout* profileForm;
    QLineEdit* fullNameEdit;
    QLineEdit* emailEdit;
    QLineEdit* phoneEdit;
    
    // Loyalty
    QTextEdit* loyaltyInfoText;
    
    void setupUi();
    void setupSearchTab(QWidget* searchWidget);
    void setupReservationsTab();
    void setupCheckinTab(QWidget* checkinWidget);
    void setupProfileTab(QWidget* profileWidget);
    void setupLoyaltyTab(QWidget* loyaltyWidget);
    void loadData();
    void loadProfile();
    
private slots:
    void onSearchFlights();
    void onBookFlight();
    void refreshMyReservations();
    void onCancelReservation();
    void onCheckin();
    void onUpdateProfile();
    void updateLoyaltyInfo();
    
public:
    explicit PassengerWindow(const QString& passengerId, QWidget *parent = nullptr);
    ~PassengerWindow();
};

#endif // PASSENGERWINDOW_H
