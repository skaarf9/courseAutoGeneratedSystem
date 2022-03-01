#include "myTime.h"

bool myTime::isConflicting(const myTime & other_time, int cmpIndex)
{
	/*���A��B������ʼ, ����A��B��ʼǰ����, ��ôA��B�Ͳ��ཻ, ����ȡ��,����A��B�ཻ�����*/
	if (!(this->startWeek > other_time.endWeek || this->endWeek < other_time.startWeek)) {
		/*����A�е�ÿ�ܿγ�,�����B�е�ÿ�ܿγ��غ���ô�ͻ������ͻ*/
		for (WeeklyLesson this_one : this->weeklyLessons) {
			if (this_one.dailyLesson == other_time.weeklyLessons[cmpIndex].dailyLesson && this_one.week == other_time.weeklyLessons[cmpIndex].week) {
				return true;
			}
		}
	}
	return false;
}

unsigned short myTime::getStartWeek()
{
	return this->startWeek;
}

unsigned short myTime::getEndWeek()
{
	return this->endWeek;
}

vector<WeeklyLesson> myTime::getWeeklyLessons()
{
	return this->weeklyLessons;
}

void myTime::setWeeklyLessons(vector<WeeklyLesson> ls)
{
	this->weeklyLessons = ls;
}

void myTime::setWeeklyLessons(int i, WeeklyLesson ls)
{
	this->weeklyLessons[i] = ls;
}

int WeeklyLesson::castToInt()
{
	return this->week * 4 + this->dailyLesson;
}

bool WeeklyLesson::operator==(const WeeklyLesson & other_one)
{
	return this->dailyLesson == other_one.dailyLesson && this->week == other_one.week;
}

WeeklyLesson WeeklyLesson::firstLesson()
{
	return WeeklyLesson(Mon, first);
}

WeeklyLesson WeeklyLesson::middleLesson()
{
	return WeeklyLesson(Wed, third);
}

WeeklyLesson WeeklyLesson::lastLesson()
{
	return WeeklyLesson(Fri, forth);
}

string WeeklyLesson::getInfo()
{
	string result = string();
	switch (week) {
	case Mon:
		result.append("����һ");
		break;
	case Tue:
		result.append("���ڶ�");
		break;
	case Wed:
		result.append("������");
		break;
	case Thur:
		result.append("������");
		break;
	case Fri:
		result.append("������");
		break;
	case Sat:
		result.append("������");
		break;
	case Sun:
		result.append("������");
		break;
	default:
		break;
	}
	result.append(" ��");
	switch (dailyLesson)
	{
	case first:
		result.append("һ");
		break;
	case second:
		result.append("��");
		break;
	case third:
		result.append("��");
		break;
	case forth:
		result.append("��");
		break;
	default:
		break;
	}
	result.append("��\n");
	return result;
}

WeeklyLesson WeeklyLesson::operator++()
{
	this->dailyLesson = static_cast<DailyLesson>((static_cast<int>(this->dailyLesson) + 1) % 4);
	if (this->dailyLesson == first) {
		this->week = static_cast<Week>((static_cast<int>(this->week) + 1) % 7);
	}
	return *this;
}
