#pragma once
#include<string>
using namespace std;

/*ѧ����*/
class subject
{
public:
	/*��ȡ��ӡ��Ϣ*/
	string getInfo();
	/*���캯��*/
	subject(string name, int workload, int subject_id, int duration, int weeklyLessonNum) :name(name), workload(workload), duration(duration), subject_id(subject_id), weeklyLessonNum(weeklyLessonNum){};
	/*��ȡ��λ������*/
	int getWorkload();
	/*���õ�λ������*/
	void setWorkload(int workload);
	/*����ÿ�ܿ�ʱ*/
	void setWeeklyLessonNum(int num);
	/*��ȡ����*/
	string getName();
	/*��ȡѧ��id*/
	int getSubjectID();
	/*��ȡѧ���ܿ�ʱ*/
	int getDuration();
	/*��ȡѧ��ÿ�ܿ�ʱ*/
	int getWeeklyLessonNum();
private:
	/*ѧ��id*/
	int subject_id;
	/*ѧ������*/
	string name;
	/*��λ������(��λ��)*/
	int workload;
	/*ѧ���ܿ�ʱ(��λ�ճ����ڿ�,һ�첻����ϰ�ܹ����Ŀ�ʱ,��������)*/
	int duration;
	/*ÿ�ܿ�ʱ*/
	int weeklyLessonNum;
};

