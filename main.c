#include "main.h"

// int login(char username[], char password[]) { char name[MAX_NAEM_lEN]; }

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
            clear_input_buffer();
            pause_on_win();
            continue;
        }
        switch (op)
        {
        case 0:
            clear_screen();
            printf("成功退出, 欢迎下次使用!");
            flag = 0;
            break;
        case 1:
            add_student(head);
            break;
        case 2:
            show_all_student(head);
            break;
        case 3:
            find_student(head);
            break;
        case 4:
            update_student(head);
            break;
        case 5:
            delete_student(head);
            break;
        case 6:
            sort_student(head);
            break;
        case 7:
            get_mean_score(head);
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
    printf("4. 修改学生信息            \n");
    printf("5. 删除学生信息            \n");
    printf("6. 排序学生信息            \n");
    printf("7. 计算学生成绩平均数       \n");
    printf("0. 退出                    \n");
    printf("============================\n");
    printf("请输入相应的序号选择!       \n");
}

void add_student(Node *head)
{
    Node *fresh = malloc(sizeof(Node)); // fresh: 新生
    fresh->next = NULL;
    // printf("请输入学生的学号, 姓名, 年龄, 性别, 成绩\n");
    clear_screen();
    printf("请输入学生的学号, 姓名, 成绩:\n");
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

void clear_input_buffer()
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
    // system("pause");
    // system("cls");
    clear_input_buffer();
    printf("请输入任意字符继续...\n");
    getchar();
    clear_screen();
}

void clear_screen()
{
    printf("\033[2J\033[H"); // 跨平台清屏
}

void show_all_student(Node *head)
{
    clear_screen();
    int count = print_all_student(head);
    printf("总共有%d位学生...\n", count);
    pause_on_win();
}

int print_all_student(Node *head)
{
    Node *move = head->next;
    int count = 0;
    while (move != NULL)
    {
        printf("学号: %d    姓名: %s    分数: %d\n", move->student.id, move->student.name, move->student.score);
        count++;
        move = move->next;
    }
    return count;
}

void find_student(Node *head)
{
    clear_screen();
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
        printf("没有找到学号为:%d的学生...\n", stu_id);
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
    while (fread(&fresh->student, sizeof(Student), 1, file) == 1)
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

void update_student(Node *head)
{
    clear_screen();
    printf("请输入要修改学生的学号: ");
    int stu_id;
    scanf("%d", &stu_id);

    Node *move = head->next;

    while (move != NULL)
    {
        if (move->student.id = stu_id)
        {
            Student stu = move->student;
            printf("找到学号为:%d的学生: 姓名: %s\t成绩: %d\n", stu.id, stu.name, stu.score);
            printf("请输入新的学号, 姓名, 成绩:");
            scanf("%d%s%d", &move->student.id, move->student.name, &move->student.score);
            save_student(head);
            printf("成功修改!\n");
            pause_on_win();
            return;
        }
        move = move->next;
    }

    printf("未找到学号为%d的学生...\n", stu_id);
    pause_on_win();
}

void delete_student(Node *head)
{
    show_all_student(head);
    printf("请输入要删除学生的学号: ");
    int stu_id;
    scanf("%d", &stu_id);

    Node *move = head; // 注意没有 next

    while (move->next != NULL)
    {
        if (move->next->student.id == stu_id)
        {
            Node *tmp = move->next;
            move->next = move->next->next;
            free(tmp);  // 释放内存
            tmp = NULL; // 防止野指针
            save_student(head);
            printf("删除成功!\n");
            pause_on_win();
            return;
        }
        move = move->next;
    }
    printf("未找到该学生\n");
    pause_on_win();
}

void sort_student(Node *head)
{
    // 冒泡排序
    for (Node *turn = head->next; turn->next != NULL; turn = turn->next)
    {
        for (Node *move = head->next; move->next != NULL; move = move->next)
        {
            if (move->student.score > move->next->student.score)
            {
                // 交换学生而不是节点
                Student temp = move->student;
                move->student = move->next->student;
                move->next->student = temp;
            }
        }
    }
    printf("排序成功!\n");
    show_all_student(head);
}

// 主要是为了使用数组
int get_mean_score(Node *head)
{
    clear_screen();
    int arr[MAX_STUDENT] = {0};
    Node *move = head->next;

    int count = 0;
    while (move != NULL)
    {
        arr[count] = move->student.score;
        count++;
        move = move->next;
    }

    int sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += arr[i];
    }
    printf("共有%d名学生\n", count);
    printf("学生成绩平均数为: %f\n", (double)sum / count);
    pause_on_win();
}