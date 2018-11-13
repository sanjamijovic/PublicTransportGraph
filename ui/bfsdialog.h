#ifndef BFSDIALOG_H
#define BFSDIALOG_H

#include <QDialog>

namespace Ui {
    class BfsDialog;
}

class BfsDialog : public QDialog {
    Q_OBJECT

public:
    explicit BfsDialog(QWidget *parent = 0);
    ~BfsDialog();

    QString getFirstStop() const;
    QString getSecondStop() const;

private:
    Ui::BfsDialog *ui;
};

#endif // BFSDIALOG_H
