#include"teacher.h"



bool teacher::operator==(const teacher & other_one)
{
	return this->getTeacherID() == other_one.getTeacherID();
}

/*��ʦ���ʵ�ַ���*/
string teacher::getInfo() {
	string result;
	result = "��ʦid: " + to_string(this->teacher_id) + " ��ʦ����: " + this->teacher_name + "\n";
	return result;
}


//todo ����淶����
/*���ý�ʦ���ѧ�ƺ��ʶ�*/
void teacher::setSuitableIndex(vector<subject> subjects) {
	cout << "���潫����" + this->teacher_name + "��ѧ�ƺ��ʶ�����: "<< endl;
	/*������е�����*/
	this->subjectSuitableIndex.clear();
	for (auto subject : subjects) {
		cout << "������" + subject.getName() << "�ĺ��ʶ�:";
		int index;
		cin >> index;
		this->subjectSuitableIndex.push_back(index);
	};
	/*��ӡ���*/
	this->printIndex(subjects);
}


/*ֱ��ʹ�������滻ʵ���е�����*/
void teacher::setSuitableIndex(int length, vector<int> index) {
	if (index.size() != length) {
		cerr << "����ĳ�������!\n";
	}else{ this->subjectSuitableIndex = index; }
}

/*��ӡѧ�ƺ��ʶ�*/
void teacher::printIndex(vector<subject> subjects) {
	for (vector<subject>::iterator it = subjects.begin(); it != subjects.end(); it++) {
		cout << setw(10) << it->getName();
	}
	cout << endl;
	for (int index : this->subjectSuitableIndex) {
		cout << setw(10) << index;
	}
	cout << endl;
}

/*��ȡѧ�ƺ��ʶ�*/
vector<int> teacher::getSuitableIndex()const {
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

string teacher::getTeacherName() const
{
	return this->teacher_name;
}
