#ifndef TWOSTOPSDIALOG_H
#define TWOSTOPSDIALOG_H

#include <QDialog>

namespace Ui {
class TwoStopsDialog;
}

class TwoStopsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TwoStopsDialog(QWidget *parent = 0);
    ~TwoStopsDialog();

    QString getLine() const;
    QString getFirstStop() const;
    QString getSecondStop() const;

private:
    Ui::TwoStopsDialog *ui;
};

#endif // TWOSTOPSDIALOG_H
