#include "lineinfowindow.h"
#include "ui_lineinfowindow.h"
#include "directiontabwidget.h"
#include "busline.h"
#include "busstop.h"

LineInfoWindow::LineInfoWindow(BusLine* line, QWidget *parent) :
    QWidget(parent),
    line_(line),
    ui(new Ui::LineInfoWindow)
{
    ui->setupUi(this);
    setWindowTitle("Line " + QString::fromStdString(line->getName()));
    ui->lineName->setText(QString::fromStdString(line_->getName()));

    ui->route->setText(QString::fromStdString(line_->getFirstStop()) + QString::fromUtf8(" \u2192 ") + QString::fromStdString(line->getLastStop()));

    auto directionA = new DirectionTabWidget();
    ui->tabWidget->addTab(directionA, "Direction A");
    auto directionB = new DirectionTabWidget();
    ui->tabWidget->addTab(directionB, "Direction B");
    makeTable(directionA, BusLine::DIRECTION_A);
    makeTable(directionB, BusLine::DIRECTION_B);
}

LineInfoWindow::~LineInfoWindow() {
    delete ui;
}

void LineInfoWindow::makeTable(DirectionTabWidget* direction, BusLine::Directions lineDir)
{

    LineDirection dir = (lineDir == BusLine::DIRECTION_A ? line_->directionA_ : line_->directionB_);

    unsigned long numOfCollumns = line_->getNumberOfStops(lineDir);
    direction->stopsTable()->setRowCount(numOfCollumns);
    direction->stopsTable()->setColumnCount(6);
    direction->stopsTable()->setEditTriggers(QAbstractItemView::NoEditTriggers);

    for(int i = 0; i < direction->stopsTable()->horizontalHeader()->count(); i++)
        direction->stopsTable()->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QStringList tableHeader;
    tableHeader << "Stop ID" << "Stop Name" << "Latitude" << "Longitude" << "Zone ID" << "Lines";
    direction->stopsTable()->setHorizontalHeaderLabels(tableHeader);

    int i = 0;
    for(auto stop : dir.getStops()) {
        direction->stopsTable()->setItem(i, 0, new QTableWidgetItem(QString::number(stop->getStopID_())));
        direction->stopsTable()->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(stop->getStopName_())));
        direction->stopsTable()->setItem(i, 2, new QTableWidgetItem(QString::number(stop->getLocation_().getLatitude())));
        direction->stopsTable()->setItem(i, 3, new QTableWidgetItem(QString::number(stop->getLocation_().getLongitude())));
        direction->stopsTable()->setItem(i, 4, new QTableWidgetItem(QString::number(stop->getZoneID_())));
        i++;
    }
}
