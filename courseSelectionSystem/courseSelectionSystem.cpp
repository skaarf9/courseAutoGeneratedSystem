#include "course.h"
#include <iostream>
#include "teacher.h"
#include "courseSelectionStrategy.h"
#include "classroomAndTime.h"
using namespace std;




/*ȫ�ֱ���*/

/*�༶*/
myClass c1 = myClass(11, "һ�꼶һ��");
myClass c2 = myClass(12, "һ�꼶����");
myClass c3 = myClass(13, "һ�꼶����");
myClass c4 = myClass(14, "һ�꼶�İ�");
vector<myClass> classes = { c1, c2, c3, c4 };

/*ѧ��*/
/*���Ϊѧ������, �ұ�Ϊһ����ʦ�ܹ�������ٸ���ĸ�ѧ��,����ʦ�Ĺ������е��ϵ,��ʦ�����ܹ����ܵĹ�������λ,����ľ��Ǿ��Ƕ��ٸ���ĸ�ѧ���ڿ������Ӧ��ʦ��һ����������λ
����ʦ̫��ʱ����ֶ����ͬcourse�Ŀ�����,��ѧ�ƺ���ʦ��ͬ,���Ƿ��Ǹ�Ӧ�ý�������⻹�д���ȶ
*/
vector<subject> subjects = {
	/*���� ��λ������ ѧ����� ѧ�ƿ�ʱ(�����) ÿ�ܿ�ʱ*/
	{"����", 2, 1, 30, 2},
	{"��ѧ", 2, 2, 30, 2},
	{"Ӣ��", 2, 3, 30, 2},
	{"����", 2, 4, 16, 2},
	{"��ѧ", 4, 5, 21, 2},
	{"��ʷ", 4, 6, 15, 1},
	{"����", 4, 7, 17, 2},
	{"����", 4, 8, 19, 2},
	{"����", 4, 9, 24, 2}
};
/*��ʦ����*/
/* ��ʦ�ĺ��ʶ�(��������ɵ�,���帳ֵ��main������)
1  6  8  7  4  9  1  3  10
7  4  10 1  9  6  10 5  2
1  1  8  3  6  1  1  0  10
4  8  3  10 4  8  10 0  1
4  1  10 9  0  8  10 3  10
*/
teacher t1 = teacher("����ʦ", 1, 3);
teacher t2 = teacher("����ʦ", 2, 4);
teacher t3 = teacher("����ʦ", 3, 3);
teacher t4 = teacher("����ʦ", 4, 1);
teacher t5 = teacher("л��ʦ", 5, 2);

/* �������� */
vector<classroom> classrooms = {
	{"1101", 2},
	{"1102", 2},
	{"1103", 2},
	{"1104", 4},
	{"1201", 2},
	{"1202", 4}
};



int main() {
	/*teacher t1 = teacher("����ʦ", 23, 3);*/
	/*t1.setSuitableIndex(subjects);*/
	t1.setSuitableIndex(subjects.size(), { 1, 6, 8, 7, 4, 9, 1, 3, 10 });
	t2.setSuitableIndex(subjects.size(), { 7, 4, 10, 1, 9, 6, 10, 5, 2 });
	t3.setSuitableIndex(subjects.size(), { 1, 1, 8, 3, 6, 1, 1, 0, 10 });
	t4.setSuitableIndex(subjects.size(), { 4, 8, 3, 10, 4, 8, 10, 0, 1 });
	t5.setSuitableIndex(subjects.size(), { 4, 1, 10, 9, 0, 8, 10, 3, 10 });
	vector<teacher> teachers = vector<teacher>{
	t1, t2, t3, t4, t5
	};
	/*for (auto i : teachers) {
		i.printIndex(subjects);
	}*/
	vector<course> courses;
	courseSelectTeacherStrategy cs = courseSelectTeacherStrategy(teachers, subjects, classes, classrooms);
	cs.courseSelectT();
	/*course course1 = course(1, "����", vector<myClass>{c1, c2, c3, c4});
	cout << course1.getInfo()<< endl;*/
	return 0;
}