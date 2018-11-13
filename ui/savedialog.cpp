#include "savedialog.h"
#include "ui_savedialog.h"
#include <QFileDialog>
#include "graphformatgenerator.h"
#include "lgraphgenerator.h"
#include "cgraphgenerator.h"
#include "outputfileformater.h"
#include "gmloutput.h"
#include "csvoutput.h"

SaveDialog::SaveDialog(Network &network, QWidget *parent) :
        QDialog(parent),
        ui(new Ui::SaveDialog),
        network_(network),
        graph(C_MODEL),
        format(GML) {
    ui->setupUi(this);
    ui->graph->addItem("C model");
    ui->graph->addItem("L model");
    connect(ui->graph, SIGNAL(activated(int)), this, SLOT(graphModel(int)));

    ui->format->addItem("GML");
    ui->format->addItem("CSV Edges Table");
    ui->format->addItem("CSV Adjacency List");
    ui->format->addItem("CSV Matrix");
    connect(ui->format, SIGNAL(activated(int)), this, SLOT(formatType(int)));

    connect(ui->dialogButtonBox, SIGNAL(accepted()), this, SLOT(acc()));


}

SaveDialog::~SaveDialog() {
    delete ui;
}

void SaveDialog::graphModel(int val) {
    switch (val) {
        case 0:
            graph = C_MODEL;
            break;
        case 1:
            graph = L_MODEL;
            break;
    }
}

void SaveDialog::formatType(int val) {
    switch (val) {
        case 0:
            format = GML;
            break;
        case 1:
            format = CSV_EDGES_TABLE;
            break;
        case 2:
            format = CSV_ADJACENCY_LIST;
            break;
        case 3:
            format = CSV_MATRIX;
            break;

    }
}


void SaveDialog::acc() {
    std::string form = (format == GML) ? "GML files (*.gml)" : "CSV files (*.csv)";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/", tr(form.c_str()));

    GraphFormatGenerator *generator;
    OutputFileFormater *formater;
    if (graph == L_MODEL)
        generator = new LGraphGenerator(network_);
    else
        generator = new CGraphGenerator(network_);

    if (format == GML)
        formater = new GmlOutput(*generator, fileName.QString::toStdString());
    else {
        CsvOutput::Type typeOfCsv;
        if (format == CSV_EDGES_TABLE)
            typeOfCsv = CsvOutput::EDGES_TABLE;
        else if (format == CSV_ADJACENCY_LIST)
            typeOfCsv = CsvOutput::ADJACENCY_LIST;
        else
            typeOfCsv = CsvOutput::MATRIX;

        formater = new CsvOutput(*generator, fileName.QString::toStdString(), typeOfCsv);
    }

    formater->makeFile();
    delete generator;
    delete formater;

}

