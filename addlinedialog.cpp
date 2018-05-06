#include "addlinedialog.h"
#include "ui_addlinedialog.h"
#include "network.h"
#include "busline.h"
#include "textparser.h"
#include "mainwindow.h"
#include "invalidfile.h"
#include <QFileDialog>
#include <QAction>
#include <QMessageBox>

AddLineDialog::AddLineDialog(Network& network, std::function<void(void)> draw, bool* valid, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddLineDialog),
    network_(network),
    draw_(draw),
    valid_(valid)
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
    BusLine* oldLine = nullptr;
    if(fileNameDirectionA != "" && fileNameDirectionB != "") {
        BusLine* line;
        if((line = network_.getLine(ui->lineName->text().toStdString())) == nullptr) {
            line = new BusLine(ui->lineName->text().toStdString(), ui->firstStop->text().toStdString(), ui->lastStop->text().toStdString());
            network_.addLine(line);
        }
        else {
            oldLine = new BusLine(*line);
            line->removeAllStops();
            line->setFirstStop(ui->firstStop->text().toStdString());
            line->setLastStop(ui->lastStop->text().toStdString());
        }
        TextParser parser(network_);
        try{
            parser.collectStopsData(fileNameDirectionA.toStdString(), line, BusLine::DIRECTION_A);
            parser.collectStopsData(fileNameDirectionB.toStdString(), line, BusLine::DIRECTION_B);
        }
        catch(InvalidFile& e) {
            QMessageBox* message = new QMessageBox();
            message->setText(QString::fromStdString(e.what()));
            message->show();
            *valid_ = false;
            if(oldLine != nullptr)
                network_.addLine(oldLine);
            return;
        }
        delete oldLine;
        draw_();
        *valid_ = true;
    }
    else {
        QMessageBox* message = new QMessageBox();
        message->setText("Files not specified");
        message->show();
        *valid_ = false;
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

