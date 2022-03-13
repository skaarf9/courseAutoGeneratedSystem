#ifndef COURSEDISPLAYWIDGET_H
#define COURSEDISPLAYWIDGET_H

#include <QWidget>

namespace Ui {
class CourseDisplayWidget;
}

class CourseDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CourseDisplayWidget(QWidget *parent = nullptr);
    ~CourseDisplayWidget();

private:
    Ui::CourseDisplayWidget *ui;
};

#endif // COURSEDISPLAYWIDGET_H
