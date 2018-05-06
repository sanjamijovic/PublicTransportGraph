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

    void closeEvent(QCloseEvent*) override;

private:
    Ui::MainWindow *ui;
    Network& network_;
    bool exported = true;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *viewMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *newAct;
    QAction *filterAct;
    QAction *deleteAct;
    QAction *showConnectedAct;
    QAction *showConnectedPairsAct;
    QAction *showLinesForStopAct;
    QAction *showNextStopsAct;
    QAction *twoStopsAct;
    QAction *mostMutualAct;
    QAction *nearestStopAct;
    QAction *shortestPathAct;
    QAction *smallestStopoversAct;

    void createActions();
    void createMenus();
    void drawWindow();

private slots:
    void open();
    void handleButton(const std::string& lineName);
    void save();
    void newLine();
    void filter();
    void deleteLine();

    void showConnectedLines();
    void showConnectedPairs();
    void showLinesForStop();
    void showNextStops();
    void twoStops();
    void mostMutual();
    void nearestStop();
    void shortestPath();
    void smallestStopovers();

};

#endif // MAINWINDOW_H
