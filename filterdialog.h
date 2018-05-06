#ifndef FILTERDIALOG_H
#define FILTERDIALOG_H

#include <QDialog>

class Network;

namespace Ui {
class FilterDialog;
}

class FilterDialog : public QDialog
{
    Q_OBJECT

public:
    enum FilterType {
        ZONE, LINE_NUMBER_S, LINE_NUMBER_G, LINE_NUMBER_B, STOPS_NUMBER_S, STOPS_NUMBER_G
    };

    explicit FilterDialog(Network& network, std::function<void(void)> draw, bool* valid, QWidget *parent = 0);
    ~FilterDialog();

private:
    Ui::FilterDialog *ui;
    Network& network_;
    std::function<void(void)> draw_;
    FilterType typeOfFilter = ZONE;
    bool* valid_;
private slots:
    void acc();
    void filterType(int);
};

#endif // FILTERDIALOG_H
