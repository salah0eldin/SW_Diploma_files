#include "LoginWindow.h"
#include "DatabaseManager.h"
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUi();
}

LoginWindow::~LoginWindow() {
}

void LoginWindow::setupUi() {
    setWindowTitle("Airline Management System - Login");
    setFixedSize(500, 600);
    
    // Elegant dark theme with solid colors
    setStyleSheet(
        "QMainWindow { background-color: #0d1117; }"
        "QWidget { background-color: #0d1117; color: #e6edf3; font-family: 'Segoe UI', Arial; }"
        "QLineEdit { "
        "   background-color: #161b22; "
        "   border: 2px solid #30363d; "
        "   border-radius: 10px; "
        "   padding: 14px 16px; "
        "   color: #e6edf3; "
        "   font-size: 15px; "
        "   selection-background-color: #1f6feb; "
        "}"
        "QLineEdit:focus { "
        "   border: 2px solid #1f6feb; "
        "   background-color: #0d1117; "
        "}"
        "QLineEdit::placeholder { color: #7d8590; }"
        "QComboBox { "
        "   background-color: #161b22; "
        "   border: 2px solid #30363d; "
        "   border-radius: 10px; "
        "   padding: 14px 16px; "
        "   color: #e6edf3; "
        "   font-size: 15px; "
        "}"
        "QComboBox:focus { border: 2px solid #1f6feb; }"
        "QComboBox::drop-down { "
        "   border: none; "
        "   width: 30px; "
        "}"
        "QComboBox::down-arrow { "
        "   image: none; "
        "   border-left: 5px solid transparent; "
        "   border-right: 5px solid transparent; "
        "   border-top: 6px solid #7d8590; "
        "   margin-right: 8px; "
        "}"
        "QComboBox QAbstractItemView { "
        "   background-color: #161b22; "
        "   color: #e6edf3; "
        "   border: 1px solid #30363d; "
        "   selection-background-color: #1f6feb; "
        "   outline: none; "
        "}"
        "QPushButton { "
        "   background-color: #238636; "
        "   color: white; "
        "   border: none; "
        "   border-radius: 10px; "
        "   padding: 16px; "
        "   font-size: 16px; "
        "   font-weight: 600; "
        "}"
        "QPushButton:hover { "
        "   background-color: #2ea043; "
        "}"
        "QPushButton:pressed { "
        "   background-color: #1a7f37; "
        "}"
        "QLabel { color: #e6edf3; background-color: transparent; }"
    );
    
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setSpacing(18);
    mainLayout->setContentsMargins(50, 45, 50, 45);
    
    // Header section with icon and branding
    QWidget* headerWidget = new QWidget(this);
    QVBoxLayout* headerLayout = new QVBoxLayout(headerWidget);
    headerLayout->setSpacing(8);
    headerLayout->setContentsMargins(0, 0, 0, 0);
    
    QLabel* iconLabel = new QLabel("✈️", this);
    QFont iconFont = iconLabel->font();
    iconFont.setPointSize(56);
    iconLabel->setFont(iconFont);
    iconLabel->setAlignment(Qt::AlignCenter);
    headerLayout->addWidget(iconLabel);
    
    mainLayout->addWidget(headerWidget);
    mainLayout->addSpacing(5);
    
    // Title
    QLabel* titleLabel = new QLabel("Airline Management System", this);
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(22);
    titleFont.setBold(true);
    titleFont.setWeight(QFont::Bold);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #58a6ff; margin-bottom: 5px;");
    mainLayout->addWidget(titleLabel);
    
    QLabel* subtitleLabel = new QLabel("Sign in to your account", this);
    QFont subtitleFont = subtitleLabel->font();
    subtitleFont.setPointSize(12);
    subtitleLabel->setFont(subtitleFont);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("color: #8b949e; margin-bottom: 10px;");
    mainLayout->addWidget(subtitleLabel);
    
    mainLayout->addSpacing(25);
    
    // Username
    QLabel* usernameLabel = new QLabel("Username", this);
    usernameLabel->setStyleSheet("color: #e6edf3; font-weight: 600; font-size: 13px; margin-bottom: 6px;");
    mainLayout->addWidget(usernameLabel);
    
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Enter your username");
    usernameEdit->setMinimumHeight(48);
    mainLayout->addWidget(usernameEdit);
    
    mainLayout->addSpacing(12);
    
    // Password
    QLabel* passwordLabel = new QLabel("Password", this);
    passwordLabel->setStyleSheet("color: #e6edf3; font-weight: 600; font-size: 13px; margin-bottom: 6px;");
    mainLayout->addWidget(passwordLabel);
    
    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Enter your password");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setMinimumHeight(48);
    mainLayout->addWidget(passwordEdit);
    
    mainLayout->addSpacing(12);
    
    // Role selection
    QLabel* roleLabel = new QLabel("Select Role", this);
    roleLabel->setStyleSheet("color: #e6edf3; font-weight: 600; font-size: 13px; margin-bottom: 6px;");
    mainLayout->addWidget(roleLabel);
    
    roleComboBox = new QComboBox(this);
    roleComboBox->addItem("Passenger", static_cast<int>(UserRole::Passenger));
    roleComboBox->addItem("Booking Agent", static_cast<int>(UserRole::BookingAgent));
    roleComboBox->addItem("Administrator", static_cast<int>(UserRole::Administrator));
    roleComboBox->setMinimumHeight(48);
    mainLayout->addWidget(roleComboBox);
    
    mainLayout->addSpacing(25);
    
    // Login button
    loginButton = new QPushButton("Sign In", this);
    loginButton->setMinimumHeight(50);
    loginButton->setCursor(Qt::PointingHandCursor);
    mainLayout->addWidget(loginButton);
    
    mainLayout->addSpacing(25);
    
    // Divider
    QFrame* divider = new QFrame(this);
    divider->setFrameShape(QFrame::HLine);
    divider->setStyleSheet("background-color: #21262d; border: none; height: 1px;");
    divider->setFixedHeight(1);
    mainLayout->addWidget(divider);
    
    mainLayout->addSpacing(15);
    
    // Default credentials info
    QLabel* infoTitleLabel = new QLabel("Demo Accounts", this);
    infoTitleLabel->setAlignment(Qt::AlignCenter);
    infoTitleLabel->setStyleSheet("color: #8b949e; font-size: 11px; font-weight: 600; margin-bottom: 8px;");
    mainLayout->addWidget(infoTitleLabel);
    
    QLabel* infoLabel = new QLabel(
        "<div style='text-align: center; line-height: 1.6;'>"
        "<p style='color: #7d8590; font-size: 11px; margin: 3px 0;'><span style='color: #58a6ff;'>●</span> Admin: <b>admin</b> / admin123</p>"
        "<p style='color: #7d8590; font-size: 11px; margin: 3px 0;'><span style='color: #58a6ff;'>●</span> Agent: <b>agent</b> / agent123</p>"
        "<p style='color: #7d8590; font-size: 11px; margin: 3px 0;'><span style='color: #58a6ff;'>●</span> Passenger: <b>passenger</b> / pass123</p>"
        "</div>",
        this
    );
    infoLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(infoLabel);
    
    // Connect signals
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked() {
    QString username = usernameEdit->text().trimmed();
    QString password = passwordEdit->text();
    UserRole selectedRole = static_cast<UserRole>(roleComboBox->currentData().toInt());
    
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }
    
    DatabaseManager* db = DatabaseManager::getInstance();
    auto user = db->getUserByUsername(username);
    
    if (!user) {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        return;
    }
    
    if (user->getPassword() != password) {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
        return;
    }
    
    if (user->getRole() != selectedRole) {
        QMessageBox::warning(this, "Login Failed", 
                             QString("User '%1' is not registered as %2.")
                             .arg(username)
                             .arg(roleComboBox->currentText()));
        return;
    }
    
    if (!user->getIsActive()) {
        QMessageBox::warning(this, "Login Failed", "This account is inactive.");
        return;
    }
    
    // Login successful
    emit loginSuccessful(user->getUserId(), user->getRole());
    
    // Clear fields
    usernameEdit->clear();
    passwordEdit->clear();
    
    // Hide login window
    hide();
}
