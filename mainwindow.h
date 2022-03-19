#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "propertiesreader.h"
#include <QMainWindow>
#include "mysqlutil.h"
#include <QSqlQuery>
#include <sstream>
#include "courseSelectionStrategy.h"
#include <QMessageBox>
#include <QStandardItemModel>
#include <coursedisplaywidget.h>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
