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
myClass c5 = myClass(15, "һ�꼶���");
myClass c6 = myClass(16, "һ�꼶����");
myClass c7 = myClass(17, "һ�꼶�߰�");
myClass c8 = myClass(18, "һ�꼶�˰�");
vector<myClass> classes = { c1, c2, c3, c4, c5, c6, c7, c8 };

/*ѧ��*/
/*���Ϊѧ������, ��λ������Ϊһ����ʦ�ܹ�������ٸ���ĸ�ѧ��,����ʦ�Ĺ������е��ϵ,��ʦ�����ܹ����ܵĹ�������λ,����ľ��Ǿ��Ƕ��ٸ���ĸ�ѧ���ڿ������Ӧ��ʦ��һ����������λ*/
vector<subject> subjects = {
	/*���� ��λ������ ѧ����� ѧ�ƿ�ʱ(�����) ÿ�ܿ�ʱ*/
	{"����", 1, 1, 30, 4},
	{"��ѧ", 1, 2, 30, 4},
	{"Ӣ��", 1, 3, 30, 4},
	{"����", 2, 4, 16, 3},
	{"��ѧ", 4, 5, 21, 3},
	{"��ʷ", 4, 6, 15, 1},
	{"����", 4, 7, 17, 3},
	{"����", 3, 8, 19, 2},
	{"����", 3, 9, 24, 2},
	{"����", 3, 10, 14, 2},
};
/*��ʦ����*/
teacher t1 = teacher("����ʦ", 1, 7);
teacher t2 = teacher("����ʦ", 2, 6);
teacher t3 = teacher("����ʦ", 3, 6);
teacher t4 = teacher("����ʦ", 4, 4);
teacher t5 = teacher("л��ʦ", 5, 5);
teacher t6 = teacher("֣��ʦ", 6, 5);
teacher t7 = teacher("����ʦ", 7, 9);
teacher t8 = teacher("����ʦ", 8, 6);
teacher t9 = teacher("����ʦ", 9, 7);

/* �������� */
vector<classroom> classrooms = {
	{"1101", 2},
	{"1102", 2},
	{"1103", 2},
	{"1104", 4},
	{"1201", 2},
	{"1202", 4}/*,
	{"1203", 4},
	{"1204", 2},*/
};



int main() {
	//��ʦ�ĺ��ʶ�
	t1.setSuitableIndex(subjects.size(), { 1, 6, 8, 7, 4, 9, 1, 3, 10, 9 });
	t2.setSuitableIndex(subjects.size(), { 7, 4, 10, 1, 9, 6, 10, 5, 2, 8 });
	t3.setSuitableIndex(subjects.size(), { 1, 1, 8, 3, 6, 1, 1, 0, 10, 7 });
	t4.setSuitableIndex(subjects.size(), { 4, 8, 3, 10, 4, 8, 10, 0, 1, 2 });
	t5.setSuitableIndex(subjects.size(), { 4, 1, 10, 9, 0, 8, 0, 3, 10, 4 });
	t6.setSuitableIndex(subjects.size(), { 1, 6, 4, 6, 0, 9, 5, 6, 1, 7 });
	t7.setSuitableIndex(subjects.size(), { 5, 6, 10, 1, 5, 0, 6, 5, 5, 10 });
	t8.setSuitableIndex(subjects.size(), { 3, 5, 5, 9, 2, 4, 1, 0, 10, 3 });
	t9.setSuitableIndex(subjects.size(), { 9, 3, 2, 7, 1, 6, 5, 6, 2, 9 });
	vector<teacher> teachers = vector<teacher>{
	t1, t2, t3, t4, t5, t6, t7, t8, t9
	};
	/*for (auto i : teachers) {
		i.printIndex(subjects);
	}*/
	vector<course> courses;
	courseSelectTeacherStrategy cs = courseSelectTeacherStrategy(teachers, subjects, classes, classrooms);
	cout << "------------------��ѯ�༶---------------" << endl;
	cs.getWeeklyLessonByClass(c1);
	cout << "------------------��ѯ��ʦ---------------" << endl;
	cs.getWeeklyLessonByTeacher(t1);
	return 0;
}