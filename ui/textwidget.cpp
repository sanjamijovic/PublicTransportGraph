#include "textwidget.h"
#include "ui_textwidget.h"

TextWidget::TextWidget(const QString &output, QWidget *parent) :
        QWidget(parent),
        ui(new Ui::TextWidget) {
    ui->setupUi(this);
    ui->text->setText(output);
}

TextWidget::~TextWidget() {
    delete ui;
}
