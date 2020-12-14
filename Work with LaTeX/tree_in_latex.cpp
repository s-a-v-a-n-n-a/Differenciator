#define _CRT_SECURE_NO_WARNINGS

#include "tree_in_latex.h"

const char* phrase_bank[] =
{
	"{\\bf We are going to work with this expression, but before we'll simplify it:}\n",
	"{\\bf So it looks like this:}\n",
	"{\\bf Let's find deprivative for this expression:}\n",
	"{\\bf So, I'll try to simplify it, let's believe in my success}\n",
	"{\\bf Final deprivative is:}\n",
	"{\\bf Let's see how does it look like:}\n",
	"We pretend that we can calculate derivatives:\n",
	"mATAN is my whole life!\n",
	"With this program you don't need to be a genius to calculate the speed of me going mad\n",
	"My name is Anya Savchuk but my dept calls me to calculate derivatives\n",
	"The show must go on\n",
	"Just do it!\n",
	"It may look strange but I hope that's right\n"
};

void tree_tex_call()
{
	char temp[512];
	sprintf(temp, "pdflatex %s > nul", DEFAULT_TEX_FILE_NAME);
	system((char*)temp);

	sprintf(temp, "%s", DEFAULT_PDF_FILE_NAME);
	system((char*)temp);
}

void diff_print_introduction(FILE* out)
{
	fprintf(out, "\\documentclass{article}\n");
	fprintf(out, "\\usepackage[T2A]{fontenc}\n");
	fprintf(out, "\\usepackage[utf8x]{inputenc}\n");
	fprintf(out, "\\usepackage[russian]{babel}\n");
	fprintf(out, "\\usepackage[normalem]{ulem}\n");
	fprintf(out, "\\usepackage{amsmath}\n");
	fprintf(out, "\\usepackage{tikz}\n"
				 "\\usepackage{pgfplots}\n"
				 "\\pgfplotsset{compat=1.9}\n");
	fprintf(out, "\\textheight=24cm\n");
	fprintf(out, "\\textwidth=17cm\n");
	fprintf(out, "\\oddsidemargin=-30pt\n");
	fprintf(out, "\\topmargin=-2cm\n");
	fprintf(out, "\\parskip=5pt\n");

	fprintf(out, "\\begin{document}\n");

	fprintf(out, "\\begin{center}\n");
	fprintf(out, "{\\bf MIPT 2020 presents}\n\n");
	fprintf(out, "\n\n \\begin{Huge}\n{\\bf <<Bad mathematitian taking deprivatives>>}\n \\end{Huge} \n\n");
	fprintf(out, "$\\copyright$ Annnna Savchuk\n");
	fprintf(out, "\\end{center}\n");
	fprintf(out, "%s", INTRODUCTION);
	fprintf(out, "%s", PLAN);
}

void diff_print_phrase(FILE* out, int phrase)
{
	if (phrase < PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT)
	{
		fprintf(out, "\\begin{flushleft}\n");
		fprintf(out, "%s", phrase_bank[phrase]);
		fprintf(out, "\\end{flushleft}\n");
	}
	else
	{
		int phrase_number = rand() % (PHRASES_AMOUNT - PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT) + PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT;
		fprintf(out, "%s", phrase_bank[phrase_number]);
	}
}

void diff_print_formula(FILE* out, Diff_tree* dtree, long long index)
{
	diff_print_expression_and_reductions(out, dtree, index);
}

void diff_print_conclusion(FILE* out)
{
	fprintf(out, "%s", REFERENCES);
	fprintf(out, "\\end{document}\n");
}

void diff_print_formula_in_tex(Diff_tree* dtree, long long index, char end, int phrase, int command)
{
	static long long opening = 0;
	char mode[] = "ab";
	if (!opening)
		mode[0] = 'w';
	FILE* out = fopen(DEFAULT_TEX_FILE_NAME, mode);

	if (!opening)
		diff_print_introduction(out);

	diff_print_phrase(out, phrase);
	if (command == FORMULA)
		diff_print_formula(out, dtree, index);
	else
		build_graph(out, dtree);

	if (end)
		diff_print_conclusion(out);

	fclose(out);

	opening++;
}

void build_graph(FILE* out, Diff_tree* dtree)
{
	fprintf(out, "\\begin{center}"
		"\\begin{tikzpicture}\n"
		"\\begin{axis}\n"
		"\\addplot coordinates {\n");
	for (double i = MIN_X; i < MAX_X; i += delta)
	{
		double point = evaluate_expr(dtree, dtree->root_index, i);
		fprintf(out, "(%lg, %lg)\n", i, point);
	}

	fprintf(out, "};\n"
		"\\end{axis}\n"
		"\\end{tikzpicture}\n"
		"\\end{center}\n\n");
}

long long diff_count_depth(Diff_tree* dtree, long long index)
{
	if (tree_if_lief(dtree, index))
	{
		dtree->tree[index].depth = 1;
		return 1;
	}

	long long left = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	long long left_amount = 0;
	long long right_amount = 0;

	if (left != ABSENT)
		left_amount = diff_count_depth(dtree, left);
	if (right != ABSENT)
		right_amount = diff_count_depth(dtree, right);

	dtree->tree[index].depth = left_amount + right_amount + 1;
	return left_amount + right_amount + 1;
}

#define DEFINE_OPS(name, number, tex_name, priority, differentiate, evaluate)\
		case number:\
			fprintf(out, "%s", tex_name);\
			break;

void diff_print_tree_node(FILE* out, Diff_tree* dtree, long long index)
{
	char type = tree_get_type(dtree, index);

	if (type == NUMBER)
	{
		long long parent = tree_parent(dtree, index);

		long long parent_left = tree_left_son(dtree, parent);
		long long parent_right = tree_right_son(dtree, parent);

		tree_operations parent_op = dtree->tree[parent].operation;

		if (((parent_op == OP_LN || parent_op == OP_SIN || parent_op == OP_COS || parent_op == OP_SQRT) && index == tree_left_son(dtree, parent))
			|| (parent_op == OP_DIFF && index == tree_right_son(dtree, parent)))
			;
		else if (dtree->tree[index].number < 0)
			fprintf(out, "\\left( %lg \\right)", dtree->tree[index].number);
		else
			fprintf(out, "%lg", dtree->tree[index].number);
	}
	else if (type == VARIABLE)
		fprintf(out, "%c", dtree->tree[index].variable);
	else if (dtree->tree[index].operation == OP_MUL)
		fprintf(out, " \\cdot ");
	else
	{
		switch (tree_get_operation(dtree, index))
		{
		#include "Operations.h"
		default:
			break;
		}
	}
}

#undef DEFINE_OPS

long long diff_print_casual_operations(FILE* out, Diff_tree* dtree, long long parent, long long son, long long* array_for_reductions, long long current_empty_index)
{
	tree_operations parent_op = tree_get_operation(dtree, parent);
	tree_operations son_op = tree_get_operation(dtree, son);
	if (tree_priorities[parent_op] < tree_priorities[son_op] || ((parent_op == son_op) && (parent_op == OP_SUB)))
	{
		fprintf(out, "\\left(");
		current_empty_index = diff_print_tree_expression(out, dtree, son, array_for_reductions, current_empty_index);
		fprintf(out, "\\right)");
	}
	else
		current_empty_index = diff_print_tree_expression(out, dtree, son, array_for_reductions, current_empty_index);

	return current_empty_index;
}

long long diff_print_left_branch(FILE* out, Diff_tree* dtree, long long index, long long* array_for_reductions, long long current_empty_index)
{
	long long left = tree_left_son(dtree, index);
	tree_operations current_op = tree_get_operation(dtree, index);
	if (tree_get_type(dtree, left) == OPERATION)
	{
		current_empty_index = diff_print_casual_operations(out, dtree, index, left, array_for_reductions, current_empty_index);
	}
	else
		current_empty_index = diff_print_tree_expression(out, dtree, left, array_for_reductions, current_empty_index);

	return current_empty_index;
}

long long diff_print_right_branch(FILE* out, Diff_tree* dtree, long long index, long long* array_for_reductions, long long current_empty_index)
{
	long long right = tree_right_son(dtree, index);
	tree_operations current_op = tree_get_operation(dtree, index);
	if (tree_get_type(dtree, right) == OPERATION)
	{
		tree_operations right_op = dtree->tree[right].operation;
		if ((current_op == OP_SQRT || current_op == OP_POW) && out != stdout)
		{
			fprintf(out, "{");
			current_empty_index = diff_print_tree_expression(out, dtree, right, array_for_reductions, current_empty_index);
			fprintf(out, "}");
		}
		else
			current_empty_index = diff_print_casual_operations(out, dtree, index, right, array_for_reductions, current_empty_index);
	}
	else
		current_empty_index = diff_print_tree_expression(out, dtree, right, array_for_reductions, current_empty_index);

	return current_empty_index;
}

long long diff_print_tree_expression(FILE* out, Diff_tree* dtree, long long index, long long* array_for_reductions, long long current_empty_index)
{
	if (tree_if_lief(dtree, index))
	{
		diff_print_tree_node(out, dtree, index);
		return current_empty_index;
	}

	long long amount = tree_get_depth(dtree, index);

	if (amount < MAX_EXPR_AMOUNT_TO_PRINT && amount > MIN_EXPR_AMOUNT_TO_PRINT && array_for_reductions)
	{
		array_for_reductions[current_empty_index++] = index;
		fprintf(out, "%c", ('A' + current_empty_index - 1));

		return current_empty_index;
	}
	else
	{
		long long left  = tree_left_son(dtree, index);
		long long right = tree_right_son(dtree, index);

		tree_operations current_op = dtree->tree[index].operation;

		if (current_op == OP_DIV)
			fprintf(out, "\\frac{");

		if (left != ABSENT)
			current_empty_index = diff_print_left_branch(out, dtree, index, array_for_reductions, current_empty_index);

		//if (current_op == OP_SQRT && out != stdout)
			//fprintf(out, "\\");
		if (current_op != OP_DIV)
			diff_print_tree_node(out, dtree, index);
		else
			fprintf(out, "}{");

		if (right != ABSENT)
			current_empty_index = diff_print_right_branch(out, dtree, index, array_for_reductions, current_empty_index);

		if (current_op == OP_DIV)
			fprintf(out, "}");

		return current_empty_index;
	}
}

void diff_print_expression_and_reductions(FILE* out, Diff_tree* dtree, long long index)
{
	long long long_expressions[LETTERS] = { -1 };
	long long current_empty_index = 0;

	diff_count_depth(dtree, index);

	fprintf(out, "$$");
	current_empty_index = diff_print_tree_expression(out, dtree, index, long_expressions, 0);

	if (current_empty_index)
		fprintf(out, ", $$ where\n");
	else
		fprintf(out, "$$\n");
	for (int i = 0; i < current_empty_index; i++)
	{
		fprintf(out, "$$");
		fprintf(out, "%c = ", 'A' + i);
		diff_print_tree_expression(out, dtree, long_expressions[i], NULL, 0);
		fprintf(out, "$$\n");
	}
}