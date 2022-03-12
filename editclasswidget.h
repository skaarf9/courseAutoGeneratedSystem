#ifndef EDITCLASSWIDGET_H
#define EDITCLASSWIDGET_H

#include <QWidget>

namespace Ui {
class EditClassWidget;
}

class EditClassWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditClassWidget(QWidget *parent = nullptr);
    ~EditClassWidget();

private:
    Ui::EditClassWidget *ui;
};

#endif // EDITCLASSWIDGET_H
