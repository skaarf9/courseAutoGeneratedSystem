#include "editclasswidget.h"
#include "ui_editclasswidget.h"

EditClassWidget::EditClassWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditClassWidget)
{
    ui->setupUi(this);
}

EditClassWidget::~EditClassWidget()
{
    delete ui;
}
