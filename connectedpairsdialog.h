#ifndef CONNECTEDPAIRSDIALOG_H
#define CONNECTEDPAIRSDIALOG_H

#include <QDialog>

class Network;

namespace Ui {
class ConnectedPairsDialog;
}

class ConnectedPairsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConnectedPairsDialog(Network& network, QWidget *parent = 0);
    ~ConnectedPairsDialog();

private:
    Ui::ConnectedPairsDialog *ui;
    Network& network_;
private slots:
    void acc();
};

#endif // CONNECTEDPAIRSDIALOG_H
