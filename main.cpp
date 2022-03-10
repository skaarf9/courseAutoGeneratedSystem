#include "mainwindow.h"
#include "course.h"
#include <iostream>
#include "teacher.h"
#include "courseSelectionStrategy.h"
#include "classroomAndTime.h"
#include <QApplication>

using namespace std;




/*全局变量*/

/*班级*/
myClass c1 = myClass(11, "一年级一班");
myClass c2 = myClass(12, "一年级二班");
myClass c3 = myClass(13, "一年级三班");
myClass c4 = myClass(14, "一年级四班");
myClass c5 = myClass(15, "一年级五班");
myClass c6 = myClass(16, "一年级六班");
myClass c7 = myClass(17, "一年级七班");
myClass c8 = myClass(18, "一年级八班");
vector<myClass> classes = { c1, c2, c3, c4, c5, c6, c7, c8 };

/*学科*/
/*左边为学科名称, 单位工作量为一名老师能够负责多少个班的该学科,和老师的工作量有点关系,老师的是能够承受的工作量单位,这里的就是就是多少个班的该学科授课任务对应老师的一个工作量单位*/
vector<subject> subjects = {
    /*名称 单位工作量 学科序号 学科课时(随机的) 每周课时*/
    {"语文", 1, 1, 30, 4},
    {"数学", 1, 2, 30, 4},
    {"英语", 1, 3, 30, 4},
    {"物理", 2, 4, 16, 3},
    {"化学", 4, 5, 21, 3},
    {"历史", 4, 6, 15, 1},
    {"生物", 4, 7, 17, 3},
    {"地理", 3, 8, 19, 2},
    {"政治", 3, 9, 24, 2},
    {"体育", 3, 10, 14, 2},
};
/*教师数据*/
teacher t1 = teacher("张老师", 1, 7);
teacher t2 = teacher("李老师", 2, 6);
teacher t3 = teacher("王老师", 3, 6);
teacher t4 = teacher("周老师", 4, 4);
teacher t5 = teacher("谢老师", 5, 5);
teacher t6 = teacher("郑老师", 6, 5);
teacher t7 = teacher("杨老师", 7, 9);
teacher t8 = teacher("哈老师", 8, 6);
teacher t9 = teacher("安老师", 9, 7);

/* 教室数据 */
vector<classroom> classrooms = {
    {"1101", 2},
    {"1102", 2},
    {"1103", 2},
    {"1104", 4},
    {"1201", 2},
    {"1202", 4}/*,
    {"1203", 4},
    {"1204", 2},*/
};



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //教师的合适度
    t1.setSuitableIndex(subjects.size(), { 1, 6, 8, 7, 4, 9, 1, 3, 10, 9 });
    t2.setSuitableIndex(subjects.size(), { 7, 4, 10, 1, 9, 6, 10, 5, 2, 8 });
    t3.setSuitableIndex(subjects.size(), { 1, 1, 8, 3, 6, 1, 1, 0, 10, 7 });
    t4.setSuitableIndex(subjects.size(), { 4, 8, 3, 10, 4, 8, 10, 0, 1, 2 });
    t5.setSuitableIndex(subjects.size(), { 4, 1, 10, 9, 0, 8, 0, 3, 10, 4 });
    t6.setSuitableIndex(subjects.size(), { 1, 6, 4, 6, 0, 9, 5, 6, 1, 7 });
    t7.setSuitableIndex(subjects.size(), { 5, 6, 10, 1, 5, 0, 6, 5, 5, 10 });
    t8.setSuitableIndex(subjects.size(), { 3, 5, 5, 9, 2, 4, 1, 0, 10, 3 });
    t9.setSuitableIndex(subjects.size(), { 9, 3, 2, 7, 1, 6, 5, 6, 2, 9 });
    vector<teacher> teachers = vector<teacher>{
    t1, t2, t3, t4, t5, t6, t7, t8, t9
    };
    /*for (auto i : teachers) {
        i.printIndex(subjects);
    }*/
    vector<course> courses;
//    courseSelectTeacherStrategy cs = courseSelectTeacherStrategy(teachers, subjects, classes, classrooms);
//    cout << "------------------查询班级---------------" << endl;
//    cs.getWeeklyLessonByClass(c1);
//    cout << "------------------查询教师---------------" << endl;
//    cs.getWeeklyLessonByTeacher(t1);
    MainWindow w;
    w.show();
    return a.exec();
}
