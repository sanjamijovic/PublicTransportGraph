#ifndef LINEDIALOG_H
#define LINEDIALOG_H

#include <QDialog>

namespace Ui {
class LineDialog;
}

class LineDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LineDialog(QWidget *parent = 0);
    ~LineDialog();

    QString getLine() const;

private:
    Ui::LineDialog *ui;
};

#endif // LINEDIALOG_H
