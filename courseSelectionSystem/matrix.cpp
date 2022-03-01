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
	/*row����ʦ���*/
	int row = new_one.x;
	if (this->info.empty()) {
		this->info.push_back(new_one);
		++this->workload[row];
		/*cout << "��ʼ��" << row << " " << new_one.y <<" : "<<new_one.value<< endl;*/
		return;
	}
	if (info.size() == this->size && new_one.value > this->get_max_one().value) {
		/*cout << "����" << endl;*/
		return;
	}
	/*����ʦ��������û��,�ܹ�����*/
	if (workload[row] <= 0) {
		/*�������ʦ�����պ�����,��Ҫ��֤new_one�Ƿ���ʺ�*/
		/*������֤����С�ڽ�����к��ʶ����ֵ,�ж��Ƿ�С�ڽ������ͬһ����ʦ�����ֵ�������ܹ�ȷ������,��һ��ֻ�Ǵ�����֤*/
		if (workload[row] == 0 && new_one.value < this->get_max_one().value) {
			int max = -1;
			int max_index = -1;
			int insert_index = 0;
			/*��ȡinfo��ͬһ����ʦ�������ʶ�*/
			for (int i = this->info.size() - 1; i >= 0; --i) {
				if (this->info[i].x == row && this->info[i].value > max) {
					max_index = i;
					max = this->info[i].value;
				}
			}
			/*��ȡnew_one��info�е�λ��*/
			for (int i = this->info.size() - 1; i >= 0; --i) {
				if (new_one.value >= info[i].value) {
					insert_index = i + 1;
					break;
				}
			}
			if (max > new_one.value) {
				/*ɾ��ͬ��������ֵͬʱ����ֵ�������λ��*/
				this->info.erase(info.begin() + max_index);
				this->info.emplace(this->info.begin() + insert_index);
				return;
			}
		}
		else {
			/*����Ҫ�����Ƿ�ʹ�ý��տγ̵���ʦ�޷�ʤ��*/
			for (int i = 0; i < this->info.size();++i) {
				if (this->info[i].value > new_one.value) {
					/*���ͬһ���Ѿ���һ����,������ֵ��ͬ�е����ֵ����*/
					for (int same_col = 0; same_col < this->info.size(); ++same_col) {
						/*�ҵ���ͬһ�е�*/
						if (this->info[same_col].y == new_one.y) {
							/*�����ֱ���ֵ��,�Ͳ���*/
							if (this->info[same_col].value > new_one.value) {
								--workload[this->info[same_col].x];
								this->info.erase(this->info.begin() + same_col);
								break;
							}
							/*�����ֱ���ֵС,��ֱ������*/
							else {
								return;
							}
							
						}
						/*û��ͬ�е�����,��ǰ��same_colָ��info�е����һ��*/
						else if (same_col == this->info.size() - 1) {
							/*�ж�info�Ƿ�����,����ȷ����ֱ�Ӳ���,û��ͬ������*/
							if (this->info.size() == this->size) {
								--workload[this->info.back().x];
								this->info.pop_back();
							}
							/*cout << "������" << row << " " << new_one.y << " : " << new_one.value << endl;*/
							break;
						}
					}
					this->info.emplace(this->info.begin() + i, new_one);
					++workload[row];
					return;
				}
				/*���������������û��break,Ҳ����˵�������û�б�new_one.valueС��,����Ҫ����һ��������ǽ������û��*/
				else if (i == this->info.size() - 1 && this->info.size() < this->size) {
					for (auto i : this->info) {
						if (i.y == new_one.y) {
							return;
						}
					}
					this->info.push_back(new_one);
					/*cout << "����ʱ������" << row << " " << new_one.y << " : " << new_one.value << endl;*/
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
