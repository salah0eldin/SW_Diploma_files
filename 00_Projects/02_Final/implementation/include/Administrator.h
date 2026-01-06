#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H

#include "User.h"

class Administrator : public User {
private:
    QString department;
    QString accessLevel;

public:
    Administrator(const QString& userId = "", const QString& username = "",
                  const QString& password = "", const QString& department = "");
    
    QString getDepartment() const { return department; }
    QString getAccessLevel() const { return accessLevel; }
    
    void setDepartment(const QString& dept) { department = dept; }
    void setAccessLevel(const QString& level) { accessLevel = level; }
    
    QString toJson() const override;
    static Administrator* fromJson(const QString& json);
};

#endif // ADMINISTRATOR_H
