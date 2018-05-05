#include "locationwidget.h"
#include "ui_locationwidget.h"

LocationWidget::LocationWidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationWidget)
{
    ui->setupUi(this);
}

LocationWidget::~LocationWidget()
{
    delete ui;
}

QString LocationWidget::getLatitude() const
{
    return ui->latitude->text();
}

QString LocationWidget::getLongitude() const
{
    return ui->longitude->text();
}

QString LocationWidget::getLine() const
{
    return ui->lineName->text();
}
