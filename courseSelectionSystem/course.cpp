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

bool course::isConflict(const course& other_one, int cmpIndex)
{
	/*���ʱ������ʦ��ͬ����ʱ���������ͬ����ʱ����༶��ͻ,��һ����ͻ��γ̳�ͻ*/
	bool time_teacher = this->teacher == other_one.teacher && this->room_time.getTime().isConflicting(other_one.room_time.getTime(), cmpIndex);
	bool time_room = this->room_time.isConflict(other_one.room_time, cmpIndex);
	//todo �༶��ͻ���
	bool time_class = true;
	return time_teacher && time_class && time_room;
}

classroomAndTime course::getClassroomAndTime()
{
	return this->room_time;
}

teacher course::getTeacher()
{
	return this->teacher;
}
