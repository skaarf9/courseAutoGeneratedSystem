#include "myTime.h"

bool myTime::isConflict(const myTime & other_time, WeeklyLesson weeklyLesson)
{
	/*如果A在B结束后开始, 或者A在B开始前结束, 那么A与B就不相交, 我们取反,就是A与B相交的情况*/
	if (!(this->startWeek > other_time.endWeek || this->endWeek < other_time.startWeek)) {
		/*遍历A中的每周课程,如果与weeklyLesson重合那么就会产生冲突*/
		for (WeeklyLesson this_one : this->weeklyLessons) {
			if (this_one == weeklyLesson)
			{
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

void myTime::addWeeklyLessons(WeeklyLesson lesson)
{
	this->weeklyLessons.push_back(lesson);
}

int WeeklyLesson::castToInt()
{
	return this->week * 4 + this->dailyLesson;
}

bool WeeklyLesson::operator==(const WeeklyLesson & other_one)
{
	return this->dailyLesson == other_one.dailyLesson && this->week == other_one.week;
}

bool WeeklyLesson::operator<(const WeeklyLesson & other_one)
{
	return this->week == other_one.week? this->dailyLesson < other_one.dailyLesson :this->week < other_one.week;
}

bool WeeklyLesson::operator<=(const WeeklyLesson & other_one)
{
	return this->week == other_one.week ? this->dailyLesson <= other_one.dailyLesson : this->week < other_one.week;
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
		result.append("星期一");
		break;
	case Tue:
		result.append("星期二");
		break;
	case Wed:
		result.append("星期三");
		break;
	case Thur:
		result.append("星期四");
		break;
	case Fri:
		result.append("星期五");
		break;
	case Sat:
		result.append("星期六");
		break;
	case Sun:
		result.append("星期日");
		break;
	default:
		break;
	}
	result.append(" 第");
	switch (dailyLesson)
	{
	case first:
		result.append("一");
		break;
	case second:
		result.append("二");
		break;
	case third:
		result.append("三");
		break;
	case forth:
		result.append("四");
		break;
	default:
		break;
	}
	result.append("节\n");
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
