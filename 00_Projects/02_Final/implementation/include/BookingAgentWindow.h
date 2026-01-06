#ifndef BOOKINGAGENTWINDOW_H
#define BOOKINGAGENTWINDOW_H

#include <QWidget>
#include <QTabWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QDateEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QLabel>

class BookingAgentWindow : public QWidget {
    Q_OBJECT

private:
    QTabWidget* tabWidget;
    QString agentId;
    
    // Search widgets
    QLineEdit* originEdit;
    QLineEdit* destinationEdit;
    QDateEdit* dateEdit;
    QTableWidget* searchResultsTable;
    
    // Book widgets
    QLineEdit* passengerNameEdit;
    QLineEdit* flightNumberEdit;
    QLineEdit* seatNumberEdit;
    QComboBox* paymentMethodCombo;
    
    // Reservations
    QTableWidget* reservationsTable;
    
    // Statistics
    QTextEdit* statsTextEdit;
    
    void setupUi();
    void setupSearchTab(QWidget* searchWidget);
    void setupBookTab(QWidget* bookWidget);
    void setupReservationsTab();
    void setupStatisticsTab(QWidget* statsWidget);
    void loadData();
    
private slots:
    void onSearchFlights();
    void onBookFlight();
    void refreshReservations();
    void onCancelReservation();
    void updateStatistics();
    
public:
    explicit BookingAgentWindow(const QString& agentId, QWidget *parent = nullptr);
    ~BookingAgentWindow();
};

#endif // BOOKINGAGENTWINDOW_H
