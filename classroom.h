#pragma once
#include<string>
using namespace std;

class classroom
{
public:
	/*比较函数的重载*/
	bool operator == (const classroom& other_one);
	/*构造函数*/
	classroom(string name, int capacity) :name(name), capacity(capacity) {};
	classroom() {};
	/*获取名称或者代号*/
	string getName();
	/*获取容量*/
	int getCapacity();
private:
	/*教室的命名, 比如1101之类的,可能会有代表意义,比如说1101代表1教1楼01号教室*/
	string name;
	/* 容量 单位为班,代表同时上课的班级最大数量,大教室能容纳的多*/
	int capacity;
};

