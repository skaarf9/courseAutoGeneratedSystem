#pragma once
#include<map>
#include<vector>
using namespace std;

struct matrix
{
	int x;
	int y;
	int value;
};

class matrixArray{
public:
	/*��ȡ��������С���Ǹ�Ԫ��*/
	matrix get_min_one();
	/*��ȡ�����������Ǹ�Ԫ��*/
	matrix get_max_one();
	/*�ڲ��������޵�����²���Ԫ��*/
	void insert_one(matrix new_one);
	matrixArray(int size, vector<int> workload):size(size), workload(workload){
		this->info.reserve(size);
	}
	/*��ȡinfo*/
	vector<matrix> getInfo();
private:
	/*����ѡ����������*/
	vector<matrix> info;
	/*����������С,ֵ�볬�������ͬ*/
	int size;
	/*�������, Ϊ��ʱ��ʾ���ܽ��ܵĹ�����*/
	vector<int> workload;
};