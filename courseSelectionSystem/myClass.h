#pragma once
#include<string>
using namespace std;

/*�༶��*/
class myClass {
public:
	/*��ȡȫ����Ϣ*/
	string getInfo();
	/*���캯��*/
	myClass(int class_id, string name) :class_id(class_id), class_name(name) {};
	bool operator == (const myClass& other_one);
private:
	int class_id;
	string class_name;
};