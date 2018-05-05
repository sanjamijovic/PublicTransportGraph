#include <QFileDialog>
#include <QPushButton>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "textparser.h"
#include "lineinfowindow.h"
#include "savedialog.h"
#include "addlinedialog.h"

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
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);

    editMenu = menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(newAct);
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Open network file"), "/", tr("Text Files (*.txt)"));
    TextParser parser(network_);
    parser.collectData(fileName.toUtf8().constData());

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
    AddLineDialog* addDialog = new AddLineDialog(network_);
    addDialog->show();
}
