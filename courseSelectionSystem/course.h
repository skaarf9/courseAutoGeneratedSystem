/*
��Ϊ�γ�,��ָһ��ѧ����һ����ʦ����ķ�Χ,����:
Ӣ���,����ʦ����ķ�Χ
�����Χ��Ҫ�����༶
��Ҫ���ֵ���:
  1,����ʦ���ͬʱ����һ���Ӣ�����ѧ,��������"course"����ͬһ��.��ѧ�Ʋ�ͬ��"course"�ǲ�ͬ��;
  2,����ʦ����һ��������Ӣ��,����������ͬһ"course"��������ʦ�����Ӣ��İ༶�γ�;
  3,һ��������Ӣ��������ʦ��,��ѧ������ʦ��,��ֱ�����������ʦ�����Ӣ��İ༶�γ���������ʦ�������ѧ�İ༶�γ�
  4,һ��������Ӣ��������ʦ��,�������İ��Ӣ��������ʦ��,��Ҳ���ڲ�ͬ��"course"
  5,����ѧ���е�λ������(��λ��),�������һ��˵��,����˵Ӣ��ĵ�λ������Ϊ2,Ҳ����ÿ��������ͱ���ֳ���һ��course,������course�ǿ�����ͬһ����ʦ�����,������Ҳ��������ͬ��course,��Ϊ�༶��ͬ,�Ͽ�ʱ���Ǵ���
�ܽ�:
  ��ͬ��"course"ֻ��(��ʦ, ѧ��, �༶��)��������Ψһ��,������ʦ����İ༶�����Ǹ���϶���,��Ҫע��,������һ���Ǹ����,�����Ǹ����
*/
#pragma once
#include "myClass.h"
#include <vector>
#include <string>
#include "classroomAndTime.h"
#include "teacher.h"
using namespace std;

class course {
public:
	/*����<����, ���ڱȽ�workload*/
	bool operator < (const course& other_one);
	/*��ȡ�γ���Ϣ*/
	string getInfo();
	/*���캯��*/
	course(teacher teacher, subject subject, vector<myClass> cla) :teacher(teacher), subject(subject), classes(cla){};
	/*��ȡѧ��subject*/
	subject getSubject()const;
	/*����ʱ�������*/
	void set_room_time(classroomAndTime room_time);
	/*�γ��Ƿ��г�ͻ*/
	bool isConflict(const course& other_one, int cmpIndex);
	/*��ȡʱ�������*/
	classroomAndTime getClassroomAndTime();
	/*��ȡ��ʦ*/
	teacher getTeacher();
private:
	/*��ʦid*/
	teacher teacher;
	/*ѧ��id*/
	subject subject;
	/*����İ༶*/
	vector<myClass> classes;
	/*ʱ�������*/
	classroomAndTime room_time;
};