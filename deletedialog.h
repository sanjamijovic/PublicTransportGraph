#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDialog>

class Network;

namespace Ui {
    class DeleteDialog;
}

class DeleteDialog : public QDialog {
    Q_OBJECT

public:
    explicit DeleteDialog(Network &network, std::function<void(void)> draw, bool *valid, QWidget *parent = 0);
    ~DeleteDialog();

private:
    Ui::DeleteDialog *ui;
    Network &network_;
    std::function<void(void)> draw_;
    bool *valid_;

private slots:
    void acc();
};

#endif // DELETEDIALOG_H
