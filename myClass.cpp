#include"myClass.h"

std::string myClass::getInfo() {
    std::string result;
    result = "班级id: " + std::to_string(this->class_id) + " 班级名称: " + this->class_name + "\n";
	return result;
}

bool myClass::operator==(const myClass & other_one)
{
	return this->class_id == other_one.class_id;
}

std::string myClass::getClassName(){
    return this->class_name;
}
