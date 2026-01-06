#ifndef AIRLINE_H
#define AIRLINE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class airline;
}
QT_END_NAMESPACE

class airline : public QMainWindow
{
    Q_OBJECT

public:
    airline(QWidget *parent = nullptr);
    ~airline();

private:
    Ui::airline *ui;
};
#endif // AIRLINE_H
