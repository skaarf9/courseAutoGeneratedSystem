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

QString getClassesNameFromVector(std::vector<myClass> classes){
    QString result;
    for(myClass c : classes){
        result.append(QString::fromStdString(c.getClassName() + "\n"));
    }
    return result.trimmed();
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
    connect(ui->btn_login, &QPushButton::clicked, this,[=]()mutable{
        try{
            MysqlUtil sql(ui->editer_UserName->text(), ui->editer_password->text());
        }catch(std::exception e){
            QMessageBox::critical(this, "登录信息", "登录失败");
            return;
        }
        QMessageBox::information(this, "登录信息", "登录成功!");
        propReader.writeProperties("username", ui->editer_UserName->text());
        propReader.writeProperties("password", ui->editer_password->text());
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
        courseSelectTeacherStrategy cs = courseSelectTeacherStrategy(teachers, subjects, classes, classrooms);
//        std::vector<course> courses = cs.getCourses();
        std::vector<course> courses = cs.getWeeklyLessonByClass({1}, 2);
        for(course c : courses){
            CourseDisplayWidget* courseWidget = new CourseDisplayWidget();
            courseWidget->findChild<QLabel*>("subject")->setText(QString::fromStdString(c.getSubject().getName()));
            courseWidget->findChild<QLabel*>("teacher")->setText(QString::fromStdString(c.getTeacher().getTeacherName()));
            courseWidget->findChild<QLabel*>("classroom")->setText(QString::fromStdString(c.getClassroomAndTime().getClassroom().getName()));
            courseWidget->findChild<QLabel*>("classes")->setText(getClassesNameFromVector(c.getClasses()));
            courseWidget->findChild<QLabel*>("weeks")->setText(QString::fromStdString(c.getClassroomAndTime().getTime().getWeeklyTimes()));
            std::vector<WeeklyLesson> weeklyLesson = c.getClassroomAndTime().getTime().getWeeklyLessons();
            for (WeeklyLesson l : weeklyLesson){
                int col = static_cast<int>(l.getWeek());
                int row = static_cast<int>(l.getDailyLesson());
                switch(row){
                  case 0:
                    row = 1;
                    break;
                  case 1:
                    row = 3;
                    break;
                  case 2:
                    row = 7;
                    break;
                  case 3:
                    row = 8;
                    break;
                  default:
                    break;
                }
//                std::cout << l.getInfo() << std::endl << col << row << std::endl;
                this->ui->coursesDisplay->addWidget(courseWidget, row, col + 1);
            }
        }
//        CourseDisplayWidget* courseWidget = new CourseDisplayWidget();
//        courseWidget->findChild<QLabel*>("subject")->setText("测试学科");
//        courseWidget->findChild<QLabel*>("teacher")->setText("测试老师");
//        courseWidget->findChild<QLabel*>("classroom")->setText("测试教室");
//        courseWidget->findChild<QLabel*>("classes")->setText("测试班级\n测试班级");
//        courseWidget->findChild<QLabel*>("weeks")->setText("1~10周");
//        this->ui->coursesDisplay->addWidget(courseWidget, 8, 1);
        //跳转到下一页
        this->ui->stackedWidget->setCurrentIndex(1);
//        new QStandardItem()
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

