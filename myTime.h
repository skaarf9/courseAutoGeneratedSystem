#pragma once
#include<string>
#include<vector>
#include <sstream>

enum Week {
	Mon,
	Tue,
	Wed,
	Thur,
	Fri,
	Sat,
	Sun
};
/*每天的课程*/
enum DailyLesson {
	//上午第一二节
	first,
	//上午第二三节
	second,
	//下午一二节
	third,
	//下午三四节
	forth
};

class WeeklyLesson {
public:
	/*返回该节课程对应的数字,数字范围为0-27(包括周六周末的情况)*/
	int castToInt();
	bool operator == (const WeeklyLesson& other_one);
	bool operator < (const WeeklyLesson& other_one);
	bool operator <= (const WeeklyLesson& other_one);
	/*返回一个每周第一节课程的时间*/
	static WeeklyLesson firstLesson();
	/*返回一个中间的时间*/
	static WeeklyLesson middleLesson();
	/*返回一个结尾的时间,默认为星期五第四节,如果需要计算周六周末则应该为周末第四节*/
	static WeeklyLesson lastLesson();
	/*返回信息*/
    std::string getInfo();
	/*课程向后推移*/
	WeeklyLesson operator ++ ();
	/*默认构造函数*/
	WeeklyLesson() {};
	/*有参构造函数*/
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
	/*构造函数,包含初始化列表*/
    myTime(unsigned short startWeek, unsigned short endWeek, std::vector<WeeklyLesson> weeklyLessons) : startWeek(startWeek), endWeek(endWeek), weeklyLessons(weeklyLessons) {};
	myTime(unsigned short startWeek, unsigned short endWeek) : startWeek(startWeek), endWeek(endWeek) {};
	myTime() {};
	/*检查时间是否冲突*/
	bool isConflict(const myTime& other_time, WeeklyLesson weeklyLesson);
	/*获取开始周*/
	unsigned short getStartWeek();
	/*获取结束周*/
	unsigned short getEndWeek();
    /* 获取周次信息 */
    std::string getWeeklyTimes();
	/*获取每周课程对应时间*/
    std::vector<WeeklyLesson> getWeeklyLessons();
	/*设置每周课程对应时间*/
    void setWeeklyLessons(std::vector<WeeklyLesson> ls);
	void setWeeklyLessons(int i, WeeklyLesson ls);
	/*添加每周课程时间*/
	void addWeeklyLessons(WeeklyLesson lesson);
private:
	/*周的限定范围为1-20*/
	/*开始周*/
	unsigned short startWeek;
	/*结束周*/
	unsigned short endWeek;
	/*每周课程的对应时间*/
    std::vector<WeeklyLesson> weeklyLessons;
};

