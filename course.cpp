#include "course.h"

bool course::operator<(const course & other_one)
{
	/*让course从大到小排序,我们需要先满足大的课程的教室选择,然后满足小的*/
	return this->getSubject().getWorkload() > other_one.getSubject().getWorkload();
}

/*课程中显示所有信息的方法*/
std::string course::getInfo() {
	/*分隔符*/
    std::string result = "----------------------\n";
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

classroomAndTime course::getClassroomAndTime()
{
	return this->room_time;
}

teacher course::getTeacher()
{
	return this->teacher;
}

std::vector<myClass> course::getClasses()
{
	return this->classes;
}

void course::addClassTimeWeekly(WeeklyLesson ls)
{
	this->room_time.addClassTimeWeekly(ls);
}
