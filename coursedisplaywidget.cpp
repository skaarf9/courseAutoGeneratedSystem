#include "coursedisplaywidget.h"
#include "ui_coursedisplaywidget.h"

CourseDisplayWidget::CourseDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CourseDisplayWidget)
{
    ui->setupUi(this);
}

CourseDisplayWidget::~CourseDisplayWidget()
{
    delete ui;
}
