#pragma once
#include"course.h"
#include"teacher.h"
#include<algorithm>

class courseSelectTeacherStrategy
{
public:
	/*为课程分配老师与班级*/
	void courseSelectTeacherAndClass();

	/* 为课程分配教室与时间 */
	void courseSelectClassroomAndTime();
	/* 根据完成的排课情况,打印出对应班级的每周课程信息 */
	void getWeeklyLessonByClass(myClass myClass);

	/* 根据完成的排课情况,打印出对应老师的每周课程信息 */
	void getWeeklyLessonByTeacher(teacher t);
	/*构造函数*/
    courseSelectTeacherStrategy(std::vector<teacher> teachers, std::vector<subject> subjects, std::vector<myClass> classes, std::vector<classroom> rooms) :teachers(teachers), subjects(subjects), classes(classes), rooms(rooms){
		courseSelectTeacherAndClass();
		courseSelectClassroomAndTime();
	};
	
private:
    std::vector<myClass> classes;
    std::vector<subject> subjects;
    std::vector<course> courses;
    std::vector<teacher> teachers;
	/*选择老师算法所需的矩阵*/
    std::vector<std::vector<int>> matrix;
	/*教室*/
    std::vector<classroom> rooms;

	/*初始化矩阵,传入subjects的原因是我们需要在init_matrix中修改subjects的数据,但是在类中我们不需要改,所以传值就好了*/
    void init_matrix(std::vector<subject> subjects);
	/*转化学科中的单位工作量(数字代表班级数量)为所需工作量(根据班级数量转化为所需数量)*/
    std::vector<subject> changeSubjects(std::vector<subject> subjects);
};

