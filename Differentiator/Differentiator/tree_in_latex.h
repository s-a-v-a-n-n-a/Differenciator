#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include "diff_tree.h"
#include "diff_differentiator.h"

void			tree_tex_call								();

void			diff_print_introduction						(FILE* out);
void			diff_print_phrase							(FILE* out, int phrase);
void			diff_print_formula							(FILE* out, Diff_tree* dtree, long long index);
void			diff_print_conclusion						(FILE* out);
void			diff_print_formula_in_tex					(Diff_tree* dtree, long long index, char end, int phrase, int command);

void			build_graph									(FILE* out, Diff_tree* dtree);

long long		diff_count_depth							(Diff_tree* dtree, long long index);

void			diff_print_tree_node						(FILE* out, Diff_tree* dtree, long long index);

long long		diff_print_casual_operations				(FILE* out, Diff_tree* dtree, long long parent, long long son, long long* array_for_reductions, long long current_empty_index);
long long		diff_print_left_branch						(FILE* out, Diff_tree* dtree, long long index, long long* array_for_reductions, long long current_empty_index);
long long		diff_print_right_branch						(FILE* out, Diff_tree* dtree, long long index, long long* array_for_reductions, long long current_empty_index);
long long		diff_print_tree_expression					(FILE* out, Diff_tree* dtree, long long index, long long* array_for_reductions, long long current_empty_index);

void			diff_print_expression_and_reductions		(FILE* out, Diff_tree* dtree, long long index);