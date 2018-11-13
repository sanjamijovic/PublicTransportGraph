#ifndef LINECHANGESTOP_H
#define LINECHANGESTOP_H

#include <QDialog>

namespace Ui {
    class LineChangeStop;
}

class LineChangeStop : public QDialog {
    Q_OBJECT

public:
    explicit LineChangeStop(QWidget *parent = 0);
    ~LineChangeStop();

    QString getDirection() const;
    QString getline() const;
    QString getStop() const;
    QString getAction() const;

    QString getStopName() const;
    QString getLatitude() const;
    QString getLongitude() const;
    QString getZone() const;

private:
    Ui::LineChangeStop *ui;
    QString clickedDirection;

private slots:
    void direction(int);
    void add();
    void remove();
};

#endif // LINECHANGESTOP_H
