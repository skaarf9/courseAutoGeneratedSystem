#include "course.h"
#include <iostream>
#include "teacher.h"
#include "courseSelectionStrategy.h"
#include "classroomAndTime.h"
using namespace std;




/*全局变量*/

/*班级*/
myClass c1 = myClass(11, "一年级一班");
myClass c2 = myClass(12, "一年级二班");
myClass c3 = myClass(13, "一年级三班");
myClass c4 = myClass(14, "一年级四班");
vector<myClass> classes = { c1, c2, c3, c4 };

/*学科*/
/*左边为学科名称, 右边为一名老师能够负责多少个班的该学科,和老师的工作量有点关系,老师的是能够承受的工作量单位,这里的就是就是多少个班的该学科授课任务对应老师的一个工作量单位
当老师太少时会出现多个相同course的可能性,即学科和老师相同,这是否是个应该解决的问题还有待商榷
*/
vector<subject> subjects = {
	/*名称 单位工作量 学科序号 学科课时(随机的) 每周课时*/
	{"语文", 2, 1, 30, 2},
	{"数学", 2, 2, 30, 2},
	{"英语", 2, 3, 30, 2},
	{"物理", 2, 4, 16, 2},
	{"化学", 4, 5, 21, 2},
	{"历史", 4, 6, 15, 1},
	{"生物", 4, 7, 17, 2},
	{"地理", 4, 8, 19, 2},
	{"政治", 4, 9, 24, 2}
};
/*教师数据*/
/* 教师的合适度(随机数生成的,具体赋值在main函数中)
1  6  8  7  4  9  1  3  10
7  4  10 1  9  6  10 5  2
1  1  8  3  6  1  1  0  10
4  8  3  10 4  8  10 0  1
4  1  10 9  0  8  10 3  10
*/
teacher t1 = teacher("张老师", 1, 3);
teacher t2 = teacher("李老师", 2, 4);
teacher t3 = teacher("王老师", 3, 3);
teacher t4 = teacher("周老师", 4, 1);
teacher t5 = teacher("谢老师", 5, 2);

/* 教室数据 */
vector<classroom> classrooms = {
	{"1101", 2},
	{"1102", 2},
	{"1103", 2},
	{"1104", 4},
	{"1201", 2},
	{"1202", 4}
};



int main() {
	/*teacher t1 = teacher("张老师", 23, 3);*/
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
	/*course course1 = course(1, "语文", vector<myClass>{c1, c2, c3, c4});
	cout << course1.getInfo()<< endl;*/
	return 0;
}