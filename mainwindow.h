#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "network.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Network& network, QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Network& network_;

    QMenu *fileMenu;
    QAction *openAct;
    QAction *saveAct;

    void createActions();
    void createMenus();

private slots:
    void open();
    void handleButton(const std::string& lineName);
    void save();
};

#endif // MAINWINDOW_H
