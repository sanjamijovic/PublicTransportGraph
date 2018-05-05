#ifndef ADDLINEDIALOG_H
#define ADDLINEDIALOG_H

#include <QDialog>

class Network;

namespace Ui {
class AddLineDialog;
}

class MainWindow;

class AddLineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddLineDialog(Network& network, std::function<void(void)> draw, QWidget* parent = 0);
    ~AddLineDialog();

private:
    Ui::AddLineDialog *ui;
    Network& network_;
    QString fileNameDirectionA = "";
    QString fileNameDirectionB = "";
    std::function<void(void)> draw_;

private slots:
    void acc();
    void dirA();
    void dirB();
};

#endif // ADDLINEDIALOG_H
