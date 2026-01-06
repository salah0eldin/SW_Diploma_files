#include <QApplication>
#include <QMessageBox>
#include "LoginWindow.h"
#include "MainWindow.h"
#include "DatabaseManager.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    // Set application information
    QApplication::setApplicationName("Airline Reservation System");
    QApplication::setApplicationVersion("1.0.0");
    QApplication::setOrganizationName("Software Engineering Diploma");
    
    try {
        // Initialize database
        DatabaseManager* db = DatabaseManager::getInstance();
        db->loadAll();
        
        // If no data exists, initialize with defaults
        if (db->getAllUsers().isEmpty()) {
            db->initializeDefaultData();
            QMessageBox::information(nullptr, "First Run", 
                "Database initialized with default data.\n\n"
                "Default users:\n"
                "Administrator: admin / admin123\n"
                "Booking Agent: agent / agent123\n"
                "Passenger: passenger / pass123");
        }
        
        // Create and show login window
        LoginWindow* loginWindow = new LoginWindow();
        
        // Create main window (hidden initially)
        MainWindow* mainWindow = new MainWindow();
        
        // Connect login success to main window
        QObject::connect(loginWindow, &LoginWindow::loginSuccessful,
                        [mainWindow, loginWindow](const QString& userId, UserRole role) {
            mainWindow->setCurrentUser(userId, role);
            mainWindow->show();
            loginWindow->close();
            loginWindow->deleteLater();
        });
        
        loginWindow->show();
        
        int result = app.exec();
        
        // Save all data before exit
        db->saveAll();
        
        return result;
        
    } catch (const std::exception& e) {
        QMessageBox::critical(nullptr, "Fatal Error", 
            QString("An error occurred: %1").arg(e.what()));
        return 1;
    }
}
