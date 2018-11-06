#ifndef LINEINFOWINDOW_H
#define LINEINFOWINDOW_H

#include "busline.h"
#include "directiontabwidget.h"
#include <QWidget>
#include <string>

class LineDirection;

namespace Ui {
    class LineInfoWindow;
}

class LineInfoWindow : public QWidget {
    Q_OBJECT

public:
    LineInfoWindow(BusLine *line, QWidget *parent = nullptr);
    virtual ~LineInfoWindow();

private:
    BusLine *line_;
    Ui::LineInfoWindow *ui;

    void makeTable(DirectionTabWidget *, BusLine::Directions);
};

#endif // LINEINFOWINDOW_H
