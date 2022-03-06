#pragma once
#include<string>
#include<vector>
using namespace std;

enum Week {
	Mon,
	Tue,
	Wed,
	Thur,
	Fri,
	Sat,
	Sun
};
/*ÿ��Ŀγ�*/
enum DailyLesson {
	//�����һ����
	first,
	//����ڶ�����
	second,
	//����һ����
	third,
	//�������Ľ�
	forth
};

class WeeklyLesson {
public:
	/*���ظýڿγ̶�Ӧ������,���ַ�ΧΪ0-27(����������ĩ�����)*/
	int castToInt();
	bool operator == (const WeeklyLesson& other_one);
	bool operator < (const WeeklyLesson& other_one);
	bool operator <= (const WeeklyLesson& other_one);
	/*����һ��ÿ�ܵ�һ�ڿγ̵�ʱ��*/
	static WeeklyLesson firstLesson();
	/*����һ���м��ʱ��*/
	static WeeklyLesson middleLesson();
	/*����һ����β��ʱ��,Ĭ��Ϊ��������Ľ�,�����Ҫ����������ĩ��Ӧ��Ϊ��ĩ���Ľ�*/
	static WeeklyLesson lastLesson();
	/*������Ϣ*/
	string getInfo();
	/*�γ��������*/
	WeeklyLesson operator ++ ();
	/*Ĭ�Ϲ��캯��*/
	WeeklyLesson() {};
	/*�вι��캯��*/
	WeeklyLesson(Week week, DailyLesson dailyLesson): week(week), dailyLesson(dailyLesson) {};
private:
	friend class myTime;
	Week week;
	DailyLesson dailyLesson;
};

class specificTime {
public:
	int week;
	WeeklyLesson weeklyLesson;
	specificTime(int week, WeeklyLesson weeklyLesson) : week(week), weeklyLesson(weeklyLesson) {};
};

class myTime
{
public:
	/*���캯��,������ʼ���б�*/
	myTime(unsigned short startWeek, unsigned short endWeek, vector<WeeklyLesson> weeklyLessons) : startWeek(startWeek), endWeek(endWeek), weeklyLessons(weeklyLessons) {};
	myTime() {};
	/*���ʱ���Ƿ��ͻ*/
	bool isConflict(const myTime& other_time, WeeklyLesson weeklyLesson);
	/*��ȡ��ʼ��*/
	unsigned short getStartWeek();
	/*��ȡ������*/
	unsigned short getEndWeek();
	/*��ȡÿ�ܿγ̶�Ӧʱ��*/
	vector<WeeklyLesson> getWeeklyLessons();
	/*����ÿ�ܿγ̶�Ӧʱ��*/
	void setWeeklyLessons(vector<WeeklyLesson> ls);
	void setWeeklyLessons(int i, WeeklyLesson ls);
	/*���ÿ�ܿγ�ʱ��*/
	void addWeeklyLessons(WeeklyLesson lesson);
private:
	/*�ܵ��޶���ΧΪ1-20*/
	/*��ʼ��*/
	unsigned short startWeek;
	/*������*/
	unsigned short endWeek;
	/*ÿ�ܿγ̵Ķ�Ӧʱ��*/
	vector<WeeklyLesson> weeklyLessons;
};

