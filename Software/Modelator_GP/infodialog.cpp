#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InfoDialog)
{
    ui->setupUi(this);
    ui->info_num_vertex->setText("0");

}

InfoDialog::~InfoDialog()
{
    delete ui;
}

void InfoDialog::setTextVertex(const char *text)
{
     ui->info_num_vertex->setText(text);
}


