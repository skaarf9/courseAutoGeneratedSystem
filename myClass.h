#pragma once
#include<string>
using namespace std;

/*班级类*/
class myClass {
public:
	/*获取全部信息*/
	string getInfo();
	/*构造函数*/
	myClass(int class_id, string name) :class_id(class_id), class_name(name) {};
	bool operator == (const myClass& other_one);
private:
	int class_id;
	string class_name;
};