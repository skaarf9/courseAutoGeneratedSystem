#pragma once
#include"course.h"
#include"teacher.h"
#include<algorithm>

class courseSelectTeacherStrategy
{
public:
	/*为课程分配老师*/
	void courseSelectT();
	/*构造函数*/
	courseSelectTeacherStrategy(vector<teacher> teachers, vector<subject> subjects, vector<myClass> classes, vector<classroom> rooms) :teachers(teachers), subjects(subjects), classes(classes), rooms(rooms){};
	
private:
	vector<myClass> classes;
	vector<subject> subjects;
	vector<course> courses;
	vector<teacher> teachers;
	/*选择老师算法所需的矩阵*/
	vector<vector<int>> matrix;
	/*教室*/
	vector<classroom> rooms;

	/*初始化矩阵,传入subjects的原因是我们需要在init_matrix中修改subjects的数据,但是在类中我们不需要改,所以传值就好了*/
	void init_matrix(vector<subject> subjects);
	/*转化学科中的单位工作量(数字代表班级数量)为所需工作量(根据班级数量转化为所需数量)*/
	vector<subject> changeSubjects(vector<subject> subjects);
};

