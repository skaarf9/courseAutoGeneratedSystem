#pragma once
#include<string>
using namespace std;

class classroom
{
public:
	/*�ȽϺ���������*/
	bool operator == (const classroom& other_one);
	/*���캯��*/
	classroom(string name, int capacity) :name(name), capacity(capacity) {};
	classroom() {};
	/*��ȡ���ƻ��ߴ���*/
	string getName();
	/*��ȡ����*/
	int getCapacity();
private:
	/*���ҵ�����, ����1101֮���,���ܻ��д�������,����˵1101����1��1¥01�Ž���*/
	string name;
	/* ���� ��λΪ��,����ͬʱ�Ͽεİ༶�������,����������ɵĶ�*/
	int capacity;
};

