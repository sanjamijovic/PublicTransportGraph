#ifndef LINEFORSTOPDIALOG_H
#define LINEFORSTOPDIALOG_H

#include <QDialog>

class Network;

namespace Ui {
    class LineForStopDialog;
}

class InfoForStopDialog : public QDialog {
    Q_OBJECT

public:
    // stops = false shows lines
    explicit InfoForStopDialog(bool stops, Network &network, QWidget *parent = 0);
    ~InfoForStopDialog();

private:
    Ui::LineForStopDialog *ui;
    Network &network_;
    bool stops_;

private slots:
    void acc();
};

#endif // LINEFORSTOPDIALOG_H
