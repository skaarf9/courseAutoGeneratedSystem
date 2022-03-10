#include "matrix.h"
#include<iostream>
using namespace std;

matrix matrixArray::get_min_one()
{
	return this->info.front();
}

matrix matrixArray::get_max_one()
{
	return this->info.back();
}

void matrixArray::insert_one(matrix new_one)
{
	/*row即老师序号*/
	int row = new_one.x;
	if (this->info.empty()) {
		this->info.push_back(new_one);
		++this->workload[row];
		/*cout << "初始化" << row << " " << new_one.y <<" : "<<new_one.value<< endl;*/
		return;
	}
	if (info.size() == this->size && new_one.value > this->get_max_one().value) {
		/*cout << "跳过" << endl;*/
		return;
	}
	/*该老师工作量还没满,能够插入*/
	if (workload[row] <= 0) {
		/*如果该老师工作刚好满了,需要验证new_one是否更适合*/
		/*这里验证的是小于结果集中合适度最大值,判断是否小于结果集中同一个老师的最大值才真正能够确定可行,这一步只是粗略验证*/
		if (workload[row] == 0 && new_one.value < this->get_max_one().value) {
			int max = -1;
			int max_index = -1;
			int insert_index = 0;
			/*获取info中同一个老师的最大合适度*/
			for (int i = this->info.size() - 1; i >= 0; --i) {
				if (this->info[i].x == row && this->info[i].value > max) {
					max_index = i;
					max = this->info[i].value;
				}
			}
			/*获取new_one在info中的位置*/
			for (int i = this->info.size() - 1; i >= 0; --i) {
				if (new_one.value >= info[i].value) {
					insert_index = i + 1;
					break;
				}
			}
			if (max > new_one.value) {
				/*删除同组中最大的值同时将新值插入合适位置*/
				this->info.erase(info.begin() + max_index);
				this->info.emplace(this->info.begin() + insert_index);
				return;
			}
		}
		else {
			/*不需要考虑是否使得接收课程的老师无法胜任*/
			for (int i = 0; i < this->info.size();++i) {
				if (this->info[i].value > new_one.value) {
					/*如果同一列已经有一个了,并且新值比同列的这个值更优*/
					for (int same_col = 0; same_col < this->info.size(); ++same_col) {
						/*找到了同一列的*/
						if (this->info[same_col].y == new_one.y) {
							/*该数字比新值大,就插入*/
							if (this->info[same_col].value > new_one.value) {
								--workload[this->info[same_col].x];
								this->info.erase(this->info.begin() + same_col);
								break;
							}
							/*该数字比新值小,就直接抛弃*/
							else {
								return;
							}
							
						}
						/*没有同列的数据,当前的same_col指向info中的最后一个*/
						else if (same_col == this->info.size() - 1) {
							/*判断info是否满了,而且确定能直接插入,没有同列数据*/
							if (this->info.size() == this->size) {
								--workload[this->info.back().x];
								this->info.pop_back();
							}
							/*cout << "插入了" << row << " " << new_one.y << " : " << new_one.value << endl;*/
							break;
						}
					}
					this->info.emplace(this->info.begin() + i, new_one);
					++workload[row];
					return;
				}
				/*如果遍历结束还是没有break,也就是说结果集中没有比new_one.value小的,还需要考虑一种情况就是结果集还没满*/
				else if (i == this->info.size() - 1 && this->info.size() < this->size) {
					for (auto i : this->info) {
						if (i.y == new_one.y) {
							return;
						}
					}
					this->info.push_back(new_one);
					/*cout << "不足时插入了" << row << " " << new_one.y << " : " << new_one.value << endl;*/
					break;
				}
			}
		}
	}
	return;
}

vector<matrix> matrixArray::getInfo()
{
	return this->info;
}
