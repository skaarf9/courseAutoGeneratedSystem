#include "course.h"

bool course::operator<(const course & other_one)
{
	/*��course�Ӵ�С����,������Ҫ�������Ŀγ̵Ľ���ѡ��,Ȼ������С��*/
	return this->getSubject().getWorkload() > other_one.getSubject().getWorkload();
}

/*�γ�����ʾ������Ϣ�ķ���*/
string course::getInfo() {
	/*�ָ���*/
	string result = "----------------------\n";
	result += this->teacher.getInfo() + this->subject.getInfo() + "����İ༶: \n";
	for(myClass classInstance : this->classes)
	{
		result.append(classInstance.getInfo());
	}
	result.append(this->room_time.getInfo());
	return result;
}

subject course::getSubject()const
{
	return this->subject;
}

void course::set_room_time(classroomAndTime room_time)
{
	this->room_time = room_time;
}

classroomAndTime course::getClassroomAndTime()
{
	return this->room_time;
}

teacher course::getTeacher()
{
	return this->teacher;
}

vector<myClass> course::getClasses()
{
	return this->classes;
}

void course::addClassTimeWeekly(WeeklyLesson ls)
{
	this->room_time.addClassTimeWeekly(ls);
}
