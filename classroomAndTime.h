#pragma once
#include "classroom.h"
#include "myTime.h"

class classroomAndTime
{
public:
	/*获取全部信息*/
    std::string getInfo();
	/*是否冲突*/
	bool isConflict(const classroomAndTime& other_one, WeeklyLesson weeklyLesson);
	/*构造函数*/
	classroomAndTime(classroom room, myTime time): room (room), time(time){};
	classroomAndTime() {};
	/*获取时间*/
	myTime getTime()const;
	/*设置教室*/
	void setClassroom(classroom room);
    /* 获取教室 */
    classroom getClassroom();
	/*设置时间*/
	void setTime(myTime time);
	/*添加每周上课时间*/
	void addClassTimeWeekly(WeeklyLesson ls);
	/*判断是否为空*/
	bool isEmpty();
private:
	/*教室,如果有多节,教室也必须是同一个*/
	classroom room;
	/*时间*/
	myTime time;
};

