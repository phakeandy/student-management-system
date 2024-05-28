#define MAX_NAEM_lEN 20
#define MAX_STUDENT 1000

typedef struct _Student
{
	int id;					 // 学生学号
	char name[MAX_NAEM_lEN]; // 姓名
	int age;				 // 年龄
	char sex;				 // 性别
	int score;				 // 成绩
} Student;

typedef struct _Node
{
	Student student;	// 学生信息
	struct _Node *next; // 指向下一个节点
} Node;
