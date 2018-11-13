#include "linechangestop.h"
#include "ui_linechangestop.h"
#include <QComboBox>
#include <QRadioButton>

LineChangeStop::LineChangeStop(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::LineChangeStop) {
    ui->setupUi(this);
    ui->addButton->setChecked(true);
    ui->direction->addItem(tr("Direction A"));
    clickedDirection = ui->direction->currentText();
    ui->direction->addItem(tr("Direction B"));
    connect(ui->direction, SIGNAL(activated(int)), SLOT(direction(int)));
    ui->stopInfoBox->setVisible(true);
    connect(ui->addButton, SIGNAL(toggled(bool)), SLOT(add()));
    connect(ui->removeButton, SIGNAL(toggled(bool)), SLOT(remove()));
}

LineChangeStop::~LineChangeStop() {
    delete ui;
}

QString LineChangeStop::getDirection() const {
    return clickedDirection;
}

QString LineChangeStop::getline() const {
    return ui->line->text();
}

QString LineChangeStop::getStop() const {
    return ui->stop->text();
}

QString LineChangeStop::getAction() const {
    return (ui->addButton->isChecked() ? ui->addButton->text() : ui->removeButton->text());
}

QString LineChangeStop::getStopName() const {
    return ui->stopName->text();
}

QString LineChangeStop::getLatitude() const {
    return ui->latitude->text();
}

QString LineChangeStop::getLongitude() const {
    return ui->longitude->text();
}

QString LineChangeStop::getZone() const {
    return ui->zone->text();
}

void LineChangeStop::direction(int val) {
    clickedDirection = ui->direction->currentText();
}

void LineChangeStop::add() {
    ui->stopInfoBox->setVisible(true);
}

void LineChangeStop::remove() {
    ui->stopInfoBox->setVisible(false);
}
