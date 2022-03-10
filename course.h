/*
此为课程,是指一个学科中一个老师负责的范围,比如:
英语课,李老师负责的范围
这个范围主要包括班级
需要区分的是:
  1,李老师如果同时负责一班的英语和数学,那这两个"course"不是同一个.即学科不同的"course"是不同的;
  2,李老师负责一班与二班的英语,这两个属于同一"course"即由李老师负责教英语的班级课程;
  3,一班与二班的英语由李老师上,数学由王老师上,这分别属于由李老师负责教英语的班级课程与由王老师负责教数学的班级课程
  4,一班与二班的英语由李老师上,三班与四班的英语由张老师上,这也属于不同的"course"
  5,由于学科有单位工作量(单位班),这里添加一项说明,比如说英语的单位工作量为2,也就是每隔两个班就必须分出来一个course,这俩个course是可以由同一个老师负责的,但是这也是两个不同的course,因为班级不同,上课时间是错开的
总结:
  不同的"course"只有(老师, 学科, 班级组)这个组合是唯一的,另外老师负责的班级往往是个组合对象,需要注意,例子中一二是个组合,三四是个组合
*/
#pragma once
#include "myClass.h"
#include <vector>
#include <string>
#include "classroomAndTime.h"
#include "teacher.h"
using namespace std;

class course {
public:
	/*重载<符号, 用于比较workload*/
	bool operator < (const course& other_one);
	/*获取课程信息*/
	string getInfo();
	/*构造函数*/
	course(teacher teacher, subject subject, vector<myClass> cla) :teacher(teacher), subject(subject), classes(cla){};
	/*获取学科subject*/
	subject getSubject()const;
	/*设置时间与教室*/
	void set_room_time(classroomAndTime room_time);
	/*获取时间与教室*/
	classroomAndTime getClassroomAndTime();
	/*获取老师*/
	teacher getTeacher();
	/*获取班级*/
	vector<myClass> getClasses();
	/*添加一个每周上课时间*/
	void addClassTimeWeekly(WeeklyLesson ls);
private:
	/*教师id*/
	teacher teacher;
	/*学科id*/
	subject subject;
	/*负责的班级*/
	vector<myClass> classes;
	/*时间与教室*/
	classroomAndTime room_time;
};