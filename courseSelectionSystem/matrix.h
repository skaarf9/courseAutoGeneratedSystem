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
	/*获取向量中最小的那个元素*/
	matrix get_min_one();
	/*获取向量中最大的那个元素*/
	matrix get_max_one();
	/*在不超过上限的情况下插入元素*/
	void insert_one(matrix new_one);
	matrixArray(int size, vector<int> workload):size(size), workload(workload){
		this->info.reserve(size);
	}
	/*获取info*/
	vector<matrix> getInfo();
private:
	/*储存选择结果的向量*/
	vector<matrix> info;
	/*限制向量大小,值与超额工作量相同*/
	int size;
	/*超额工作量, 为负时表示还能接受的工作量*/
	vector<int> workload;
};