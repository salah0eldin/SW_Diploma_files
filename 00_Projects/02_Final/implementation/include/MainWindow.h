#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "User.h"
#include "AdministratorWindow.h"
#include "BookingAgentWindow.h"
#include "PassengerWindow.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    QStackedWidget* stackedWidget;
    QLabel* userInfoLabel;
    QPushButton* logoutButton;
    QString currentUserId;
    UserRole currentUserRole;
    AdministratorWindow* administratorWindow;
    BookingAgentWindow* bookingAgentWindow;
    PassengerWindow* passengerWindow;
    
    void setupUi();
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    void setCurrentUser(const QString& userId, UserRole role);
    
private slots:
    void onLogoutClicked();
    
signals:
    void logoutRequested();
};

#endif // MAINWINDOW_H
