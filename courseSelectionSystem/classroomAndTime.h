#pragma once
#include "classroom.h"
#include "myTime.h"

class classroomAndTime
{
public:
	/*获取全部信息*/
	string getInfo();
	/*是否冲突*/
	bool isConflict(const classroomAndTime& other_one, int cmpIndex);
	/*构造函数*/
	classroomAndTime(classroom room, myTime time): room (room), time(time){};
	classroomAndTime() {};
	/*获取时间*/
	myTime getTime()const;
	/*设置教室*/
	void setClassroom(classroom room);
	/*设置时间*/
	void setTime(myTime time);
private:
	/*教室*/
	classroom room;
	/*时间*/
	myTime time;
};

