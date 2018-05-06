#include <QFileDialog>
#include <QPushButton>
#include <QMessageBox>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textparser.h"
#include "lineinfowindow.h"
#include "savedialog.h"
#include "addlinedialog.h"
#include "filterdialog.h"
#include "deletedialog.h"
#include "connectedlinesdialog.h"
#include "connectedpairsdialog.h"
#include "lineforstopdialog.h"
#include "twostopsdialog.h"
#include "linedialog.h"
#include "locationwidget.h"
#include "busstop.h"
#include "bfsdialog.h"

#include <iostream>

MainWindow::MainWindow(Network& network, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    network_(network)
{
    ui->setupUi(this);
    setWindowTitle("PublicTransportGraph");
    createActions();
    createMenus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if(!exported) {

        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "End", "Do you want to save your work?",QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
              save();
              while(!exported);
              QApplication::quit();
          } else {
            QApplication::quit();
          }
    }
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    newAct = new QAction(tr("&Add new line"), this);
    newAct->setShortcuts(QKeySequence::New);
    connect(newAct, &QAction::triggered, this, &MainWindow::newLine);

    filterAct = new QAction(tr("&Filter lines"), this);
    connect(filterAct, &QAction::triggered, this, &MainWindow::filter);

    deleteAct = new QAction(tr("&Delete line"), this);
    connect(deleteAct, &QAction::triggered, this, &MainWindow::deleteLine);

    showConnectedAct = new QAction(tr("&Show lines connected to line"), this);
    connect(showConnectedAct, &QAction::triggered, this, &MainWindow::showConnectedLines);

    showConnectedPairsAct = new QAction(tr("&Show connected pairs"), this);
    connect(showConnectedPairsAct, &QAction::triggered, this, &MainWindow::showConnectedPairs);

    showLinesForStopAct = new QAction(tr("&Show lines for stop"), this);
    connect(showLinesForStopAct, &QAction::triggered, this, &MainWindow::showLinesForStop);

    showNextStopsAct = new QAction(tr("&Show all next stops for stop"), this);
    connect(showNextStopsAct, &QAction::triggered, this, &MainWindow::showNextStops);

    twoStopsAct = new QAction(tr("&Two stops in one direction"), this);
    connect(twoStopsAct, &QAction::triggered, this, &MainWindow::twoStops);

    mostMutualAct = new QAction(tr("&Line with most mutual stops"), this);
    connect(mostMutualAct, &QAction::triggered, this, &MainWindow::mostMutual);

    nearestStopAct = new QAction(tr("&Nearest stop to location"), this);
    connect(nearestStopAct, &QAction::triggered, this, &MainWindow::nearestStop);

    shortestPathAct = new QAction(tr("&Shortest path"), this);
    connect(shortestPathAct, &QAction::triggered, this, &MainWindow::shortestPath);

    smallestStopoversAct = new QAction(tr("&Least stopovers"), this);
    connect(smallestStopoversAct, &QAction::triggered, this, &MainWindow::smallestStopovers);

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(newAct);
    editMenu->addAction(filterAct);
    editMenu->addAction(deleteAct);

    viewMenu = menuBar()->addMenu(tr("&View"));
    viewMenu->addAction(showConnectedAct);
    viewMenu->addAction(showConnectedPairsAct);
    viewMenu->addAction(showLinesForStopAct);
    viewMenu->addAction(showNextStopsAct);
    viewMenu->addAction(twoStopsAct);
    viewMenu->addAction(mostMutualAct);
    viewMenu->addAction(nearestStopAct);
    viewMenu->addAction(shortestPathAct);
    viewMenu->addAction(smallestStopoversAct);
}

void MainWindow::open() {
    if(!exported) {
        QMessageBox::StandardButton reply;
          reply = QMessageBox::question(this, "Save old work", "Do you want to save your work?",QMessageBox::Yes|QMessageBox::No);
          if (reply == QMessageBox::Yes) {
              save();
          }
    }
    network_.clear();

    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open network file"), "/", tr("Text Files (*.txt)"));
    TextParser parser(network_);
    try {
        parser.collectData(fileName.toUtf8().constData());
    } catch(std::exception& e) {
        QMessageBox* message = new QMessageBox();
        message->setText(QString::fromStdString(e.what()));
        message->show();
    }
    drawWindow();
    exported = false;

}

void MainWindow::handleButton(const std::string& lineName) {
    auto line = network_.getLine(lineName);
    LineInfoWindow* lineWindow = new LineInfoWindow(line);
    lineWindow->show();
}

void MainWindow::save() {
    SaveDialog* dialog = new SaveDialog(network_);
    if(dialog->exec())
        exported = true;

}

void MainWindow::newLine() {
    bool valid;
    AddLineDialog* addDialog = new AddLineDialog(network_, [this] { drawWindow(); }, &valid);
    if(addDialog->exec())
        exported = !valid;
}

void MainWindow::filter()
{
    bool valid;
    FilterDialog* filterDialog = new FilterDialog(network_, [this] {drawWindow();}, &valid);
    if(filterDialog->exec())
        exported = !valid;
}

void MainWindow::deleteLine()
{
    bool valid;
    DeleteDialog* deleteDialog = new DeleteDialog(network_, [this] {drawWindow();}, &valid);
    if(deleteDialog->exec())
        exported = !valid;
}

void MainWindow::showConnectedLines()
{
    ConnectedLinesDialog* connectedDialog = new ConnectedLinesDialog(network_);
    connectedDialog->show();
}

void MainWindow::showConnectedPairs()
{
    ConnectedPairsDialog* pairsDialog = new ConnectedPairsDialog(network_);
    pairsDialog->show();
}

void MainWindow::showLinesForStop()
{
    InfoForStopDialog* lineForStopDialog = new InfoForStopDialog(false, network_);
    lineForStopDialog->show();
}

void MainWindow::showNextStops()
{
    InfoForStopDialog* nextStops = new InfoForStopDialog(true, network_);
    nextStops->show();
}

void MainWindow::twoStops()
{
    TwoStopsDialog* dialog = new TwoStopsDialog();
    dialog->show();
    if(dialog->exec()) {
        auto line = network_.getLine(dialog->getLine().toStdString());
        if(line == nullptr) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid line");
        }
        else{
            auto stop1 = network_.getStop(dialog->getFirstStop().toInt());
            if(line == nullptr) {
                QMessageBox* message = new QMessageBox();
                message->setText("Invalid first stop");
            }
            else{
                auto stop2 = network_.getStop(dialog->getSecondStop().toInt());
                if(line == nullptr) {
                    QMessageBox* message = new QMessageBox();
                    message->setText("Invalid second stop");
                }
                else {

                    QMessageBox* outmessage = new QMessageBox();
                    if(line->hasStopsInOneDirection(stop1, stop2))
                        outmessage->setText("Line has those stops in one direction.");
                    else
                        outmessage->setText("Line doesn't have those stops in one direction.");
                    outmessage->show();
                }
            }
        }
    }

}

void MainWindow::mostMutual()
{
    LineDialog* dialog = new LineDialog();
    dialog->show();
    if(dialog->exec()) {
        auto line = network_.getLine(dialog->getLine().toStdString());
        QMessageBox* message = new QMessageBox();
        if(line != nullptr) {
            auto lineName = line->lineWithMostMutualStops()->getName();
            message->setText("Line with most mutual stops: " + QString::fromStdString(lineName));
            message->show();
        }
        else {
            message->setText("Invalid line name");
            message->show();
        }
    }
}

void MainWindow::nearestStop()
{
    LocationWidget* location = new LocationWidget();
    location->show();
    if(location->exec()) {
        bool valid;
        double latitude = location->getLatitude().toDouble(&valid);
        if(!valid) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid latitude");
            message->show();
            return;
        }
        double longitude = location->getLongitude().toDouble(&valid);
        if(!valid) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid longitude");
            message->show();
            return;
        }
        auto lineName = location->getLine().toStdString();
        Location location(latitude, longitude);
        BusStop* stop;
        if(lineName == "")
            stop = network_.nearestStopToLocation(location);
        else {
            auto line = network_.getLine(lineName);
            if(line == nullptr) {
                QMessageBox* message = new QMessageBox();
                message->setText("Invalid line name");
                message->show();
                return;
            }
            stop = network_.nearestStopToLocation(location, line);
        }

        QMessageBox* message = new QMessageBox();
        message->setText("Nearest stop: " + QString::fromStdString(std::to_string(stop->getStopID_())) + " " + QString::fromStdString(stop->getStopName_()));
        message->show();
    }
}

void MainWindow::shortestPath()
{
    BfsDialog* dialog = new BfsDialog();
    dialog->show();
    if(dialog->exec()) {
        int stop1 = dialog->getFirstStop().toInt();
        int stop2 = dialog->getSecondStop().toInt();
        BusStop *s1, *s2;
        if((s1 = network_.getStop(stop1)) == nullptr || (s2 = network_.getStop(stop2)) == nullptr) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid stops");
            message->show();
            return;
        }

        auto result = network_.shortestPath(s1, s2);
        QMessageBox* message = new QMessageBox();
        message->setText("Shortest path: " + QString::fromStdString(std::to_string(result)));
        message->show();

    }
}

void MainWindow::smallestStopovers()
{
    BfsDialog* dialog = new BfsDialog();
    dialog->show();
    if(dialog->exec()) {
        int stop1 = dialog->getFirstStop().toInt();
        int stop2 = dialog->getSecondStop().toInt();
        BusStop *s1, *s2;
        if((s1 = network_.getStop(stop1)) == nullptr || (s2 = network_.getStop(stop2)) == nullptr) {
            QMessageBox* message = new QMessageBox();
            message->setText("Invalid stops");
            message->show();
            return;
        }

        auto result = network_.numOfStopovers(s1, s2);
        QMessageBox* message = new QMessageBox();
        message->setText("Number of stopovers: " + QString::fromStdString(std::to_string(result)));
        message->show();

    }
}

void MainWindow::drawWindow() {
    QLayoutItem *child;
    while ((child = ui->linesGrid->takeAt(0)) != 0)  {
        delete child->widget();
        delete child;
    }

    auto allLineNames = network_.getAllLineNames();
    unsigned long numOfCollumns = size().width() / 150;

    int i = 0;
    for (auto name : allLineNames) {
        auto button = new QPushButton(QString::fromStdString(name));
        connect(button, &QPushButton::released, this, [this, name] { handleButton(name); });
        ui->linesGrid->addWidget(button,  i/ numOfCollumns, i % numOfCollumns);
        i++;
    }
}
