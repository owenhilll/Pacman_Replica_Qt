#ifndef ALLTREASURECOLLECTED_H
#define ALLTREASURECOLLECTED_H

#include <QDialog>

namespace Ui {
class alltreasurecollected;
}

class alltreasurecollected : public QDialog
{
    Q_OBJECT

public:
    explicit alltreasurecollected(QWidget *parent = nullptr);
    ~alltreasurecollected();

private:
    Ui::alltreasurecollected *ui;
};

#endif // ALLTREASURECOLLECTED_H
