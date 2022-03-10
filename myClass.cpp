#include"myClass.h"

string myClass::getInfo() {
	string result;
	result = "班级id: " + to_string(this->class_id) + " 班级名称: " + this->class_name + "\n";
	return result;
}

bool myClass::operator==(const myClass & other_one)
{
	return this->class_id == other_one.class_id;
}
