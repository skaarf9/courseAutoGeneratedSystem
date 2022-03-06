#include "courseSelectionStrategy.h"

/* 开启测试代码 */
#define Test

/*所选择的老师的标记(用在矩阵中)*/
constexpr int MAX_SELECTED = -11;
/*每周最大的课时数,如果定为28则计算了周六周日*/
constexpr int MAX_LESSONS = 20;

/*判断向量中是否有instance*/
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

/*尝试一下蛮力算法*/
/*测试了下打印所有序列,太慢了,算了*/
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
//	/*列的数量*/
//	const int col = matrix[0].size();
//	/*行的数量*/
//	const int row = matrix.size();
//	string result;
//	cout_all_possibilities(row, col, result);
//	
//}



/*将矩阵的第colNum列的方案进行交换, 待交换行 为changeRow*/
void change_col(int colNum, int changeRow, vector<vector<int>>& matrix) {
	cout << "转移第" << colNum << "列,转移行为" << changeRow << endl;
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
	/*初始化矩阵,用于选取每个课程的老师*/
	this->init_matrix(this->changeSubjects(subjects));
	//Brute(matrix);
	/*验证一下subjects没有被改变*/
	/*for (auto subject : subjects) {
		cout << subject.getWorkload() << endl;
	}*/
	/*for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		cout << endl;
	}*/
	/*根据矩阵得出了选取的老师, 现在需要生成course向量集并添加班级信息*/
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
		/*根据matrix获取teacher_index,也就是-11的row*/
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
	cout << "完成教师与班级信息的添加" << endl;
#endif
}

void courseSelectTeacherStrategy::courseSelectClassroomAndTime()
{
	/*下一步,为课程添加时间与教室*/
	bool complete_all = false;
	/*排序course,让其按照学科的工作量(班级数量)从大到小排序(重载了<符号)*/
	sort(&courses[0], &courses[0] + courses.size());
	int start_index = 1;
	while (!complete_all) {

		//这个for循环用于找到初始的教室和时间
		vector<course>::iterator it = courses.begin();
		for (; it != courses.end(); ++it) {
			//如果课程已经设置了班级和时间则跳过(未完成设置的会在后面重置为空)
			if (!it->getClassroomAndTime().isEmpty())continue;
			/*开始周: 初始为第一周第一节课的时间,也可以设置为其他的,只要最后能容纳所有的课程就好*/
			int start_week = start_index;
			/*结束周,由开始周与学科课时再加每周课时计算出结束周,向上取整*/
			int end_week = (it->getSubject().getDuration() - 1) / it->getSubject().getWeeklyLessonNum() + start_week;
			/*教室限制大小*/
			int room_size_limit = it->getClasses().size();
			for (; end_week <= 20; ++start_week) {
				bool complete = false;
				for (WeeklyLesson weeklyTime = WeeklyLesson::firstLesson(); weeklyTime <= WeeklyLesson::lastLesson(); ++weeklyTime) {
					vector<classroom>::iterator room_it = this->rooms.begin();
					for (; room_it != this->rooms.end(); ++room_it) {
						bool changeTime = false;
						//如果教室太小则跳过
						//这里可以添加自定义教室规则
						if (room_it->getCapacity() < room_size_limit)continue;
						vector<course>::iterator course_it = courses.begin();
						for (; course_it != courses.end(); ++course_it) {
							//如果该课程没有设置教室和时间则跳过
							if (course_it->getClassroomAndTime().isEmpty())continue;
							//时间与教室冲突
							if (course_it->getClassroomAndTime().isConflict(
								{
									*room_it,
									myTime(static_cast<unsigned short>(start_week),
										static_cast<unsigned short>(end_week),
										vector<WeeklyLesson>())
								}, weeklyTime))
							{
								//如果还有别的符合条件的教室
								bool changeClassroom = false;
								vector<classroom>::iterator temp_it = room_it + 1;
								for (; temp_it != this->rooms.end(); ++temp_it) {
									if (temp_it->getCapacity() >= room_size_limit) {
										//换教室
										room_it = temp_it - 1;
										changeClassroom = true;
										break;
									}
								}
								if (changeClassroom) {
									break;
								}
								//执行到这里说明没有合适的教室了
								//换时间
								changeTime = true;
								break;
							}
							//同一时间老师或学生冲突
							else if (course_it->getClassroomAndTime().getTime().isConflict(myTime(static_cast<unsigned short>(start_week),
								static_cast<unsigned short>(end_week),
								vector<WeeklyLesson>()), weeklyTime) && (course_it->getTeacher() == it->getTeacher() || intersect_vector<myClass>(course_it->getClasses(), it->getClasses()))) {
								//换时间
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
							//这里能完成所有courses的更新
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
				cout << "无法分配教室和时间" << endl;
				system("pause");
				exit(-1);
			}
		}
		//完成了一次选课时间,如果每周两节的话还需要再找一个时间就够了
		//另外,第一次选课是以同时占满每个教室为方向写的(另一种是将每个时间的某个教室占满,会导致单个教室资源紧张,从而影响该教室后续同一课程的安排),所以如果第二次找不到合适的时间,那么只可能是本身教室就不够多
		//由于第二次选时间是不需要遍历教室或者周的,所以只能另起炉灶,不过代码还是可以参考的
		bool done = false;
		while (!done) {
			//跳出大循环的key
			//如果在一次遍历后都完成了添加则complete_all仍然是true,将跳出最终循环
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
				//如果已配置课程数不足每周课时,则添加
				if (it->getClassroomAndTime().getTime().getWeeklyLessons().size() < it->getSubject().getWeeklyLessonNum()) {
					//只要有一个还没完成,则false;
					complete_all = false;
					//根据已有的教室寻找合适的时间
					for (WeeklyLesson weeklyTime = WeeklyLesson::firstLesson(); weeklyTime <= WeeklyLesson::lastLesson(); ++weeklyTime) {
						vector<course>::iterator it_temp = courses.begin();
						for (; it_temp < courses.end(); ++it_temp) {
							if (it_temp->getClassroomAndTime().getTime().isConflict(myTime(static_cast<unsigned short>(start_week),
								static_cast<unsigned short>(end_week),
								vector<WeeklyLesson>()), weeklyTime) && (it_temp->getTeacher() == it->getTeacher() || intersect_vector<myClass>(it_temp->getClasses(), it->getClasses()))) {
								//如果遍历到最后一个了,则证明这个无法完成插入
								if (weeklyTime == WeeklyLesson::lastLesson()) {
									//删除先前已经插入的数据
									it->set_room_time(classroomAndTime());
								}
								break;
							}
						}
						if (it_temp == courses.end()) {
							//两个都要加,因为如果要重置循环的话还需要completeCourse的数据保持最新
							it->addClassTimeWeekly(weeklyTime);
							//如果还有需要添加的就设置为false,让循环继续,知道一次循环过后不再有需要添加的或者不能添加的为止
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
	/*将现有的教师学科合适度加入矩阵*/
	for (teacher t:this->teachers){
		this->matrix.push_back(t.getSuitableIndex());
	}
	/*根据学科的限制班级数在矩阵后加上学科列, 根据日常经验, course是按照学科进行排序的, 因为两个course,班级不同,老师不同,但是subject相同,那么,这俩course应该所选教室是相邻的,由于之后选择教室是顺序选择的,所以我们需要顺序排列相同subject的course*/
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
	/*打印一下矩阵*/
	cout << "初始教师合适度" << endl;
	index = 0;
	cout << setw(5) << "教师名称";
	for (int index : matrix[0]) {
		cout << setw(5) << "学科";
	}
	cout << setw(5) << "教师工作量" << endl;
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
/*第一步,准备工作,贪心选择最优的划分方式使得合适度总和最高,不考虑教师所能承受的工作量*/
	/*列的数量*/
	const int col = matrix[0].size();
	/*行的数量*/
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
		找到每列中的最大值后,将其他数据转化为与最大值之间的差距,最大值标记为MAX_SELECTED,以在有多个最大值时进行区分,并将当前每个教师的工作量存入数组中
		*/
		/*cout << "最大值为matrix["<< maxIndex <<"]["<<i<<"]: " <<max<<endl;*/
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
	cout << "总共需要" << sum << "个课程" << endl;
#endif
/*第二步,根据教师的工作量对不合理之处进行转移*/
	/*将current_workload中的数字转化为差值,同时验证教师的工作量大于所需工作量*/
	int teachers_workload_sum = 0;
	for (int i = 0; i < row; ++i) {
		current_workload[i] = current_workload[i] - this->teachers[i].getWorkload();
		teachers_workload_sum += current_workload[i];
	}
	if (teachers_workload_sum > 0) {
		cout << "教师能够承受的工作量不足以支撑教学任务" << endl;
		system("pause");
		exit(0);
	}
	/*打印一下矩阵*/
#ifdef Test
	int i = -1;
	cout << "第一步优化后" << endl;
	for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		/*cout << " -1的数量: "<< current_workload[++i] << " 老师所能承受的工作量: " <<this->teachers[i].getWorkload() <<endl;*/
		cout << " 相差的工作量: " << current_workload[++i] << " 老师所能承受的工作量: " << this->teachers[i].getWorkload() << endl;
	}
#endif
	/*将优化序列按照需要调整量有小到大排列,老师中需要调整的数量较少先选)*/
	//vector<int> searching_sequence;
	//for (int sequence = 0; sequence < current_workload.size(); ++sequence) {
	//	/*该老师工作量超标*/
	//	if (current_workload[sequence] > 0) {
	//		/*搜索序列还为空*/
	//		if (searching_sequence.empty()) {
	//			searching_sequence.push_back(sequence);
	//		}
	//		else {
	//			/*遍历搜索序列,查找待插入老师的位置*/
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
	//	cout << "当前即为最优方案" << endl;
	//	return;
	//}
	//for (int i : searching_sequence) {
	for (int i = 0; i < row; ++i) {
		if (current_workload[i] > 0) {
			/*cout << "寻找第" << i << "个老师的转化方案" << endl;*/
			//工作量大于承受量
			/*matrixArray received_array = matrixArray(current_workload[i], current_workload);*/

			/*标记一下已选择列,在接下来的选择中弃用该列*/
			vector<int> selected_cols = vector<int>(current_workload[i], -1);
			/*每次向外传送一个工作,总共需要的次数为current_workload[i]次,即该老师超量工作量*/
			while (0 < current_workload[i]) {
				/*找到可选范围内对总和影响最小的*/
				int min = INT32_MAX;
				int min_row = -1;
				int min_col = -1;
				/*j为列数*/
				/*遍历该老师的每一列*/
				for (int j = 0; j < col; ++j) {
					/*当前列为原来所选方案,那么待选方案也肯定是在这一行,这里j最重要*/
					if (matrix[i][j] == MAX_SELECTED) {
						for (int n = 0; n < row; ++n) {
							/*
							第一个条件:待选老师还能承担工作;
							第二个条件:待选方案比当前最优(min)更优
							第三个条件:待选方案之前没有选择过同一列的方案,(如果已经选过该列的,那么这一列自动全部放弃)
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
				//cout << "找到的最小的符合的值: " << min << "位置是[" << min_row << "][" << min_col << "]" << endl;
				selected_cols[current_workload[i] - 1] = min_col;
				++current_workload[min_row];
				--current_workload[i];
				change_col(min_col, min_row, matrix);
			}

			/*cout << "-----------------------" << endl;
			cout << "现在是第" << i << "行:"<<endl;
			for (auto instance : received_array.getInfo()) {
				cout << "将要替换" << instance.x << "," << instance.y << "位置" << endl;
			}*/
		}
	}
	i = -1;
	cout << "第二次优化后" << endl;
	for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		/*cout << " -1的数量: "<< current_workload[++i] << " 老师所能承受的工作量: " <<this->teachers[i].getWorkload() <<endl;*/
		cout << " 相差的工作量: " << current_workload[++i] << " 老师所能承受的工作量: " << this->teachers[i].getWorkload() << endl;
	}
/*尝试优化*/
	bool flag;
	do {
		flag = false;
		for (int i = 0; i < row; ++i) {
			for (int j = 0; j < col; ++j) {
				/*如果当前数字(matrix[i][j])为负数(可以尝试优化)并且不是已选方案, matrix[i][j]为备选方案*/
				if (matrix[i][j] < 0 && matrix[i][j] != MAX_SELECTED) {
					/*找到这一列的已选方案*/
					int selected_row = 0;
					for (; selected_row < row; ++selected_row) {
						if (matrix[selected_row][j] == MAX_SELECTED) {
							break;
						}
					}
					/*这个时候selected_row已经是当前列所选了*/
					if (current_workload[i] < 0) {
						//备选方案能够直接转让,不需要交换方案
						change_col(i, j, matrix);
						++current_workload[selected_row];
						--current_workload[i];
						flag = true;
						break;
					}
					/*遍历找到替换方案中的最小值*/
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
					/*比较交换的方案是否使得组合更加合理*/
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
	//	/*cout << " -1的数量: "<< current_workload[++i] << " 老师所能承受的工作量: " <<this->teachers[i].getWorkload() <<endl;*/
	//	cout << " 相差的工作量: " << current_workload[++i] << " 老师所能承受的工作量: " << this->teachers[i].getWorkload() << endl;
	//}
/*最后*/
	/*返回所选的老师*/


	///*打印一下矩阵*/
#ifdef Test
	i = -1;
	cout << "第三步优化后" << endl;
	for (vector<int> row : matrix) {
		for (int col : row) {
			cout << setw(5) << col;
		}
		/*cout << " -1的数量: "<< current_workload[++i] << " 老师所能承受的工作量: " <<this->teachers[i].getWorkload() <<endl;*/
		cout << " 相差的工作量: "<< current_workload[++i] << " 老师所能承受的工作量: " <<this->teachers[i].getWorkload() <<endl;
	}
#endif
}

/* 不会修改原有的subject,传回的数据是个修改后的副本 */
/* 功能是 */
vector<subject> courseSelectTeacherStrategy::changeSubjects(vector<subject> subjects)
{
	int classNum = this->classes.size();
	for (vector<subject>::iterator it = subjects.begin(); it != subjects.end(); it++) {
		/*向上取整*/
		/*cout << classNum << " : " << it->getWorkload()<<endl;*/
		it->setWorkload((classNum - 1) / it->getWorkload() + 1);
	}
	/*打印一下*/
	/*cout << "调整后:" << endl;
	for (auto subject: subjects) {
		cout << subject.getName() << " : "<< subject.getWorkload() << endl;
	}*/
	return subjects;
}
