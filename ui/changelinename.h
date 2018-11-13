#ifndef CHANGELINENAME_H
#define CHANGELINENAME_H

#include <QDialog>

namespace Ui {
    class ChangeLineName;
}

class ChangeLineName : public QDialog {
    Q_OBJECT

public:
    explicit ChangeLineName(QWidget *parent = 0);
    ~ChangeLineName();

    QString oldName() const;
    QString newName() const;

private:
    Ui::ChangeLineName *ui;
};

#endif // CHANGELINENAME_H
