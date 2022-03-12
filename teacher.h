#pragma once
#include<vector>
#include<iostream>
#include <iomanip>
#include<string>
#include"subject.h"

/*教师类*/
class teacher {
public:
	/*重载 == 运算符*/
	bool operator == (const teacher& other_one);
    std::string getInfo();
	/*构造函数*/
    teacher(std::string name, int id, int workload):teacher_name(name), teacher_id(id), workload(workload){};
	/*设定教师的学科适合度*/
    void setSuitableIndex(std::vector<subject> subjects);
    void setSuitableIndex(int length, std::vector<int> index);
	/*打印学科合适度*/
    void printIndex(std::vector<subject> subjects);
	/*获取学科合适度向量*/
    std::vector<int> getSuitableIndex()const;
	/*获取工作量承受度*/
	int getWorkload() const;
	/*获取教师id*/
	int getTeacherID()const;
	/*获取教师名称*/
    std::string getTeacherName()const;
private:
	/*教师名称*/
    std::string teacher_name;
	/*教师id*/
	int teacher_id;
	/*教师相对于学科的合适程度*/
    std::vector<int> subjectSuitableIndex;
	/*工作量:能够负责的最大数量course*/
	int workload;
};
