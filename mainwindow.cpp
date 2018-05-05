#include <QFileDialog>
#include <QPushButton>

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
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open network file"), "/", tr("Text Files (*.txt)"));
    TextParser parser(network_);
    parser.collectData(fileName.toUtf8().constData());
    drawWindow();

}

void MainWindow::handleButton(const std::string& lineName) {
    auto line = network_.getLine(lineName);
    LineInfoWindow* lineWindow = new LineInfoWindow(line);
    lineWindow->show();
}

void MainWindow::save() {
    SaveDialog* dialog = new SaveDialog(network_);
    dialog->show();

}

void MainWindow::newLine() {
    AddLineDialog* addDialog = new AddLineDialog(network_, [this] { drawWindow(); });
    addDialog->show();
}

void MainWindow::filter()
{
    FilterDialog* filterDialog = new FilterDialog(network_, [this] {drawWindow();});
    filterDialog->show();
}

void MainWindow::deleteLine()
{
    DeleteDialog* deleteDialog = new DeleteDialog(network_, [this] {drawWindow();});
    deleteDialog->show();
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
