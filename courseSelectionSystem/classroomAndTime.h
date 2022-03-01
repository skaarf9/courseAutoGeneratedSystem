#pragma once
#include "classroom.h"
#include "myTime.h"

class classroomAndTime
{
public:
	/*��ȡȫ����Ϣ*/
	string getInfo();
	/*�Ƿ��ͻ*/
	bool isConflict(const classroomAndTime& other_one, int cmpIndex);
	/*���캯��*/
	classroomAndTime(classroom room, myTime time): room (room), time(time){};
	classroomAndTime() {};
	/*��ȡʱ��*/
	myTime getTime()const;
	/*���ý���*/
	void setClassroom(classroom room);
	/*����ʱ��*/
	void setTime(myTime time);
private:
	/*����*/
	classroom room;
	/*ʱ��*/
	myTime time;
};

