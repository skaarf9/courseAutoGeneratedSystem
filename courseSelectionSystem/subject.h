#pragma once
#include<string>
using namespace std;

/*学科类*/
class subject
{
public:
	/*获取打印信息*/
	string getInfo();
	/*构造函数*/
	subject(string name, int workload, int subject_id, int duration, int weeklyLessonNum) :name(name), workload(workload), duration(duration), subject_id(subject_id), weeklyLessonNum(weeklyLessonNum){};
	/*获取单位工作量*/
	int getWorkload();
	/*设置单位工作量*/
	void setWorkload(int workload);
	/*设置每周课时*/
	void setWeeklyLessonNum(int num);
	/*获取名称*/
	string getName();
	/*获取学科id*/
	int getSubjectID();
	/*获取学科总课时*/
	int getDuration();
	/*获取学科每周课时*/
	int getWeeklyLessonNum();
private:
	/*学科id*/
	int subject_id;
	/*学科名称*/
	string name;
	/*单位工作量(单位班)*/
	int workload;
	/*学科总课时(单位日常两节课,一天不算自习总共有四课时,早晚两个)*/
	int duration;
	/*每周课时*/
	int weeklyLessonNum;
};

