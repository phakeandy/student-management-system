#include "main.h"

int login(char username[], char password[]) { char name[MAX_NAEM_lEN]; }

int main()
{
    Node *head = malloc(sizeof(Node));
    head->next = NULL;

    printf("welcome!!\n");
    load_student(head);

    int flag = 1;
    while (flag)
    {
        print_menu();

        int op;
        if ((scanf("%d", &op) == 0))
        {
            printf("Error: 输入无效, 请输入整数\n");
            clear_buffer();
            continue;
        }
        switch (op)
        {
        case 0:
            printf("成功退出!");
            flag = 0;
            break;
        case 1:
            add_student(head);
            break;
        case 2:
            show_all_student(head);
            // print_student(head);
            break;
        case 3:
            // print_student(head);
            find_student(head);
            break;
        default:
            printf("Error: 输入无效, 请输入0~6的整数\n");
            break;
        }
    }

    return 0;
}

void print_menu() // 打印主菜单函数
{
    printf("=========学生管理系统=========\n");
    printf("1. 添加学生信息            \n");
    printf("2. 显示所有学生信息        \n");
    printf("3. 查询学生信息            \n");
    printf("4. 排序学生信息            \n");
    printf("5. 修改学生信息            \n");
    printf("0. 退出                    \n");
    printf("请输入相应的序号选择!       \n");
}

void add_student(Node *head)
{
    Node *fresh = malloc(sizeof(Node)); // fresh: 新生
    fresh->next = NULL;
    // printf("请输入学生的学号, 姓名, 年龄, 性别, 成绩\n");
    printf("请输入学生的学号, 姓名, 成绩\n");
    scanf("%d%s%d", &fresh->student.id, fresh->student.name, &fresh->student.score);

    // 尾插法
    Node *move = head;

    while (move->next != NULL)
    {
        move = move->next;
    }
    move->next = fresh;

    save_student(head);
    pause_on_win();
}

void clear_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void print_student(Node *head)
{
    Node *move = head->next; // 将 move 初始化为首节点, 这种只能在遍历时使用, 插入时不行
    while (move != NULL)
    {
        printf("姓名: %s    学号: %d    分数: %d\n", move->student.name, move->student.id, move->student.score);
        move = move->next;
    }
    pause_on_win();
}

void pause_on_win()
{
    system("pause");
    system("cls");
}

void show_all_student(Node *head)
{
    Node *move = head->next;
    int count = 0;
    while (move != NULL)
    {
        printf("姓名: %s    学号: %d    分数: %d\n", move->student.name, move->student.id, move->student.score);
        count++;
        move = move->next;
    }
    printf("总共有%d位学生...\n", count);
    pause_on_win();
}

void find_student(Node *head)
{
    printf("请输入学生学号: ");
    int stu_id;
    scanf("%d", &stu_id);

    Node *move = head->next;

    int count = 0;
    while (move != NULL)
    {
        if (stu_id == move->student.id)
        {
            printf("姓名: %s    学号: %d    分数: %d\n", move->student.name, move->student.id, move->student.score);
            count++;
        }
        move = move->next;
    }
    if (count == 0)
    {
        printf("没有找到学号为:%d的学生...", stu_id);
    }
    pause_on_win();
}

void save_student(Node *head)
{
    FILE *file = fopen(STUDENT_INFO_FILE, "w"); // 覆盖原文件
    if (file == NULL)
    {
        printf("Erorr: 打开文件失败");
    }
    Node *move = head->next;

    while (move != NULL)
    {
        if (fwrite(&move->student, sizeof(Student), 1, file) != 1) // 写 1 块
        {
            printf("保存%s学生数据时出错\n", move->student.name);
        }
        move = move->next;
    }
    fclose(file);
}

void load_student(Node *head)
{
    FILE *file = fopen(STUDENT_INFO_FILE, "r");

    if (file == NULL)
    {
        printf("Warning: 学生信息文件%s丢失, 跳过读取!!!\n", STUDENT_INFO_FILE);
        return;
    }

    Node *fresh = malloc(sizeof(Node));
    fresh->next = NULL;

    Node *move = head;
    while (fread(&move->student, sizeof(Student), 1, file) == 1)
    {
        move->next = fresh;
        move = move->next;
        fresh = malloc(sizeof(Node));
        fresh->next = NULL;
    }
    free(fresh);
    fclose(file);
    printf("成功读取学生信息文件存档!!!\n");
}