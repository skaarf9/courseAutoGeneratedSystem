#include "courseSelectionStrategy.h"

/* �������Դ��� */
#define Test

/*��ѡ�����ʦ�ı��(���ھ�����)*/
constexpr int MAX_SELECTED = -11;
/*ÿ�����Ŀ�ʱ��,�����Ϊ28���������������*/
constexpr int MAX_LESSONS = 20;

/*�ж��������Ƿ���instance*/
template<typename T>
bool in_vector(vector<T> vector, T instance) {
	bool result = false;
	for (T vector_item : vector) {
		if (vector_item == instance) {
			result = true;
			break;
		}
	}
	return result;
}

template<typename T>
bool intersect_vector(vector<T> A, vector<T> B) {
	for (T vector_item : A) {
		if (in_vector(B, vector_item)) {
			return true;
		}
	}
	return false;
}

/*����һ�������㷨*/
/*�������´�ӡ��������,̫����,����*/
//void cout_all_possibilities(int x, int y, string result) {
//	if (y == 0) {
//		cout <<result<< endl;
//		return;
//	}
//	for (int _x = 0; _x < x; ++_x) {
//		cout_all_possibilities(x, y - 1, result + to_string(_x));
//	}
//}
//void Brute(vector<vector<int>> matrix) {
//	vector<int> min_result;
//	/*�е�����*/
//	const int col = matrix[0].size();
//	/*�е�����*/
//	const int row = matrix.size();
//	string result;
//	cout_all_possibilities(row, col, result);
//	
//}



/*������ĵ�colNum�еķ������н���, �������� ΪchangeRow*/
void change_col(int colNum, int changeRow, vector<vector<int>>& matrix) {
	cout << "ת�Ƶ�" << colNum << "��,ת����Ϊ" << changeRow << endl;
	for (int i = 0; i < matrix.size(); ++i) {
		if (i == changeRow) {
			continue;
		}
		if (matrix[i][colNum] == MAX_SELECTED) {
			matrix[i][colNum] = -matrix[changeRow][colNum];
			continue;
		}
		matrix[i][colNum] -= matrix[changeRow][colNum];
	}
	matrix[changeRow][colNum] = MAX_SELECTED;
}


void courseSelectTeacherStrategy::courseSelectTeacherAndClass()
{
	/*��ʼ������,����ѡȡÿ���γ̵���ʦ*/
	this->init_matrix(this->changeSubjects(subjects));
	//Brute(matrix);
	/*��֤һ��subjectsû�б��ı�*/
	/*for (auto subject : subjects) {
		cout << subject.getWorkload() << endl;
	}*/
	/*for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		cout << endl;
	}*/
	/*���ݾ���ó���ѡȡ����ʦ, ������Ҫ����course����������Ӱ༶��Ϣ*/
	courses.clear();
	int teacher_index = 0;
	int col = 0;
	vector<myClass>::iterator class_iterator = classes.begin();
	for (vector<subject>::iterator it = subjects.begin(); it != subjects.end();) {
		vector<myClass> myClassTemp;
		vector<subject>::iterator result = it;
		for (int i = 0; i < it->getWorkload(); ++i) {
			myClassTemp.push_back(*class_iterator);
			++class_iterator;
			if (class_iterator == classes.end()) {
				class_iterator = classes.begin();
				++it;
				break;
			}
		}
		/*����matrix��ȡteacher_index,Ҳ����-11��row*/
		for (int i = 0; i < matrix.size(); ++i) {
			if (matrix[i][col] == -11) {
				teacher_index = i;
				break;
			}
		}
		++col;
		course course_instance = course(teachers[teacher_index], *result, myClassTemp);
		courses.push_back(course_instance);
	}
#ifdef Test
	cout << "��ɽ�ʦ��༶��Ϣ�����" << endl;
#endif
}

void courseSelectTeacherStrategy::courseSelectClassroomAndTime()
{
	/*��һ��,Ϊ�γ����ʱ�������*/
	bool complete_all = false;
	/*����course,���䰴��ѧ�ƵĹ�����(�༶����)�Ӵ�С����(������<����)*/
	sort(&courses[0], &courses[0] + courses.size());
	int start_index = 1;
	while (!complete_all) {

		//���forѭ�������ҵ���ʼ�Ľ��Һ�ʱ��
		vector<course>::iterator it = courses.begin();
		for (; it != courses.end(); ++it) {
			//����γ��Ѿ������˰༶��ʱ��������(δ������õĻ��ں�������Ϊ��)
			if (!it->getClassroomAndTime().isEmpty())continue;
			/*��ʼ��: ��ʼΪ��һ�ܵ�һ�ڿε�ʱ��,Ҳ��������Ϊ������,ֻҪ������������еĿγ̾ͺ�*/
			int start_week = start_index;
			/*������,�ɿ�ʼ����ѧ�ƿ�ʱ�ټ�ÿ�ܿ�ʱ�����������,����ȡ��*/
			int end_week = (it->getSubject().getDuration() - 1) / it->getSubject().getWeeklyLessonNum() + start_week;
			/*�������ƴ�С*/
			int room_size_limit = it->getClasses().size();
			for (; end_week <= 20; ++start_week) {
				bool complete = false;
				for (WeeklyLesson weeklyTime = WeeklyLesson::firstLesson(); weeklyTime <= WeeklyLesson::lastLesson(); ++weeklyTime) {
					vector<classroom>::iterator room_it = this->rooms.begin();
					for (; room_it != this->rooms.end(); ++room_it) {
						bool changeTime = false;
						//�������̫С������
						//�����������Զ�����ҹ���
						if (room_it->getCapacity() < room_size_limit)continue;
						vector<course>::iterator course_it = courses.begin();
						for (; course_it != courses.end(); ++course_it) {
							//����ÿγ�û�����ý��Һ�ʱ��������
							if (course_it->getClassroomAndTime().isEmpty())continue;
							//ʱ������ҳ�ͻ
							if (course_it->getClassroomAndTime().isConflict(
								{
									*room_it,
									myTime(static_cast<unsigned short>(start_week),
										static_cast<unsigned short>(end_week),
										vector<WeeklyLesson>())
								}, weeklyTime))
							{
								//������б�ķ��������Ľ���
								bool changeClassroom = false;
								vector<classroom>::iterator temp_it = room_it + 1;
								for (; temp_it != this->rooms.end(); ++temp_it) {
									if (temp_it->getCapacity() >= room_size_limit) {
										//������
										room_it = temp_it - 1;
										changeClassroom = true;
										break;
									}
								}
								if (changeClassroom) {
									break;
								}
								//ִ�е�����˵��û�к��ʵĽ�����
								//��ʱ��
								changeTime = true;
								break;
							}
							//ͬһʱ����ʦ��ѧ����ͻ
							else if (course_it->getClassroomAndTime().getTime().isConflict(myTime(static_cast<unsigned short>(start_week),
								static_cast<unsigned short>(end_week),
								vector<WeeklyLesson>()), weeklyTime) && (course_it->getTeacher() == it->getTeacher() || intersect_vector<myClass>(course_it->getClasses(), it->getClasses()))) {
								//��ʱ��
								changeTime = true;
								break;
							}
						}
						if (changeTime) {
							break;
						}
						if (course_it == courses.end()) {
							myTime temp = myTime(static_cast<unsigned short>(start_week),
								static_cast<unsigned short>(end_week), vector<WeeklyLesson>());
							temp.addWeeklyLessons(weeklyTime);
							//�������������courses�ĸ���
							it->set_room_time({ *room_it, temp });
							complete = true;
							break;
						}
					}
					if (complete) {
						break;
					}
				}
				if (complete) {
					break;
				}
				++end_week;
			}
			if (end_week == 21) {
				cout << "�޷�������Һ�ʱ��" << endl;
				system("pause");
				exit(-1);
			}
		}
		//�����һ��ѡ��ʱ��,���ÿ�����ڵĻ�����Ҫ����һ��ʱ��͹���
		//����,��һ��ѡ������ͬʱռ��ÿ������Ϊ����д��(��һ���ǽ�ÿ��ʱ���ĳ������ռ��,�ᵼ�µ���������Դ����,�Ӷ�Ӱ��ý��Һ���ͬһ�γ̵İ���),��������ڶ����Ҳ������ʵ�ʱ��,��ôֻ�����Ǳ�����ҾͲ�����
		//���ڵڶ���ѡʱ���ǲ���Ҫ�������һ����ܵ�,����ֻ������¯��,�������뻹�ǿ��Բο���
		bool done = false;
		while (!done) {
			//������ѭ����key
			//�����һ�α���������������complete_all��Ȼ��true,����������ѭ��
			complete_all = true;
			done = true;
			it = courses.begin();
			for (; it != courses.end(); ++it) {
				if (it->getClassroomAndTime().isEmpty()) {
					complete_all = false;
					continue;
				}
				unsigned short start_week = it->getClassroomAndTime().getTime().getStartWeek();
				unsigned short end_week = it->getClassroomAndTime().getTime().getEndWeek();
				//��������ÿγ�������ÿ�ܿ�ʱ,�����
				if (it->getClassroomAndTime().getTime().getWeeklyLessons().size() < it->getSubject().getWeeklyLessonNum()) {
					//ֻҪ��һ����û���,��false;
					complete_all = false;
					//�������еĽ���Ѱ�Һ��ʵ�ʱ��
					for (WeeklyLesson weeklyTime = WeeklyLesson::firstLesson(); weeklyTime <= WeeklyLesson::lastLesson(); ++weeklyTime) {
						vector<course>::iterator it_temp = courses.begin();
						for (; it_temp < courses.end(); ++it_temp) {
							if (it_temp->getClassroomAndTime().getTime().isConflict(myTime(static_cast<unsigned short>(start_week),
								static_cast<unsigned short>(end_week),
								vector<WeeklyLesson>()), weeklyTime) && (it_temp->getTeacher() == it->getTeacher() || intersect_vector<myClass>(it_temp->getClasses(), it->getClasses()))) {
								//������������һ����,��֤������޷���ɲ���
								if (weeklyTime == WeeklyLesson::lastLesson()) {
									//ɾ����ǰ�Ѿ����������
									it->set_room_time(classroomAndTime());
								}
								break;
							}
						}
						if (it_temp == courses.end()) {
							//������Ҫ��,��Ϊ���Ҫ����ѭ���Ļ�����ҪcompleteCourse�����ݱ�������
							it->addClassTimeWeekly(weeklyTime);
							//���������Ҫ��ӵľ�����Ϊfalse,��ѭ������,֪��һ��ѭ������������Ҫ��ӵĻ��߲�����ӵ�Ϊֹ
							done = false;
							break;
						}
					}
				}
			}
		}
		++start_index;
	}
#ifdef Test
	for (course c : courses) {
		cout << c.getInfo();
	}
#endif
}

void courseSelectTeacherStrategy::init_matrix(vector<subject> subjects)
{
	this->matrix.clear();
	/*�����еĽ�ʦѧ�ƺ��ʶȼ������*/
	for (teacher t:this->teachers){
		this->matrix.push_back(t.getSuitableIndex());
	}
	/*����ѧ�Ƶ����ư༶���ھ�������ѧ����, �����ճ�����, course�ǰ���ѧ�ƽ��������, ��Ϊ����course,�༶��ͬ,��ʦ��ͬ,����subject��ͬ,��ô,����courseӦ����ѡ���������ڵ�,����֮��ѡ�������˳��ѡ���,����������Ҫ˳��������ͬsubject��course*/
	vector<subject>::iterator it = subjects.begin();
	int index = 0;
	for (int i = 0; it != subjects.end(); ++i, it++) {
		/*cout << it->getWorkload() << endl;*/
		while (it->getWorkload() > 1) {
			/*for (vector<vector<int>>::iterator it = matrix.begin(); it != matrix.end(); it++) {
				it->push_back((*it)[i]);
			}
			it->setWorkload(it->getWorkload() - 1);*/
			for (int row = 0; row < matrix.size(); ++row) {
				matrix[row].emplace(matrix[row].begin() + i + index, matrix[row][i + index]);
			}
			++index;
			it->setWorkload(it->getWorkload() - 1);
		}
	}
#ifdef Test
	/*��ӡһ�¾���*/
	cout << "��ʼ��ʦ���ʶ�" << endl;
	index = 0;
	cout << setw(5) << "��ʦ����";
	for (int index : matrix[0]) {
		cout << setw(5) << "ѧ��";
	}
	cout << setw(5) << "��ʦ������" << endl;
	for (vector<int> row : matrix) {
		cout << setw(5) << this->teachers[index].getTeacherName();
		for (int col : row) {
			cout << setw(5) << col;
		}
		cout << setw(5) << this->teachers[index].getWorkload();
		++index;
		cout << endl;
	}
#endif
/*��һ��,׼������,̰��ѡ�����ŵĻ��ַ�ʽʹ�ú��ʶ��ܺ����,�����ǽ�ʦ���ܳ��ܵĹ�����*/
	/*�е�����*/
	const int col = matrix[0].size();
	/*�е�����*/
	const int row = matrix.size();
	vector<int> current_workload = vector<int>(row, 0);
	for (int i = 0; i < col; ++i) {
		int max = matrix[0][i];
		int maxIndex = 0;
		for (int j = 1; j < row; ++j) {
			if (matrix[j][i] > max) {
				max = matrix[j][i];
				maxIndex = j;
			}
		}
		/*
		�ҵ�ÿ���е����ֵ��,����������ת��Ϊ�����ֵ֮��Ĳ��,���ֵ���ΪMAX_SELECTED,�����ж�����ֵʱ��������,������ǰÿ����ʦ�Ĺ���������������
		*/
		/*cout << "���ֵΪmatrix["<< maxIndex <<"]["<<i<<"]: " <<max<<endl;*/
		for (int j = 0; j < row; ++j) {
			if (j != maxIndex) {
				matrix[j][i] = max - matrix[j][i];
			}
			else {
				current_workload[j] += 1;
				matrix[j][i] = MAX_SELECTED;
			}
		}
	}
	
#ifdef Test
	int sum = 0;
	for (int i = 0; i < row; ++i) {
		sum += current_workload[i];
	}
	cout << "�ܹ���Ҫ" << sum << "���γ�" << endl;
#endif
/*�ڶ���,���ݽ�ʦ�Ĺ������Բ�����֮������ת��*/
	/*��current_workload�е�����ת��Ϊ��ֵ,ͬʱ��֤��ʦ�Ĺ������������蹤����*/
	int teachers_workload_sum = 0;
	for (int i = 0; i < row; ++i) {
		current_workload[i] = current_workload[i] - this->teachers[i].getWorkload();
		teachers_workload_sum += current_workload[i];
	}
	if (teachers_workload_sum > 0) {
		cout << "��ʦ�ܹ����ܵĹ�����������֧�Ž�ѧ����" << endl;
		system("pause");
		exit(0);
	}
	/*��ӡһ�¾���*/
#ifdef Test
	int i = -1;
	cout << "��һ���Ż���" << endl;
	for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		/*cout << " -1������: "<< current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " <<this->teachers[i].getWorkload() <<endl;*/
		cout << " ���Ĺ�����: " << current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " << this->teachers[i].getWorkload() << endl;
	}
#endif
	/*���Ż����а�����Ҫ��������С��������,��ʦ����Ҫ����������������ѡ)*/
	//vector<int> searching_sequence;
	//for (int sequence = 0; sequence < current_workload.size(); ++sequence) {
	//	/*����ʦ����������*/
	//	if (current_workload[sequence] > 0) {
	//		/*�������л�Ϊ��*/
	//		if (searching_sequence.empty()) {
	//			searching_sequence.push_back(sequence);
	//		}
	//		else {
	//			/*������������,���Ҵ�������ʦ��λ��*/
	//			for (vector<int>::iterator it = searching_sequence.begin(); it != searching_sequence.end(); ++it) {
	//				if (current_workload[*it] > current_workload[sequence]) {
	//					searching_sequence.emplace(it, sequence);
	//					break;
	//				}
	//				if (it == searching_sequence.end()) {
	//					searching_sequence.push_back(sequence);
	//					break;
	//				}
	//			}
	//		}
	//	}
	//}
	//if (searching_sequence.empty()) {
	//	cout << "��ǰ��Ϊ���ŷ���" << endl;
	//	return;
	//}
	//for (int i : searching_sequence) {
	for (int i = 0; i < row; ++i) {
		if (current_workload[i] > 0) {
			/*cout << "Ѱ�ҵ�" << i << "����ʦ��ת������" << endl;*/
			//���������ڳ�����
			/*matrixArray received_array = matrixArray(current_workload[i], current_workload);*/

			/*���һ����ѡ����,�ڽ�������ѡ�������ø���*/
			vector<int> selected_cols = vector<int>(current_workload[i], -1);
			/*ÿ�����⴫��һ������,�ܹ���Ҫ�Ĵ���Ϊcurrent_workload[i]��,������ʦ����������*/
			while (0 < current_workload[i]) {
				/*�ҵ���ѡ��Χ�ڶ��ܺ�Ӱ����С��*/
				int min = INT32_MAX;
				int min_row = -1;
				int min_col = -1;
				/*jΪ����*/
				/*��������ʦ��ÿһ��*/
				for (int j = 0; j < col; ++j) {
					/*��ǰ��Ϊԭ����ѡ����,��ô��ѡ����Ҳ�϶�������һ��,����j����Ҫ*/
					if (matrix[i][j] == MAX_SELECTED) {
						for (int n = 0; n < row; ++n) {
							/*
							��һ������:��ѡ��ʦ���ܳе�����;
							�ڶ�������:��ѡ�����ȵ�ǰ����(min)����
							����������:��ѡ����֮ǰû��ѡ���ͬһ�еķ���,(����Ѿ�ѡ�����е�,��ô��һ���Զ�ȫ������)
							*/
							if (current_workload[n] < 0 && matrix[n][j] < min && !in_vector(selected_cols, j)) {
								min = matrix[n][j];
								min_row = n;
								min_col = j;
								/*received_array.insert_one({ n, j, matrix[n][j] });*/
							}
						}
					}
				}
				//cout << "�ҵ�����С�ķ��ϵ�ֵ: " << min << "λ����[" << min_row << "][" << min_col << "]" << endl;
				selected_cols[current_workload[i] - 1] = min_col;
				++current_workload[min_row];
				--current_workload[i];
				change_col(min_col, min_row, matrix);
			}

			/*cout << "-----------------------" << endl;
			cout << "�����ǵ�" << i << "��:"<<endl;
			for (auto instance : received_array.getInfo()) {
				cout << "��Ҫ�滻" << instance.x << "," << instance.y << "λ��" << endl;
			}*/
		}
	}
	i = -1;
	cout << "�ڶ����Ż���" << endl;
	for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		/*cout << " -1������: "<< current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " <<this->teachers[i].getWorkload() <<endl;*/
		cout << " ���Ĺ�����: " << current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " << this->teachers[i].getWorkload() << endl;
	}
/*�����Ż�*/
	bool flag;
	do {
		flag = false;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				/*�����ǰ����(matrix[i][j])Ϊ����(���Գ����Ż�)���Ҳ�����ѡ����, matrix[i][j]Ϊ��ѡ����*/
				if (matrix[i][j] < 0 && matrix[i][j] != MAX_SELECTED) {
					/*�ҵ���һ�е���ѡ����*/
					int selected_row = 0;
					for (; selected_row < row; ++selected_row) {
						if (matrix[selected_row][j] == MAX_SELECTED) {
							break;
						}
					}
					/*���ʱ��selected_row�Ѿ��ǵ�ǰ����ѡ��*/
					if (current_workload[i] < 0) {
						//��ѡ�����ܹ�ֱ��ת��,����Ҫ��������
						change_col(i, j, matrix);
						++current_workload[selected_row];
						--current_workload[i];
						flag = true;
						break;
					}
					/*�����ҵ��滻�����е���Сֵ*/
					int min_changeable = INT32_MAX;
					int min_changeable_col = 0;
					for (int m = 0; m < col; ++m) {
						if (matrix[i][m] == MAX_SELECTED) {
							if (matrix[selected_row][m] < min_changeable) {
								min_changeable = matrix[selected_row][m];
								min_changeable_col = m;
							}
						}
					}
					/*�ȽϽ����ķ����Ƿ�ʹ����ϸ��Ӻ���*/
					if (-matrix[i][j] > min_changeable) {
						change_col(j, i, matrix);
						change_col(min_changeable_col, selected_row, matrix);
						flag = true;
					}
				}
			}
		}
	} while (flag);
	//i = -1;
	//for (vector<int> row : matrix) {
	//	for (int col : row) {
	//		cout << setw(5) << col;
	//	}
	//	/*cout << " -1������: "<< current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " <<this->teachers[i].getWorkload() <<endl;*/
	//	cout << " ���Ĺ�����: " << current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " << this->teachers[i].getWorkload() << endl;
	//}
/*���*/
	/*������ѡ����ʦ*/


	///*��ӡһ�¾���*/
#ifdef Test
	i = -1;
	cout << "�������Ż���" << endl;
	for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		/*cout << " -1������: "<< current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " <<this->teachers[i].getWorkload() <<endl;*/
		cout << " ���Ĺ�����: "<< current_workload[++i] << " ��ʦ���ܳ��ܵĹ�����: " <<this->teachers[i].getWorkload() <<endl;
	}
#endif
}

/* �����޸�ԭ�е�subject,���ص������Ǹ��޸ĺ�ĸ��� */
/* ������ */
vector<subject> courseSelectTeacherStrategy::changeSubjects(vector<subject> subjects)
{
	int classNum = this->classes.size();
	for (vector<subject>::iterator it = subjects.begin(); it != subjects.end(); it++) {
		/*����ȡ��*/
		/*cout << classNum << " : " << it->getWorkload()<<endl;*/
		it->setWorkload((classNum - 1) / it->getWorkload() + 1);
	}
	/*��ӡһ��*/
	/*cout << "������:" << endl;
	for (auto subject: subjects) {
		cout << subject.getName() << " : "<< subject.getWorkload() << endl;
	}*/
	return subjects;
}
