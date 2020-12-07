#pragma once

#include <math.h>
#include <time.h>

#include "Stack.h"
#include "diff_work_with_file.h"
#include "diff_tree.h"

long long diff_create_new_lief(Diff_tree* dtree, const char type, double future_value, long long left_index, long long right_index, long long parent_index);
void diff(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);

char diff_roll_up_consts(Diff_tree* dtree, long long index, char *changes);

char diff_left_operations_with_zero(Diff_tree* dtree, long long index);
char diff_right_operations_with_zero(Diff_tree* dtree, long long index);
char diff_left_operations_with_one(Diff_tree* dtree, long long index);
char diff_right_operations_with_one(Diff_tree* dtree, long long index);
char diff_simplificate_operations(Diff_tree* dtree, long long index, char *changes);

void diff_simplificate(Diff_tree* dtree);

void diff_print_tree_node(Diff_tree* dtree, long long index);
void diff_print_tree_expression(Diff_tree* dtree, long long index);