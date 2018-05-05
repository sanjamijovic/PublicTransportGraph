#include "connectedlinesdialog.h"
#include "ui_connectedlinesdialog.h"
#include "network.h"
#include "busline.h"
#include "textwidget.h"
#include <sstream>
#include <QMessageBox>

ConnectedLinesDialog::ConnectedLinesDialog(Network& network, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectedLinesDialog),
    network_(network)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acc()));
}

ConnectedLinesDialog::~ConnectedLinesDialog()
{
    delete ui;
}

void ConnectedLinesDialog::acc()
{
    auto line = network_.getLine(ui->lineName->text().toStdString());
    if(line == nullptr) {
        QMessageBox* message = new QMessageBox();
        message->setText("Line not valid");
        message->show();
    }
    else{
        auto result = line->linesWithMutualStops();
        std::stringstream ss;
        for(auto line : result)
            ss << *line << std::endl;
        TextWidget* text = new TextWidget(QString::fromStdString(ss.str()));
        text->show();
    }
}
