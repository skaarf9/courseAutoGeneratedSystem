#include "course.h"

bool course::operator<(const course & other_one)
{
	/*让course从大到小排序,我们需要先满足大的课程的教室选择,然后满足小的*/
	return this->getSubject().getWorkload() > other_one.getSubject().getWorkload();
}

/*课程中显示所有信息的方法*/
string course::getInfo() {
	/*分隔符*/
	string result = "----------------------\n";
	result += this->teacher.getInfo() + this->subject.getInfo() + "负责的班级: \n";
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
	/*如果时间与老师相同或者时间与教室相同或者时间与班级冲突,有一样冲突则课程冲突*/
	bool time_teacher = this->teacher == other_one.teacher && this->room_time.getTime().isConflicting(other_one.room_time.getTime(), cmpIndex);
	bool time_room = this->room_time.isConflict(other_one.room_time, cmpIndex);
	//todo 班级冲突检测
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
