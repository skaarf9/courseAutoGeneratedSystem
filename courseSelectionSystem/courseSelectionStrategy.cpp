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


void courseSelectTeacherStrategy::courseSelectT()
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
	/*��һ��,Ϊ�γ����ʱ�������*/
	/*����course,���䰴��ѧ�ƵĹ�����(�༶����)�Ӵ�С����*/
	sort(&courses[0], &courses[0] + courses.size());
	for (vector<course>::iterator it = courses.begin(); it != courses.end(); ++it) {
		classroom selected_classroom;
		/*��ʼ��: ��ʼΪ��һ�ܵ�һ�ڿε�ʱ��,Ҳ��������Ϊ������,ֻҪ������������еĿγ̾ͺ�*/
		int start_week = 1;
		/*������,�ɿ�ʼ����ѧ�ƿ�ʱ�ټ�ÿ�ܿ�ʱ�����������,����ȡ��*/
		int end_week = (it->getSubject().getDuration()-1) / it->getSubject().getWeeklyLessonNum() + start_week;
		/*��ѡ��ÿ�ܿγ�ʱ��,�Ǹ�����,��ѧ��ÿ�ܿγ�Ϊ2ʱ,��������Ҫ����ÿ�ܿγ�ʱ��*/
		vector<WeeklyLesson> weeklyLessons = vector<WeeklyLesson>(it->getSubject().getWeeklyLessonNum(), WeeklyLesson());
		/*��ѡ��ʱ�������*/
		classroomAndTime room_time_selected;
		bool isCompleted = false;
		for (WeeklyLesson weeklyTimeIndex = WeeklyLesson::firstLesson(); end_week <= 20; ++weeklyTimeIndex) {
			for (int classroomIndex = 0; classroomIndex < rooms.size(); ++classroomIndex) {
				if (it != courses.begin()) {
					weeklyLessons[0] = weeklyTimeIndex;
					room_time_selected.setClassroom(rooms[classroomIndex]);
					room_time_selected.setTime(myTime(start_week, end_week, weeklyLessons));
					it->set_room_time(room_time_selected);
					vector<course>::iterator temp = it;
					bool isBreaked = false;
					do {
						--temp;
						if (temp->isConflict(*it, 0)) {
							isBreaked = true;
							break;
						}
					} while (temp != courses.begin());
					/*����г�ͻ��continue,����һ��classroom*/
					if (isBreaked) {
						continue;
					}
					else {
						/*�жϵڶ��ڿ��Ƿ����ɹ�*/
						bool the_second_lesson_isCompleted = false;
						/*���ÿ����Ҫ���ڿγ�*/
						if (it->getSubject().getWeeklyLessonNum() == 2) {
							for (WeeklyLesson weeklyTimeIndex = WeeklyLesson::middleLesson(); !(weeklyTimeIndex == WeeklyLesson::lastLesson()); ++weeklyTimeIndex) {
								if (it != courses.begin()) {
									weeklyLessons[1] = weeklyTimeIndex;
									room_time_selected.setClassroom(rooms[classroomIndex]);
									room_time_selected.setTime(myTime(start_week, end_week, weeklyLessons));
									it->set_room_time(room_time_selected);
									vector<course>::iterator temp = it;
									do {
										--temp;
										if (temp->isConflict(*it, 1)) {
											continue;
										}
									} while (temp != courses.begin());
									if(temp == courses.begin()) {
										the_second_lesson_isCompleted = true;
										break;
									}
								}
								else {
									weeklyLessons[1] = weeklyTimeIndex;
									room_time_selected.setClassroom(rooms[classroomIndex]);
									room_time_selected.setTime(myTime(start_week, end_week, weeklyLessons));
									it->set_room_time(room_time_selected);
									the_second_lesson_isCompleted = true;
									break;
								}
							}
						}
						else {
							the_second_lesson_isCompleted = true;
						}
						if (the_second_lesson_isCompleted) {
							isCompleted = true;
							break;
						}
					}
				}
				else {
					weeklyLessons[0] = weeklyTimeIndex;
					weeklyLessons[1] = WeeklyLesson::middleLesson();
					room_time_selected.setClassroom(rooms[classroomIndex]);
					room_time_selected.setTime(myTime(start_week, end_week, weeklyLessons));
					it->set_room_time(room_time_selected);
					isCompleted = true;
					break;
				}
			}
			if (isCompleted) {
				break;
			}
			/*��������������һ�ڿ���ԭindex����ʼ,������һ�ܵ��ж�*/
			if (weeklyTimeIndex == WeeklyLesson::lastLesson()) {
				weeklyTimeIndex == WeeklyLesson::firstLesson();
				++end_week;
				++start_week;
			}
		}
		if (!isCompleted) {
			cout << "û����ɲ���" << endl;
		}
		else
		{
			cout << it->getInfo() << endl;
		}
	}
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
	/*��ӡһ�¾���*/
#ifdef Test
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
						cout << "���ε�";
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
