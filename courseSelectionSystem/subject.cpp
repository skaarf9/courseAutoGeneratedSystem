#include "subject.h"

string subject::getInfo()
{
	string result = string();
	result.append("学科id: " + to_string(this->subject_id));
	result.append(" 学科名称: " + this->name);
	result.append("\n单位工作量(可接受的班级数量) " + to_string(this->workload));
	result.append("\n学科课时: " + to_string(this->duration));
	result.append("\n每周课时: " + to_string(this->weeklyLessonNum) + "\n");
	return result;
}

int subject::getWorkload()
{
	return this->workload;
}

void subject::setWorkload(int workload)
{
	this->workload = workload;
}

void subject::setWeeklyLessonNum(int num)
{
	this->weeklyLessonNum = num;
}

string subject::getName()
{
	return this->name;
}

int subject::getSubjectID()
{
	return this->subject_id;
}

int subject::getDuration()
{
	return this->duration;
}

int subject::getWeeklyLessonNum()
{
	return this->weeklyLessonNum;
}
