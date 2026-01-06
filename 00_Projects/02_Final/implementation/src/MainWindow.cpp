#include "MainWindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      administratorWindow(nullptr),
      bookingAgentWindow(nullptr),
      passengerWindow(nullptr) {
    setupUi();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUi() {
    setWindowTitle("Airline Management System");
    setMinimumSize(1280, 850);
    
    // Modern styling
    setStyleSheet(
        "QMainWindow { background-color: #f5f5f5; }"
        "QWidget { font-family: 'Segoe UI', Arial; }"
        "QTabWidget::pane { "
        "   border: 1px solid #e0e0e0; "
        "   background: white; "
        "   border-radius: 8px; "
        "}"
        "QTabBar::tab { "
        "   background: #f5f5f5; "
        "   color: #666; "
        "   padding: 12px 24px; "
        "   margin-right: 4px; "
        "   border-top-left-radius: 6px; "
        "   border-top-right-radius: 6px; "
        "   font-weight: 500; "
        "}"
        "QTabBar::tab:selected { "
        "   background: white; "
        "   color: #0f4c75; "
        "   font-weight: bold; "
        "}"
        "QTabBar::tab:hover { "
        "   background: #e8e8e8; "
        "}"
        "QTableWidget { "
        "   background-color: white; "
        "   gridline-color: #e0e0e0; "
        "   border: none; "
        "   border-radius: 6px; "
        "}"
        "QTableWidget::item { "
        "   padding: 8px; "
        "   border-bottom: 1px solid #f0f0f0; "
        "}"
        "QTableWidget::item:selected { "
        "   background-color: #e3f2fd; "
        "   color: #0f4c75; "
        "}"
        "QHeaderView::section { "
        "   background-color: #f5f5f5; "
        "   color: #333; "
        "   padding: 10px; "
        "   border: none; "
        "   border-bottom: 2px solid #0f4c75; "
        "   font-weight: bold; "
        "}"
        "QPushButton { "
        "   background-color: #0f4c75; "
        "   color: white; "
        "   border: none; "
        "   border-radius: 6px; "
        "   padding: 10px 20px; "
        "   font-weight: 500; "
        "}"
        "QPushButton:hover { "
        "   background-color: #3282b8; "
        "}"
        "QPushButton:pressed { "
        "   background-color: #0a3a5c; "
        "}"
        "QLineEdit, QDateEdit, QComboBox { "
        "   padding: 8px; "
        "   border: 1px solid #ddd; "
        "   border-radius: 4px; "
        "   background: white; "
        "}"
        "QLineEdit:focus, QDateEdit:focus, QComboBox:focus { "
        "   border: 2px solid #0f4c75; "
        "}"
        "QTextEdit { "
        "   border: 1px solid #ddd; "
        "   border-radius: 6px; "
        "   background: white; "
        "   padding: 10px; "
        "}"
    );
    
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setStyleSheet("background-color: #f5f5f5;");
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    
    // Top bar with gradient
    QWidget* topBar = new QWidget(this);
    topBar->setStyleSheet(
        "QWidget { "
        "   background: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #0f4c75, stop:1 #3282b8); "
        "}"
    );
    topBar->setFixedHeight(70);
    QHBoxLayout* topBarLayout = new QHBoxLayout(topBar);
    topBarLayout->setContentsMargins(30, 0, 30, 0);
    
    // Logo
    QLabel* logoLabel = new QLabel("✈️", this);
    QFont logoFont = logoLabel->font();
    logoFont.setPointSize(24);
    logoLabel->setFont(logoFont);
    logoLabel->setStyleSheet("background: transparent;");
    topBarLayout->addWidget(logoLabel);
    
    topBarLayout->addSpacing(15);
    
    userInfoLabel = new QLabel(this);
    QFont labelFont = userInfoLabel->font();
    labelFont.setPointSize(12);
    labelFont.setBold(true);
    userInfoLabel->setFont(labelFont);
    userInfoLabel->setStyleSheet("color: white; background: transparent;");
    topBarLayout->addWidget(userInfoLabel);
    
    topBarLayout->addStretch();
    
    logoutButton = new QPushButton("LOGOUT", this);
    logoutButton->setStyleSheet(
        "QPushButton {"
        "   background-color: rgba(255, 255, 255, 0.2);"
        "   color: white;"
        "   border: 2px solid rgba(255, 255, 255, 0.3);"
        "   padding: 10px 24px;"
        "   font-weight: bold;"
        "   border-radius: 6px;"
        "   font-size: 11px;"
        "   letter-spacing: 1px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(255, 255, 255, 0.3);"
        "   border: 2px solid white;"
        "}"
        "QPushButton:pressed {"
        "   background-color: rgba(255, 255, 255, 0.1);"
        "}"
    );
    logoutButton->setCursor(Qt::PointingHandCursor);
    topBarLayout->addWidget(logoutButton);
    
    mainLayout->addWidget(topBar);
    
    // Stacked widget for different views
    stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(stackedWidget);
    
    // Connect logout button
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::onLogoutClicked);
}

void MainWindow::setCurrentUser(const QString& userId, UserRole role) {
    currentUserId = userId;
    currentUserRole = role;
    
    DatabaseManager* db = DatabaseManager::getInstance();
    auto user = db->getUser(userId);
    
    if (user) {
        QString roleName;
        switch (role) {
            case UserRole::Administrator:
                roleName = "Administrator";
                break;
            case UserRole::BookingAgent:
                roleName = "Booking Agent";
                break;
            case UserRole::Passenger:
                roleName = "Passenger";
                break;
        }
        
        userInfoLabel->setText(QString("Logged in as: %1 (%2)")
                               .arg(user->getUsername())
                               .arg(roleName));
    }
    
    // Clear existing widgets
    while (stackedWidget->count() > 0) {
        QWidget* widget = stackedWidget->widget(0);
        stackedWidget->removeWidget(widget);
        delete widget;
    }
    
    // Create appropriate window based on role
    switch (role) {
        case UserRole::Administrator:
            administratorWindow = new AdministratorWindow(this);
            stackedWidget->addWidget(administratorWindow);
            break;
            
        case UserRole::BookingAgent:
            bookingAgentWindow = new BookingAgentWindow(userId, this);
            stackedWidget->addWidget(bookingAgentWindow);
            break;
            
        case UserRole::Passenger:
            passengerWindow = new PassengerWindow(userId, this);
            stackedWidget->addWidget(passengerWindow);
            break;
    }
    
    stackedWidget->setCurrentIndex(0);
}

void MainWindow::onLogoutClicked() {
    QMessageBox::StandardButton reply = QMessageBox::question(
        this,
        "Logout",
        "Are you sure you want to logout?",
        QMessageBox::Yes | QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        currentUserId.clear();
        emit logoutRequested();
        close();
    }
}
