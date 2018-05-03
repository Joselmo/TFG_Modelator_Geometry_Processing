#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <figura3d.h>

namespace Ui {
class InfoDialog;
}

class InfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoDialog(QWidget *parent = 0);

    ~InfoDialog();

    void setTextVertex(const char *text);

private:
    Ui::InfoDialog *ui;

};

#endif // INFODIALOG_H
