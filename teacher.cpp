#include"teacher.h"



bool teacher::operator==(const teacher & other_one)
{
	return this->getTeacherID() == other_one.getTeacherID();
}

/*教师类的实现方法*/
std::string teacher::getInfo() {
    std::string result;
    result = "教师id: " + std::to_string(this->teacher_id) + " 教师名称: " + this->teacher_name + "\n";
	return result;
}


//todo 输入规范处理
/*设置教师类的学科合适度*/
void teacher::setSuitableIndex(std::vector<subject> subjects) {
    std::cout << "下面将进行" + this->teacher_name + "的学科合适度设置: "<< std::endl;
	/*清除现有的数据*/
	this->subjectSuitableIndex.clear();
	for (auto subject : subjects) {
        std::cout << "请输入" + subject.getName() << "的合适度:";
		int index;
        std::cin >> index;
		this->subjectSuitableIndex.push_back(index);
	};
	/*打印结果*/
	this->printIndex(subjects);
}


/*直接使用向量替换实例中的向量*/
void teacher::setSuitableIndex(int length, std::vector<int> index) {
	if (index.size() != length) {
        std::cerr << "输入的长度有误!\n";
	}else{ this->subjectSuitableIndex = index; }
}

/*打印学科合适度*/
void teacher::printIndex(std::vector<subject> subjects) {
    for (std::vector<subject>::iterator it = subjects.begin(); it != subjects.end(); it++) {
        std::cout << std::setw(10) << it->getName();
	}
    std::cout << std::endl;
	for (int index : this->subjectSuitableIndex) {
        std::cout << std::setw(10) << index;
	}
    std::cout << std::endl;
}

/*获取学科合适度*/
std::vector<int> teacher::getSuitableIndex()const {
    return this->subjectSuitableIndex;
}

int teacher::getWorkload()const
{
	return this->workload;
}

int teacher::getTeacherID()const
{
	return this->teacher_id;
}

std::string teacher::getTeacherName() const
{
	return this->teacher_name;
}
