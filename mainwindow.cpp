#include "mainwindow.h"
#include "ui_mainwindow.h"


std::vector<int> Stringsplit(std::string str,const char split)
{
    std::istringstream iss(str);	// 输入流
    std::string token;			// 接收缓冲区
    std::vector<int> result;
    while (getline(iss, token, split))	// 以split为分隔符
    {
        result.push_back(atoi(token.c_str()));
    }
    return result;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    PropertiesReader propReader("../GraduationProject/sql.properties");
    QHash config = propReader.getResult();
    QString username = config.take("username");
    QString password = config.take("password");
    ui->editer_UserName->setText(username);
    ui->editer_password->setText(password);
    courseSelectTeacherStrategy* cs;
    connect(ui->btn_login, &QPushButton::clicked, this,[=]()mutable{
        try{
            MysqlUtil sql(ui->editer_UserName->text(), ui->editer_password->text());
        }catch(std::exception e){
            QMessageBox::critical(this, "登录信息", "登录失败");
            return;
        }
        QMessageBox::information(this, "登录信息", "登录成功!");
        QSqlQuery query;
        //添加班级信息
        std::vector<myClass> classes;
        query.exec("select * from s_class");
        while(true == query.next()){
            classes.push_back(myClass(query.value("s_id").toInt(), query.value("s_name").toString().toStdString()));
        }
        //添加教室信息
        std::vector<classroom> classrooms;
        query.exec("select * from s_classroom");
        while(true == query.next()){
            classrooms.push_back(classroom(query.value("s_name").toString().toStdString(), query.value("s_capacity").toInt()));
        }
        //添加学科信息
        std::vector<subject> subjects;
        query.exec("select * from s_subject");
        while(true == query.next()){
            subjects.push_back(subject(query.value("s_name").toString().toStdString(), query.value("s_workload").toInt(), query.value("s_id").toInt(), query.value("s_duration").toInt(), query.value("s_weeklyLessonNum").toInt()));
        }
        int subject_size = subjects.size();
        //添加教师信息
        std::vector<teacher> teachers;
        query.exec("select * from s_teacher");
        while(true == query.next()){
            teacher t = teacher(query.value("s_name").toString().toStdString(), query.value("s_id").toInt(), query.value("s_workload").toInt());
            t.setSuitableIndex(subject_size, Stringsplit(query.value("s_subject_suitable_index").toString().toStdString(), ','));
            teachers.push_back(t);
        }
        cs = new courseSelectTeacherStrategy(teachers, subjects, classes, classrooms);
        ui->stackedWidget->setCurrentIndex(1);
        QStandardItemModel* model = new QStandardItemModel;
        ui->courseView->setModel(model);
        model->setHorizontalHeaderItem(0, new QStandardItem("姓名") );
        model->setHorizontalHeaderItem(1, new QStandardItem("学号"));
        model->setHorizontalHeaderItem(2, new QStandardItem("性别"));
        model->setHorizontalHeaderItem(3, new QStandardItem("年龄"));
        model->setHorizontalHeaderItem(4, new QStandardItem("院系"));
        model->setHorizontalHeaderItem(5, new QStandardItem("兴趣"));
        new QStandardItem()
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

