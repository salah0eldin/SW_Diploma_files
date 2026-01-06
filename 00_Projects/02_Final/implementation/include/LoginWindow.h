#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include "User.h"

class LoginWindow : public QMainWindow {
    Q_OBJECT

private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QComboBox* roleComboBox;
    QPushButton* loginButton;
    
    void setupUi();
    
private slots:
    void onLoginClicked();
    
signals:
    void loginSuccessful(const QString& userId, UserRole role);
    
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
};

#endif // LOGINWINDOW_H
