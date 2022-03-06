#include "subject.h"

string subject::getInfo()
{
	string result = string();
	result.append("ѧ��id: " + to_string(this->subject_id));
	result.append(" ѧ������: " + this->name);
	result.append("\n��λ������(�ɽ��ܵİ༶����) " + to_string(this->workload));
	result.append("\nѧ�ƿ�ʱ: " + to_string(this->duration));
	result.append("\nÿ�ܿ�ʱ: " + to_string(this->weeklyLessonNum) + "\n");
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
