#include "directiontabwidget.h"
#include "ui_directiontabwidget.h"

DirectionTabWidget::DirectionTabWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DirectionTabWidget)
{
    ui->setupUi(this);
}

DirectionTabWidget::~DirectionTabWidget()
{
    delete ui;
}

QTableWidget* DirectionTabWidget::stopsTable() {
    return ui->stopsTable;
}
