#include "twostopsdialog.h"
#include "ui_twostopsdialog.h"

TwoStopsDialog::TwoStopsDialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::TwoStopsDialog) {
    ui->setupUi(this);
}

TwoStopsDialog::~TwoStopsDialog() {
    delete ui;
}

QString TwoStopsDialog::getLine() const {
    return ui->line->text();
}

QString TwoStopsDialog::getFirstStop() const {
    return ui->stop1->text();
}

QString TwoStopsDialog::getSecondStop() const {
    return ui->stop2->text();
}
