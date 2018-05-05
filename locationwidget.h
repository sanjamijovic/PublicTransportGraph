#ifndef LOCATIONWIDGET_H
#define LOCATIONWIDGET_H

#include <QDialog>

namespace Ui {
class LocationWidget;
}

class LocationWidget : public QDialog
{
    Q_OBJECT

public:
    explicit LocationWidget(QWidget *parent = 0);
    ~LocationWidget();

    QString getLatitude() const;
    QString getLongitude() const;
    QString getLine() const;

private:
    Ui::LocationWidget *ui;
};

#endif // LOCATIONWIDGET_H
