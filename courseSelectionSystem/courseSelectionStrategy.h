#pragma once
#include"course.h"
#include"teacher.h"
#include<algorithm>

class courseSelectTeacherStrategy
{
public:
	/*Ϊ�γ̷�����ʦ*/
	void courseSelectT();
	/*���캯��*/
	courseSelectTeacherStrategy(vector<teacher> teachers, vector<subject> subjects, vector<myClass> classes, vector<classroom> rooms) :teachers(teachers), subjects(subjects), classes(classes), rooms(rooms){};
	
private:
	vector<myClass> classes;
	vector<subject> subjects;
	vector<course> courses;
	vector<teacher> teachers;
	/*ѡ����ʦ�㷨����ľ���*/
	vector<vector<int>> matrix;
	/*����*/
	vector<classroom> rooms;

	/*��ʼ������,����subjects��ԭ����������Ҫ��init_matrix���޸�subjects������,�������������ǲ���Ҫ��,���Դ�ֵ�ͺ���*/
	void init_matrix(vector<subject> subjects);
	/*ת��ѧ���еĵ�λ������(���ִ����༶����)Ϊ���蹤����(���ݰ༶����ת��Ϊ��������)*/
	vector<subject> changeSubjects(vector<subject> subjects);
};
