#include "classroomAndTime.h"

string classroomAndTime::getInfo()
{
	string result = string();
	result.append("教室编号: " + this->room.getName() + " 教室大小: " + to_string(this->room.getCapacity()) + "\n每周课程: \n");
	for (WeeklyLesson i : this->time.getWeeklyLessons()) {
		result.append(i.getInfo());
	}
	result.append(to_string(static_cast<int>(this->time.getStartWeek())) + "~" + to_string(static_cast<int>(this->time.getEndWeek())) + "周\n");
	return result;
}

bool classroomAndTime::isConflict(const classroomAndTime& other_one, WeeklyLesson weeklyLesson)
{
	/*如果教室相同,并且时间相同,才会冲突*/
	return this->room == other_one.room && this->time.isConflict(other_one.time, weeklyLesson);
}

myTime classroomAndTime::getTime()const
{
	return this->time;
}

void classroomAndTime::setClassroom(classroom room)
{
	this->room = room;
}

void classroomAndTime::setTime(myTime time)
{
	this->time = time;
}

void classroomAndTime::addClassTimeWeekly(WeeklyLesson ls)
{
	this->time.addWeeklyLessons(ls);
}

bool classroomAndTime::isEmpty()
{
	return this->room.getName() == "";
}
