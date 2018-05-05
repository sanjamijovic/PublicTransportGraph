#include "deletedialog.h"
#include "ui_deletedialog.h"
#include "network.h"
#include <QMessageBox>

DeleteDialog::DeleteDialog(Network& network, std::function<void(void)> draw, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteDialog),
    network_(network),
    draw_(draw)
{
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(acc()));
}

DeleteDialog::~DeleteDialog()
{
    delete ui;
}

void DeleteDialog::acc()
{
    BusLine* line;
    if((line = network_.getLine(ui->lineName->text().toStdString())) != nullptr) {
        network_.removeLine(line);
        draw_();
    } else {
        QMessageBox* message = new QMessageBox();
        message->setText("Nonexistent line");
        message->show();
    }
}
