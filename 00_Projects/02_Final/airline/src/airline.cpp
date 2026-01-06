#include "airline.h"
#include "ui_airline.h"

airline::airline(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::airline)
{
    ui->setupUi(this);
}

airline::~airline()
{
    delete ui;
}
