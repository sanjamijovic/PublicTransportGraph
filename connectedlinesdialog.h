#ifndef CONNECTEDLINESDIALOG_H
#define CONNECTEDLINESDIALOG_H

#include <QDialog>

class Network;

namespace Ui {
class ConnectedLinesDialog;
}

class ConnectedLinesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectedLinesDialog(Network& network, QWidget *parent = 0);
    ~ConnectedLinesDialog();

private:
    Ui::ConnectedLinesDialog *ui;
    Network& network_;

private slots:
    void acc();
};

#endif // CONNECTEDLINESDIALOG_H
