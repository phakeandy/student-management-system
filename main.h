#include <stdio.h>
#include <stdlib.h>
#include "student.c"

#define STUDENT_INFO_FILE "./stu.info"

void print_menu();
void add_student();
void clear_buffer();
void print_student(Node *head);
void pause_on_win();
void show_all_student();
void find_student(Node *head);
void save_student();
void load_student(Node *head);
