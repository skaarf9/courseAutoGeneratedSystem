#include"myClass.h"

string myClass::getInfo() {
	string result;
	result = "°à¼¶id: " + to_string(this->class_id) + " °à¼¶Ãû³Æ: " + this->class_name + "\n";
	return result;
}

bool myClass::operator==(const myClass & other_one)
{
	return this->class_id == other_one.class_id;
}
