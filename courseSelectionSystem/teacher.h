#pragma once
#include<vector>
#include<iostream>
#include <iomanip>
#include<string>
#include"subject.h"
using namespace std;

/*��ʦ��*/
class teacher {
public:
	/*���� == �����*/
	bool operator == (const teacher& other_one);
	string getInfo();
	/*���캯��*/
	teacher(string name, int id, int workload):teacher_name(name), teacher_id(id), workload(workload){};
	/*�趨��ʦ��ѧ���ʺ϶�*/
	void setSuitableIndex(vector<subject> subjects);
	void setSuitableIndex(int length, vector<int> index);
	/*��ӡѧ�ƺ��ʶ�*/
	void printIndex(vector<subject> subjects);
	/*��ȡѧ�ƺ��ʶ�����*/
	vector<int> getSuitableIndex()const;
	/*��ȡ���������ܶ�*/
	int getWorkload() const;
	/*��ȡ��ʦid*/
	int getTeacherID()const;
	/*��ȡ��ʦ����*/
	string getTeacherName()const;
private:
	/*��ʦ����*/
	string teacher_name;
	/*��ʦid*/
	int teacher_id;
	/*��ʦ�����ѧ�Ƶĺ��ʳ̶�*/
	vector<int> subjectSuitableIndex;
	/*������:�ܹ�������������course*/
	int workload;
};