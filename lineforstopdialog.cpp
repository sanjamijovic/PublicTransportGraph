#include "lineforstopdialog.h"
#include "ui_lineforstopdialog.h"
#include "network.h"
#include "busstop.h"
#include "textwidget.h"
#include <QMessageBox>
#include <sstream>

LineForStopDialog::LineForStopDialog(Network& network, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineForStopDialog),
    network_(network)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acc()));
}

LineForStopDialog::~LineForStopDialog()
{
    delete ui;
}

void LineForStopDialog::acc()
{
    auto stop = network_.getStop(ui->lineEdit->text().toInt());
    if(stop == nullptr) {
        QMessageBox* message = new QMessageBox();
        message->setText("Invalid stop");
        message->show();
    }

    std::stringstream ss;
    auto result = stop->getLines();
    for(auto line : result)
        ss << *line << std::endl;

    TextWidget* text  = new TextWidget(QString::fromStdString(ss.str()));
    text->show();
}
