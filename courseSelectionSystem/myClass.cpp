#include"myClass.h"

string myClass::getInfo() {
	string result;
	result = "�༶id: " + to_string(this->class_id) + " �༶����: " + this->class_name + "\n";
	return result;
}