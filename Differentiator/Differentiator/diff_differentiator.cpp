#define _CRT_SECURE_NO_WARNINGS

#include "diff_differentiator.h"

#define DEFINE_OPS(name, number, tex_name, priority, differentiate, evaluate)\
        case number:\
            evaluate;\
            break;

double evaluate_expr(Diff_tree* dtree, const long long index, double meaning)
{
	if (tree_if_lief(dtree, index))
	{
		if (tree_get_type(dtree, index) == NUMBER)
			return tree_get_number(dtree, index);
		else
			return meaning;
	}

	long long left = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	double left_value  = 0;
	double right_value = 0;

	if (left != ABSENT)
		left_value = evaluate_expr(dtree, left, meaning);
	if (right != ABSENT)
		right_value = evaluate_expr(dtree, right, meaning);

	tree_operations op = tree_get_operation(dtree, index);

	double value = 0;
	switch (op)
	{
		#include "Operations.h"

		default:
			return ABSENT;
	}
	return value;
}

#undef DEFINE_OPS

/*
long long diff_plus(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERENTIATE_PLUS
	DIFFERENTIATE_LEFT
	DIFFERENTIATE_RIGHT

	return current_index;
}

long long diff_sub(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERENTIATE_MINUS
	DIFFERENTIATE_LEFT
	DIFFERENTIATE_RIGHT

	return current_index;
}

long long diff_mul(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERENTIATE_PLUS

	current_index = DIFFERNTIATE_MUL
	DIFFERENTIATE_LEFT
	COPY_RIGHT

	current_index = tree_parent(dtree, current_index);

	current_index = DIFFERNTIATE_MUL
	DIFFERENTIATE_RIGHT
	COPY_LEFT

	return current_index;
}

long long diff_div(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERENTIATE_DIV

	current_index = DIFFERENTIATE_MINUS

	current_index = DIFFERNTIATE_MUL
	DIFFERENTIATE_LEFT
	COPY_RIGHT

	current_index = tree_parent(dtree, current_index);

	current_index = DIFFERNTIATE_MUL
	DIFFERENTIATE_RIGHT
	COPY_LEFT

	current_index = tree_parent(dtree, tree_parent(dtree, current_index));

	current_index = DIFFERNTIATE_MUL
	COPY_RIGHT
	COPY_RIGHT

	return current_index;
}

long long diff_pow(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERNTIATE_MUL

	current_index = DIFFERENTIATE_POW
	current_index = DIFFERENTIATE_POW(exp(1))

	current_index = tree_parent(dtree, current_index);

	current_index = DIFFERNTIATE_MUL
	COPY_RIGHT
	current_index = DIFFERENTIATE_LOG
	current_index = DIFFERENTIATE_POW(ABSENT)

	current_index = tree_parent(dtree, current_index);
	COPY_LEFT

	current_index = tree_parent(dtree, current_index);
	current_index = tree_parent(dtree, current_index);
	current_index = tree_parent(dtree, current_index);

	current_index = DIFFERENTIATE_PLUS
	current_index = DIFFERNTIATE_MUL

	DIFFERENTIATE_RIGHT

	current_index = DIFFERENTIATE_LOG
	current_index = DIFFERENTIATE_POW(ABSENT)

	current_index = tree_parent(dtree, current_index);
	COPY_LEFT

	current_index = tree_parent(dtree, current_index);
	current_index = tree_parent(dtree, current_index);

	current_index = DIFFERNTIATE_MUL
	current_index = DIFFERENTIATE_DIV

	DIFFERENTIATE_LEFT

	COPY_LEFT

	current_index = tree_parent(dtree, current_index);
	COPY_RIGHT

	return current_index;
}

long long diff_ln(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERENTIATE_DIV;
	DIFFERENTIATE_POW(1);
	COPY_RIGHT;

	return current_index;
}

long long diff_sin(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERNTIATE_MUL
	current_index = DIFFERENTIATE_COS
	DIFFERENTIATE_POW(ABSENT);
	COPY_RIGHT

	current_index = tree_parent(dtree, current_index);

	DIFFERENTIATE_RIGHT

	return current_index;
}

long long diff_cos(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERNTIATE_MUL

	current_index = DIFFERNTIATE_MUL
	DIFFERENTIATE_POW(ABSENT);
	current_index = DIFFERENTIATE_SIN
	DIFFERENTIATE_POW(ABSENT);

	COPY_RIGHT

	current_index = tree_parent(dtree, current_index);
	current_index = tree_parent(dtree, current_index);

	DIFFERENTIATE_RIGHT

	return current_index;
}

long long diff_sqrt(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	current_index = DIFFERNTIATE_MUL
	DIFFERENTIATE_POW(0.5)
	DIFFERENTIATE_RIGHT

	return current_index;
}

long long diff_diff(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	tree_clean_branch(dtree, dtree->tree[current_index].right_son);
	DO_DIFFERENTIATION
	tree_remove_knot(dtree, current_index, dtree->tree[current_index].right_son);
	current_index = dtree->tree[current_index].right_son;

	if (!tree_if_lief(dtree, current_index))
		diff_print_formula_in_tex(dtree, current_index, 0, PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT);

	return current_index;
}
*/

long long diff_create_new_lief(Diff_tree* dtree, const char type, double future_value, long long parent_index)
{
	long long new_index = 0;
	switch (type)
	{
	case NUMBER:
		tree_insert_number(dtree, &parent_index, future_value);
		break;
	case OPERATION:
		tree_insert_operation(dtree, &parent_index, (tree_operations)future_value);
		break;
	default:
		tree_insert_number(dtree, &parent_index, future_value);
		break;
	}
	return parent_index;
}

#define DEFINE_OPS(name, number, tex_name, priority, differentiate, evaluate)\
        case number:\
            differentiate;\
            break;

void diff(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	switch (tree_get_type(old_tree, branch))
	{
	case NUMBER:
		current_index = DIFFERENTIATE_VALUE(NUMBER);
		break;
	case VARIABLE:
		if (tree_get_variable(old_tree, branch) == DIFF_VARIABLE)
			current_index = DIFFERENTIATE_VALUE(VARIABLE)
		else
			current_index = DIFFERENTIATE_VALUE(NUMBER)
		break;
	case OPERATION:
		switch (tree_get_operation(old_tree, branch))
		{
		/*case OP_PLUS:
			current_index = diff_plus(old_tree, dtree, branch, current_index);
			break;
		case OP_SUB:
			current_index = diff_sub(old_tree, dtree, branch, current_index);
			break;
		case OP_MUL:
			current_index = diff_mul(old_tree, dtree, branch, current_index);
			break;
		case OP_DIV:
			current_index = diff_div(old_tree, dtree, branch, current_index);
			break;
		case OP_POW:
			current_index = diff_pow(old_tree, dtree, branch, current_index);
			break;
		case OP_LN:
			current_index = diff_ln(old_tree, dtree, branch, current_index);
			break;
		case OP_SIN:
			current_index = diff_sin(old_tree, dtree, branch, current_index);
			break;
		case OP_COS:
			current_index = diff_cos(old_tree, dtree, branch, current_index);
			break;
		case OP_SQRT:
			current_index = diff_sqrt(old_tree, dtree, branch, current_index);
			break;
		case OP_DIFF:
			current_index = diff_diff(old_tree, dtree, branch, current_index);
			break;*/
		#include "Operations.h"

		default:
			break;
		}
		break;
	default:
		break;
	}

	return;
}

#undef DEFINE_OPS

int diff_abbreviated_logarithm(Diff_tree *dtree, long long index)
{
	if (!(tree_get_type(dtree, index) == OPERATION) || !(tree_get_operation(dtree, index) == OP_POW))
		return 0;

	long long left_son = tree_left_son(dtree, index);
	long long right_son = tree_right_son(dtree, index);
	long long right_grandson = tree_right_son(dtree, right_son);
	if (!(tree_get_type(dtree, left_son) == NUMBER && (exp(1) - tree_get_number(dtree, left_son)) <= epsilon))
	{
		return 0;
	}

	if (right_son == ABSENT && right_grandson == ABSENT || tree_get_type(dtree, right_grandson) != OPERATION || tree_get_type(dtree, right_son) != OPERATION)
	{
		return 0;
	}

	if (tree_get_operation(dtree, right_grandson) == OP_LN && tree_get_operation(dtree, right_son) == OP_MUL)
	{
		long long right_right_grandson = tree_right_son(dtree, right_grandson);
		if (right_right_grandson == ABSENT)
			return 0;

		tree_remove_knot(dtree, right_grandson, right_right_grandson);
		tree_remove_knot(dtree, index, right_son);
	}
	
	return 1;
}

#define DEFINE_OPS(name, number, tex_name, priority, differentiate, evaluate)\
        case number:\
			evaluate;\
            break;

char diff_roll_up_consts(Diff_tree *dtree, long long index, char *changes)
{
	if (tree_if_lief(dtree, index))
		return dtree->tree[index].type;

	long long left = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	char left_type = diff_roll_up_consts(dtree, left, changes);
	char right_type = diff_roll_up_consts(dtree, right, changes);

	tree_operations curr_op = tree_get_operation(dtree, index);

	if (left_type == NUMBER && curr_op == OP_POW)
	{
		if (diff_abbreviated_logarithm(dtree, index))
			return tree_get_type(dtree, index);
		else
			return OPERATION;
	}

	if (left_type == NUMBER && right_type == NUMBER)
	{
		double value = 0;
		double left_value = dtree->tree[left].number;
		double right_value = dtree->tree[right].number;
		
		switch (curr_op)
		{
		/*case OP_PLUS:
			value = left_value + right_value;
			break;
		case OP_SUB:
			value = left_value - right_value;
			break;
		case OP_MUL:
			value = left_value * right_value;
			break;
		case OP_DIV:
			if (right_value)
				value = left_value / right_value;
			else
				return OPERATION;
			break;
		case OP_LN:
			value = log(right_value);
			break;
		case OP_SIN:
			value = sin(right_value);
			break;
		case OP_COS:
			value = cos(right_value);
			break;
		case OP_SQRT:
			value = sqrt(right_value);
			break;
		case OP_POW:
			break;*/
		#include "Operations.h"

		default:
			break;
		}

		long long index_after = tree_parent(dtree, index);
		tree_clean_branch(dtree, index);
		tree_insert_number(dtree, &index_after, value);

		*changes = 1;

		return NUMBER;
	}
	
	return dtree->tree[index].type;
}

#undef DEFINE_OPS

char diff_left_operations_with_zero(Diff_tree* dtree, long long index)
{
	long long left  = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	switch (dtree->tree[index].operation)
	{
	case OP_PLUS:
		tree_remove_knot(dtree, index, right);
		if (dtree->tree[right].type == VARIABLE)
			return VARIABLE;
		else
			return OPERATION;
		break;
	case OP_MUL:
		tree_remove_knot(dtree, index, left);
		return NUMBER;
		break;
	case OP_DIV:
		tree_remove_knot(dtree, index, left);
		return NUMBER;
		break;
	case OP_POW:
		if (tree_get_type(dtree, right) == NUMBER && tree_get_number(dtree, right) == 0)
		{
			dtree->tree[right].number = 1;
			tree_remove_knot(dtree, index, right);
		}
		else
			tree_remove_knot(dtree, index, left);
		return NUMBER;
		break;
	default:
		break;
	}

	return NOTHING;
}

char diff_right_operations_with_zero(Diff_tree* dtree, long long index)
{
	long long left = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	switch (tree_get_operation(dtree, index))
	{
	case OP_PLUS:
		tree_remove_knot(dtree, index, left);
		return tree_get_type(dtree, left);
		break;
	case OP_MUL:
		tree_remove_knot(dtree, index, right);
		return NUMBER;
		break;
	case OP_POW:
		dtree->tree[right].number = 1;
		tree_remove_knot(dtree, index, right);
		return NUMBER;
		break;
	default:
		break;
	}

	return NOTHING;
}

char diff_left_operations_with_one(Diff_tree* dtree, long long index)
{
	long long left  = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	switch (dtree->tree[index].operation)
	{
	case OP_MUL:
		tree_remove_knot(dtree, index, right);
		return tree_get_type(dtree, right);
		break;
	case OP_POW:
		tree_remove_knot(dtree, index, left);
		return NUMBER;
		break;
	default:
		break;
	}

	return NOTHING;
}

char diff_right_operations_with_one(Diff_tree* dtree, long long index)
{
	long long left = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	switch (dtree->tree[index].operation)
	{
	case OP_MUL:
		tree_remove_knot(dtree, index, left);
		return tree_get_type(dtree, left);
		break;
	case OP_DIV:
		tree_remove_knot(dtree, index, left);
		return tree_get_type(dtree, left);
		break;
	case OP_POW:
		tree_remove_knot(dtree, index, left);
		return tree_get_type(dtree, left);
	case  OP_LN:
		dtree->tree[index].number = 0;
		tree_remove_knot(dtree, index, right);
		return NUMBER;
		break;
	default:
		break;
	}

	return NOTHING;
}

char diff_simplificate_operations(Diff_tree* dtree, long long index, char *changes)
{
	if (tree_if_lief(dtree, index))
	{
		return dtree->tree[index].type;
	}

	long long left  = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	char left_type  = diff_simplificate_operations(dtree, left, changes);
	char right_type = diff_simplificate_operations(dtree, right, changes);
	
	if (left_type == NUMBER || right_type == NUMBER)
	{
		long long value = 0;
		char var = 0;
		char type = NOTHING;
		
		if (tree_get_type(dtree, left) == NUMBER)
		{
			if (dtree->tree[left].number == 0)
				type = diff_left_operations_with_zero(dtree, index);
			else if (dtree->tree[left].number == 1)
				type = diff_left_operations_with_one(dtree, index);
		
			if (type != NOTHING)
			{
				*changes = 1;
				return type;
			}
		}

		if (tree_get_type(dtree, right) == NUMBER)
		{
			if (dtree->tree[right].number == 0)
				type = diff_right_operations_with_zero(dtree, index);
			else if (dtree->tree[right].number == 1)
				type = diff_right_operations_with_one(dtree, index);
		
			if (type != NOTHING)
				*changes = 1;
		}
		
		return type;
	}
	
	return VARIABLE;
}

void diff_simplificate(Diff_tree* dtree)
{
	char rolling_changes = 0;
	char simplif_changes = 0;
	do
	{
		rolling_changes = 0;
		diff_roll_up_consts(dtree, dtree->root_index, &rolling_changes);
		
		if (rolling_changes)
			diff_print_formula_in_tex(dtree, dtree->root_index, 0, PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT, FORMULA);

		simplif_changes = 0;
		diff_simplificate_operations(dtree, dtree->root_index, &simplif_changes);
		
		if (simplif_changes)
			diff_print_formula_in_tex(dtree, dtree->root_index, 0, PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT, FORMULA);
	} while (rolling_changes || simplif_changes);
}
