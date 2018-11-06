#include "connectedpairsdialog.h"
#include "ui_connectedpairsdialog.h"
#include "network.h"
#include "textwidget.h"
#include "busline.h"
#include <sstream>

ConnectedPairsDialog::ConnectedPairsDialog(Network &network, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::ConnectedPairsDialog),
        network_(network) {
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acc()));
}

ConnectedPairsDialog::~ConnectedPairsDialog() {
    delete ui;
}

void ConnectedPairsDialog::acc() {
    bool valid;
    int number = ui->number->text().toInt(&valid);

    auto result = (valid ? network_.mutualStopsForAllPairsOfLines(number) : network_.mutualStopsForAllPairsOfLines());

    std::stringstream ss;
    for (auto pair : result)
        ss << pair.first.first->getName() << " : " << pair.first.second->getName() << " stops : " << pair.second
           << std::endl;

    TextWidget *text = new TextWidget(QString::fromStdString(ss.str()));
    text->show();
}
