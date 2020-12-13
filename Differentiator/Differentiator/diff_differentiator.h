#pragma once

#include <math.h>
#include <time.h>

#include "Stack.h"
#include "diff_work_with_file.h"
#include "diff_tree.h"
#include "tree_in_latex.h"

const double epsilon = 0.000001;

double			evaluate_expr						(Diff_tree* dtree, const long long index, double meaning);

long long		diff_create_new_lief				(Diff_tree* dtree, const char type, double future_value, long long parent_index);

/*long long		diff_plus							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_sub							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_mul							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_div							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_pow							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_ln								(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_sin							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_cos							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_sqrt							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);
long long		diff_diff							(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);*/
void			diff								(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index);

char			diff_roll_up_consts					(Diff_tree* dtree, long long index, char *changes);

char			diff_left_operations_with_zero		(Diff_tree* dtree, long long index);
char			diff_right_operations_with_zero		(Diff_tree* dtree, long long index);
char			diff_left_operations_with_one		(Diff_tree* dtree, long long index);
char			diff_right_operations_with_one		(Diff_tree* dtree, long long index);
char			diff_simplificate_operations		(Diff_tree* dtree, long long index, char *changes);

void			diff_simplificate					(Diff_tree* dtree);

/*void			diff_print_tree_node				(FILE *out, Diff_tree* dtree, long long index);
long long		diff_print_tree_expression			(FILE *out, Diff_tree* dtree, long long index, long long* array_for_reductions, long long current_empty_index);
void			diff_print_expression_and_reductions(FILE* out, Diff_tree* dtree, long long index);*/