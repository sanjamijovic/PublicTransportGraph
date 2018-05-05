#ifndef LINEFORSTOPDIALOG_H
#define LINEFORSTOPDIALOG_H

#include <QDialog>

class Network;

namespace Ui {
class LineForStopDialog;
}

class LineForStopDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineForStopDialog(Network& network, QWidget *parent = 0);
    ~LineForStopDialog();

private:
    Ui::LineForStopDialog *ui;
    Network& network_;
private slots:
    void acc();
};

#endif // LINEFORSTOPDIALOG_H
