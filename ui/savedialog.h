#ifndef SAVEDIALOG_H
#define SAVEDIALOG_H

#include "network.h"
#include <QDialog>

namespace Ui {
    class SaveDialog;
}

class SaveDialog : public QDialog {
    Q_OBJECT

public:
    enum GraphModel {
        L_MODEL,
        C_MODEL
    };
    enum FormatType {
        GML,
        CSV_EDGES_TABLE,
        CSV_ADJACENCY_LIST,
        CSV_MATRIX
    };

    explicit SaveDialog(Network &network, QWidget *parent = 0);

    ~SaveDialog();

private:
    Ui::SaveDialog *ui;
    Network &network_;
    GraphModel graph;
    FormatType format;

private slots:
    void graphModel(int val);
    void formatType(int val);
    void acc();
};

#endif // SAVEDIALOG_H
