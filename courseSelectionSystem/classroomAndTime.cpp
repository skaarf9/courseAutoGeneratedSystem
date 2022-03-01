#include "classroomAndTime.h"

string classroomAndTime::getInfo()
{
	string result = string();
	result.append("���ұ��: " + this->room.getName() + "\nÿ�ܿγ�: \n");
	for (WeeklyLesson i : this->time.getWeeklyLessons()) {
		result.append(i.getInfo());
	}
	result.append(to_string(static_cast<int>(this->time.getStartWeek())) + "~" + to_string(static_cast<int>(this->time.getEndWeek())) + "��\n");
	return result;
}

bool classroomAndTime::isConflict(const classroomAndTime& other_one, int cmpIndex)
{
	/*���������ͬ,����ʱ����ͬ,�Ż��ͻ*/
	return this->room == other_one.room && this->time.isConflicting(other_one.time, cmpIndex);
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
