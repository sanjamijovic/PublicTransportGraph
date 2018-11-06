#include "mainwindow.h"
#include <QApplication>

#include "network.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    Network network;
    MainWindow w(network);
    w.show();


    return a.exec();
}
