#pragma once
#include "classroom.h"
#include "myTime.h"

class classroomAndTime
{
public:
	/*��ȡȫ����Ϣ*/
	string getInfo();
	/*�Ƿ��ͻ*/
	bool isConflict(const classroomAndTime& other_one, WeeklyLesson weeklyLesson);
	/*���캯��*/
	classroomAndTime(classroom room, myTime time): room (room), time(time){};
	classroomAndTime() {};
	/*��ȡʱ��*/
	myTime getTime()const;
	/*���ý���*/
	void setClassroom(classroom room);
	/*����ʱ��*/
	void setTime(myTime time);
	/*���ÿ���Ͽ�ʱ��*/
	void addClassTimeWeekly(WeeklyLesson ls);
	/*�ж��Ƿ�Ϊ��*/
	bool isEmpty();
private:
	/*����,����ж��,����Ҳ������ͬһ��*/
	classroom room;
	/*ʱ��*/
	myTime time;
};

