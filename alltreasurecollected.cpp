#include "alltreasurecollected.h"
#include "ui_alltreasurecollected.h"

alltreasurecollected::alltreasurecollected(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::alltreasurecollected)
{
    ui->setupUi(this);
}

alltreasurecollected::~alltreasurecollected()
{
    delete ui;
}
