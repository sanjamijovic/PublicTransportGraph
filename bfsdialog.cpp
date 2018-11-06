#include "bfsdialog.h"
#include "ui_bfsdialog.h"

BfsDialog::BfsDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::BfsDialog) {
    ui->setupUi(this);
}

BfsDialog::~BfsDialog() {
    delete ui;
}

QString BfsDialog::getFirstStop() const {
    return ui->stop1->text();
}

QString BfsDialog::getSecondStop() const {
    return ui->stop2->text();
}
