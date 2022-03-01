#include"myClass.h"

string myClass::getInfo() {
	string result;
	result = "°à¼¶id: " + to_string(this->class_id) + " °à¼¶Ãû³Æ: " + this->class_name + "\n";
	return result;
}