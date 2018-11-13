#include "changelinename.h"
#include "ui_changelinename.h"

ChangeLineName::ChangeLineName(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ChangeLineName) {
    ui->setupUi(this);
}

ChangeLineName::~ChangeLineName() {
    delete ui;
}

QString ChangeLineName::oldName() const {
    return ui->oldLine->text();
}

QString ChangeLineName::newName() const {
    return ui->newLine->text();
}
