#ifndef DIRECTIONTABWIDGET_H
#define DIRECTIONTABWIDGET_H

#include <QTableWidget>
#include <QWidget>

namespace Ui {
    class DirectionTabWidget;
}

class DirectionTabWidget : public QWidget {
    Q_OBJECT

public:
    explicit DirectionTabWidget(QWidget *parent = 0);
    ~DirectionTabWidget();

    QTableWidget *stopsTable();

private:
    Ui::DirectionTabWidget *ui;
};

#endif // DIRECTIONTABWIDGET_H
