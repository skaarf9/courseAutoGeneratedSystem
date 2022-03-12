#include "classroom.h"

bool classroom::operator==(const classroom& other_one)
{

	return this->name == other_one.name;
}

std::string classroom::getName()
{
	return this->name;
}

int classroom::getCapacity()
{
	return this->capacity;
}
