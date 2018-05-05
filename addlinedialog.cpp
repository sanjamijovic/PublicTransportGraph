#include "addlinedialog.h"
#include "ui_addlinedialog.h"
#include "network.h"
#include "busline.h"
#include "textparser.h"
#include "mainwindow.h"
#include <QFileDialog>
#include <QAction>
#include <QMessageBox>

AddLineDialog::AddLineDialog(Network& network, std::function<void(void)> draw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineDialog),
    network_(network),
    draw_(draw)
{
    ui->setupUi(this);
    connect(ui->dirAButton, SIGNAL(clicked(bool)), this, SLOT(dirA()));
    connect(ui->dirBButton, SIGNAL(clicked(bool)), this, SLOT(dirB()));
    connect(ui->dialogButtonBox, SIGNAL(accepted()), this, SLOT(acc()));
}

AddLineDialog::~AddLineDialog()
{
    delete ui;
}

void AddLineDialog::acc()
{
    if(fileNameDirectionA != "" && fileNameDirectionB != "") {
        BusLine* line;
        if((line = network_.getLine(ui->lineName->text().toStdString())) == nullptr) {
            line = new BusLine(ui->lineName->text().toStdString(), ui->firstStop->text().toStdString(), ui->lastStop->text().toStdString());
            network_.addLine(line);
        }
        else {
            line->removeAllStops();
            line->setFirstStop(ui->firstStop->text().toStdString());
            line->setLastStop(ui->lastStop->text().toStdString());
        }
        TextParser parser(network_);
        parser.collectStopsData(fileNameDirectionA.toStdString(), line, BusLine::DIRECTION_A);
        parser.collectStopsData(fileNameDirectionB.toStdString(), line, BusLine::DIRECTION_B);
        draw_();
    }
    else {
        QMessageBox* message = new QMessageBox();
        message->setText("Files not specified");
        message->show();
    }
}

void AddLineDialog::dirA()
{
    fileNameDirectionA = QFileDialog::getOpenFileName(this, tr("Select file for direction A"), "/", tr("Text Files (*.txt)"));
}

void AddLineDialog::dirB()
{
    fileNameDirectionB = QFileDialog::getOpenFileName(this, tr("Select file for direction B"), "/", tr("Text Files (*.txt)"));
}

