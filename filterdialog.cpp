#include "filterdialog.h"
#include "ui_filterdialog.h"
#include "network.h"
#include <QMessageBox>

FilterDialog::FilterDialog(Network& network, std::function<void(void)> draw, bool* valid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FilterDialog),
    network_(network),
    draw_(draw),
    valid_(valid)
{
    ui->setupUi(this);
    ui->lineEdit->setVisible(false);
    ui->label->setVisible(false);

    ui->filterLabel->setText("Number of last zone:");

    ui->filterType->addItem("Filter by zone");
    ui->filterType->addItem("Filter by line number greater");
    ui->filterType->addItem("Filter by line number smaller");
    ui->filterType->addItem("Filter by line number between");
    ui->filterType->addItem("Filter by number of stops greater");
    ui->filterType->addItem("Filter by number of stops smaller");

    connect(ui->filterType,SIGNAL(activated(int)),this,SLOT(filterType(int)));
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acc()));
}

FilterDialog::~FilterDialog()
{
    delete ui;
}

void FilterDialog::acc()
{
    bool valid1;
    bool valid2;
    switch(typeOfFilter) {
    case ZONE:
        std::cout << ui->number->text().toInt();
        try {
            network_.filterByZone(ui->number->text().toInt(&valid1));
            if(!valid1) {
                QMessageBox* message = new QMessageBox();
                message->setText("Invalid zone (not a number)");
                message->show();
                *valid_ = false;
                return;
            }
        }catch(std::invalid_argument exc) {
            QMessageBox* message = new QMessageBox();
            message->setText(QString::fromStdString(exc.what()));
            message->show();
            *valid_ = false;
            return;
        }
        break;
    case LINE_NUMBER_G:
        network_.filterByLineNumberGreater(ui->number->text().toInt(&valid1));
        if(!valid1) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid line number (not a number)");
            message->show();
            *valid_ = false;
            return;
        }
        break;
    case LINE_NUMBER_S:
        network_.filterByLineNumberSmaller(ui->number->text().toInt(&valid1));
        if(!valid1) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid line number (not a number)");
            message->show();
            *valid_ = false;
            return;
        }
        break;
    case LINE_NUMBER_B:
        network_.filterByLineNumberRange(ui->number->text().toInt(&valid1), ui->lineEdit->text().toInt(&valid2));
        if(!valid1 || !valid2) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid line number (not a number)");
            message->show();
            *valid_ = false;
            return;
        }
        break;
    case STOPS_NUMBER_G:
        network_.filterByNumberOfStopsGreater(ui->number->text().toInt(&valid1));
        if(!valid1) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid stop ID (not a number)");
            message->show();
            *valid_ = false;
            return;
        }
        break;
    case STOPS_NUMBER_S:
        network_.filterByNumberOfStopsSmaller(ui->number->text().toInt(&valid1));
        if(!valid1) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid stop ID (not a number)");
            message->show();
            *valid_ = false;
            return;
        }
        break;
    }
    draw_();
    *valid_ = true;
}

void FilterDialog::filterType(int val)
{
    switch (val) {
    case 0:
        ui->lineEdit->setVisible(false);
        ui->label->setVisible(false);
        ui->filterLabel->setText("Number of last zone: (1-3)");
        typeOfFilter = ZONE;
        break;
    case 1:
        ui->lineEdit->setVisible(false);
        ui->label->setVisible(false);
        ui->filterLabel->setText("Smallest line number:");
        typeOfFilter = LINE_NUMBER_G;
        break;
    case 2:
        ui->lineEdit->setVisible(false);
        ui->label->setVisible(false);
        ui->filterLabel->setText("Biggest line number:");
        typeOfFilter = LINE_NUMBER_S;
        break;
    case 3:
        ui->lineEdit->setVisible(true);
        ui->label->setVisible(true);
        ui->filterLabel->setText("Smallest line number:");
        ui->label->setText("Biggest line number");
        typeOfFilter = LINE_NUMBER_B;
        break;
    case 4:
        ui->lineEdit->setVisible(false);
        ui->label->setVisible(false);
        ui->filterLabel->setText("Smallest stops number:");
        typeOfFilter = STOPS_NUMBER_G;
        break;
    case 5:
        ui->lineEdit->setVisible(false);
        ui->label->setVisible(false);
        ui->filterLabel->setText("Biggest stops number:");
        typeOfFilter = STOPS_NUMBER_S;
        break;

    default:
        break;

    }
}
