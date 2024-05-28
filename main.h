#include <stdio.h>
#include <stdlib.h>
#include "student.c"

#define STUDENT_INFO_FILE "./students.dat"

void print_menu();
void add_student(Node *head);
void clear_input_buffer();
void print_student(Node *head);
void pause_on_win();
void show_all_student(Node *head);
void find_student(Node *head);
void save_student(Node *head);
void load_student(Node *head);
void update_student(Node *head);
void delete_student(Node *head);
void sort_student(Node *head);
int print_all_student(Node *head);
void clear_screen();
int get_mean_score(Node *head);