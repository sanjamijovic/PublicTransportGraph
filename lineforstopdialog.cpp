#include "lineforstopdialog.h"
#include "ui_lineforstopdialog.h"
#include "network.h"
#include "busstop.h"
#include "textwidget.h"
#include <QMessageBox>
#include <sstream>

InfoForStopDialog::InfoForStopDialog(bool stops, Network& network, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LineForStopDialog),
    network_(network),
    stops_(stops)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acc()));
}

InfoForStopDialog::~InfoForStopDialog()
{
    delete ui;
}

void InfoForStopDialog::acc()
{
    auto stop = network_.getStop(ui->lineEdit->text().toInt());
    if(stop == nullptr) {
        QMessageBox* message = new QMessageBox();
        message->setText("Invalid stop");
        message->show();
    }

    std::stringstream ss;
    if(stops_) {
        auto result = network_.allNextStops(stop);
        for(auto line : result)
            ss << *line << std::endl;
    }
    else {
        auto result = stop->getLines();
        for(auto stop : result)
            ss << *stop << std::endl;
    }

    TextWidget* text  = new TextWidget(QString::fromStdString(ss.str()));
    text->show();
}
