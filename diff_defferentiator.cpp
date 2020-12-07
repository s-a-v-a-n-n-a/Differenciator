#include "diff_differentiator.h"

#define differenciate_left  diff(old_tree, dtree, old_tree->tree[branch].left_son, current_index);
#define differenciate_right diff(old_tree, dtree, old_tree->tree[branch].right_son, current_index);
#define copy_left           tree_copy_branch(old_tree, dtree, old_tree->tree[branch].left_son, current_index);
#define copy_right          tree_copy_branch(old_tree, dtree, old_tree->tree[branch].right_son, current_index);

#define differenciate_value(value)\
	diff_create_new_lief(dtree, NUMBER, value, ABSENT, ABSENT, current_index);\

#define differenciate_plus\
	diff_create_new_lief(dtree, OPERATION, OP_PLUS, ABSENT, ABSENT, current_index);\

#define differenciate_minus\
	diff_create_new_lief(dtree, OPERATION, OP_SUB, ABSENT, ABSENT, current_index);\

#define differenciate_mul\
	diff_create_new_lief(dtree, OPERATION, OP_MUL, ABSENT, ABSENT, current_index);\

#define differenciate_div\
	diff_create_new_lief(dtree, OPERATION, OP_DIV, ABSENT, ABSENT, current_index);\

#define differenciate_log\
	diff_create_new_lief(dtree, OPERATION, OP_LN, ABSENT, ABSENT, current_index);\

#define differenciate_pow\
	diff_create_new_lief(dtree, OPERATION, OP_POW, ABSENT, ABSENT, current_index);\

#define differenciate_sin\
	diff_create_new_lief(dtree, OPERATION, OP_SIN, ABSENT, ABSENT, current_index);\

#define differenciate_cos\
	diff_create_new_lief(dtree, OPERATION, OP_COS, ABSENT, ABSENT, current_index);\

/*long long diff_get_next_index(Diff_tree *dtree, const long long index, Stack *went_elements)
{
	long long next_index = 0;
	
	double last_index = 0;
	double index_before_last = 0;
	stack_back(&went_elements, &last_index);
	stack_earlier_back(&went_elements, &index_before_last);

	long long right_son = tree_right_son(dtree, index);
	long long left_son = tree_left_son(dtree, index);

	if (left_son != ABSENT && last_index != left_son && index_before_last != left_son)
	{
		next_index = left_son;
	}
	else if (right_son != ABSENT && last_index != right_son) //если правого сына и уложат в стек, то после правого точно
	{
		next_index = right_son;
	}
	else
	{
		stack_pop(&went_elements, &last_index);
		stack_pop(&went_elements, &index_before_last);
		stack_push(&went_elements, index);

		next_index = tree_parent(dtree, index);
	}

	return next_index;
}*/

void diff_print_introduction(FILE *out)
{
	fprintf(out, "\\documentclass{article}\n");
	fprintf(out, "\\usepackage[T2A]{fontenc}\n");
	fprintf(out, "\\usepackage[utf8x]{inputenc}\n");
	fprintf(out, "\\usepackage[russian]{babel}\n");
	fprintf(out, "\\usepackage{amsmath}\n");
	fprintf(out, "\\textheight=30cm\n");
	fprintf(out, "\\textwidth=17cm\n");
	fprintf(out, "\\oddsidemargin=-30pt\n");
	fprintf(out, "\\topmargin=-2cm\n");
	fprintf(out, "\\parskip=5pt\n");

	fprintf(out, "\\begin{document}\n");
}

void diff_print_phrase(FILE* out)
{
	int phrase_number = rand() % PHRASES_AMOUNT;
	fprintf(out, "%s", phrase_bank[phrase_number]);
}

/*void diff_print_new(FILE* out, Diff_tree* dtree, Diff_tree* old_tre, long long index_to_copy, long long index_where_to_copy, char branch, char will_diff, long long index)
{
	if (index == index_where_to_copy)
	{
		if (branch == RIGHT && index == tree_right_son(dtree, tree_parent(dtree, index)))
		{
			diff_print_copy(old_tree, index_to_copy);
			return;
		}
		else if (branch == LEFT && index == tree_left_son(dtree, tree_parent(dtree, index)))
		{
			diff_print_copy(old_tree, index_to_copy);
			return;
		}
	}
}*/

void diff_print_formula(FILE* out, Diff_tree *dtree, Diff_tree* old_tre, long long index_to_copy, long long index_where_to_copy)
{
	fprintf(out, "$$");

	diff_print_new(out, dtree, old_tre, index_to_copy, index_where_to_copy);

	fprintf(out, "$$");
}

void diff_print_conclusion(FILE* out)
{
	fprintf(out, "\\end{document}\n");
}

void diff_print_formula_in_tex(Diff_tree* dtree, Diff_tree* old_tre, long long index_to_copy, long long index_where_to_copy)
{
	static long long opening = 0;
	char mode[] = "ab";
	if (!opening)
		mode[0] = 'w';
	FILE* out = fopen(DEFAULT_TEX_FILE_NAME, mode);
	
	diff_print_introduction(out);

	srand(time(0));
	diff_print_phrase(out);
	//diff_print_formula(out, dtree, old_tree, index_to_copy);
	diff_print_conclusion(out);

	fclose(out);

	opening++;
}

long long diff_create_new_lief(Diff_tree *dtree, const char type, double future_value, long long left_index, long long right_index, long long parent_index)
{
	long long new_index = 0;
	switch (type)
	{
		case NUMBER:
			tree_insert_number(dtree, &parent_index, future_value);
			break;
		case OPERATION:
			tree_insert_operation(dtree, &parent_index, (tree_operations)future_value);
			//dtree->tree[parent_index].left_son = left_index;
			//dtree->tree[parent_index].right_son = right_index;
			break;
		default:
			tree_insert_number(dtree, &parent_index, future_value);
			break;
	}
	return parent_index;
}

/*long long diff(Diff_tree *old_tree, Diff_tree *dtree, const long long branch)
{
	long long current_index_for_old = old_tree->root_index;
	long long current_index = ABSENT;
	Stack* went_elements = stack_new(old_tree->size);
	
	//выглядит хреново, надо что-то с этим сделать
	stack_push(&went_elements, ABSENT);
	stack_push(&went_elements, ABSENT);
	stack_push(&went_elements, ABSENT);

	long long division_counter = 0;
	char made_diffs_for_division = 0;
	
	for (long long counter = 0; counter < old_tree->size; counter++)
	{
		switch (old_tree->tree[branch].type)
		{
			case NUMBER:
				diff_create_new_lief(dtree, NUMBER, 0, ABSENT, ABSENT, current_index);
				break;
			case VARIABLE:
				diff_create_new_lief(dtree, NUMBER, 1, ABSENT, ABSENT, current_index);
				break;
			case OPERATION:
				switch (old_tree->tree[branch].operation)
				{
					case '+':
						if (division_counter && !made_diffs_for_division)
						{

						}
						break;
					case '-':

						break;
					case '*':
						current_index = diff_create_new_lief(dtree, OPERATION, '+', ABSENT, ABSENT, current_index);
						current_index = diff_create_new_lief(dtree, OPERATION, '+', ABSENT, ABSENT, current_index);
						break;
					case '/':
						//мать моя родная я не люблю дифференциировать дроби...
						current_index = diff_create_new_lief(dtree, OPERATION, '+', ABSENT, ABSENT, current_index);
						division_counter++;
						//continue;
						//tree_copy_branch(old_tree, dtree, current_index_for_old, current_index);
						//current_index = 
						break;
					default:
						break;
				}

			break;
		default:
			break;
		}

		current_index_for_old = diff_get_next_index(old_tree, current_index_for_old, went_elements);//!!!!!!!!!!!!!!current_index надо тоже обновлять
	}
	stack_destruct(&went_elements);
}*/

void diff(Diff_tree* old_tree, Diff_tree* dtree, const long long branch, long long current_index)
{
	//printf("%d\n", current_index);
	switch (old_tree->tree[branch].type)
	{
	case NUMBER:
		current_index = differenciate_value(NUMBER)
		//	printf("number\n");
		break;
	case VARIABLE:
		current_index = differenciate_value(VARIABLE)
		//	printf("var\n");
		break;
	case OPERATION:
		switch (old_tree->tree[branch].operation)
		{
		case OP_PLUS:
			current_index = differenciate_plus
			differenciate_left
			differenciate_right
			
			break;
		case OP_SUB:
			current_index = differenciate_minus
			differenciate_left
			differenciate_right
			
			break;
		case OP_MUL:
			current_index = differenciate_plus//0
			//printf("curr %lld\n", current_index);

			current_index = differenciate_mul//1
				//printf("curr %lld\n", current_index);
			differenciate_left
			copy_right

			current_index = tree_parent(dtree, current_index);
			//printf("curr %lld\n", current_index);
			current_index = differenciate_mul
			//printf("curr %lld\n", current_index);
			differenciate_right
			copy_left

			break;
		case OP_DIV:
			current_index = differenciate_div//вниз

			current_index = differenciate_minus//влево
			
			current_index = differenciate_mul//ещё левее
			differenciate_left
			copy_right

			current_index = tree_parent(dtree, current_index);
			
			current_index = differenciate_mul
			differenciate_right
			copy_left

			current_index = tree_parent(dtree, tree_parent(dtree, current_index));

			current_index = differenciate_mul
			copy_right
			copy_right

			break;
		case OP_POW:
			current_index = differenciate_mul

			current_index = differenciate_pow
			current_index = differenciate_value(exp(1))
			
			current_index = tree_parent(dtree, current_index);

			current_index = differenciate_mul
			copy_right
			current_index = differenciate_log
			current_index = differenciate_value(ABSENT)

			current_index = tree_parent(dtree, current_index);
			copy_left

			current_index = tree_parent(dtree, current_index);
			current_index = tree_parent(dtree, current_index);
			current_index = tree_parent(dtree, current_index);

			current_index = differenciate_plus
			current_index = differenciate_mul
			differenciate_right
			
			current_index = differenciate_log
			current_index = differenciate_value(ABSENT)

			current_index = tree_parent(dtree, current_index);
			copy_left

			current_index = tree_parent(dtree, current_index);
			current_index = tree_parent(dtree, current_index);

			current_index = differenciate_mul
			current_index = differenciate_div
			differenciate_left
			copy_left

			current_index = tree_parent(dtree, current_index);
			copy_right

			break;
		case OP_LN:
			current_index = differenciate_div;

			differenciate_value(1);
			copy_right;

			break;
		case OP_SIN:
			current_index = differenciate_mul

			current_index = differenciate_cos
			differenciate_value(ABSENT);
			copy_right

			current_index = tree_parent(dtree, current_index);
			differenciate_right

			break;
		case OP_COS:
			current_index = differenciate_mul

			current_index = differenciate_mul
			differenciate_value(ABSENT);
			current_index = differenciate_sin
			differenciate_value(ABSENT);
			copy_right

			current_index = tree_parent(dtree, current_index);
			current_index = tree_parent(dtree, current_index);
			differenciate_right

			break;			
		default:
			break;
		}

		break;
	default:
		break;
	}

	//diff_print_formula_in_tex();

	return;
}

char diff_roll_up_consts(Diff_tree* dtree, long long index, char *changes)
{
	if (tree_if_lief(dtree, index))
		return dtree->tree[index].type;

	long long left = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	char left_type = diff_roll_up_consts(dtree, left, changes);
	char right_type = diff_roll_up_consts(dtree, right, changes);

	if (left_type == NUMBER && right_type == NUMBER)
	{
		double value = 0;
		double left_value = dtree->tree[left].number;
		double right_value = dtree->tree[right].number;
		//printf("%d %lg %lg\n", dtree->tree[index].operation, dtree->tree[left].number, dtree->tree[right].number);
		switch (dtree->tree[index].operation)
		{
		case OP_PLUS:
			value = left_value + right_value;
			*changes = 1;
			//printf("value plus %lg\n", value);
			break;
		case OP_SUB:
			value = left_value - right_value;
			*changes = 1;
			//printf("value sub %lg\n", value);
			break;
		case OP_MUL:
			value = left_value * right_value;
			*changes = 1;
			//printf("value mul %lg\n", value);
			break;
		case OP_DIV:
			if (right_value)
			{
				value = left_value / right_value;
				*changes = 1;
			}
			break;
		case OP_LN:
			value = log(right_value);
			break;
		case OP_POW:
			return OPERATION;
			break;
		default:
			return OPERATION;
			break;
		}

		long long index_after = tree_parent(dtree, index);
		tree_clean_branch(dtree, index);
		tree_insert_number(dtree, &index_after, value);

		return NUMBER;
	}
	
	return dtree->tree[index].type;
}

char diff_left_operations_with_zero(Diff_tree* dtree, long long index)
{
	long long left = tree_left_son(dtree, index);
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
		if (dtree->tree[right].type == NUMBER && dtree->tree[right].number == 0)
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

	switch (dtree->tree[index].operation)
	{
	case OP_PLUS:
		tree_remove_knot(dtree, index, left);
		if (dtree->tree[left].type == VARIABLE)
			return VARIABLE;
		else
			return OPERATION;
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
		if (dtree->tree[right].type == VARIABLE)
			return VARIABLE;
		else
			return OPERATION;
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
		if (dtree->tree[left].type == VARIABLE)
			return VARIABLE;
		else
			return OPERATION;
		break;
	case OP_DIV:
		tree_remove_knot(dtree, index, left);
		if (dtree->tree[left].type == VARIABLE)
			return VARIABLE;
		else
			return OPERATION;
		break;
	case OP_POW:
		tree_remove_knot(dtree, index, left);
		if (dtree->tree[left].type == VARIABLE)
			return VARIABLE;
		else if (dtree->tree[left].type == OPERATION)
			return OPERATION;
		else
			return NUMBER;
	default:
		break;
	}

	return NOTHING;
}

char diff_simplificate_operations(Diff_tree* dtree, long long index, char *changes)
{
	if (tree_if_lief(dtree, index))
		return dtree->tree[index].type;

	long long left  = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	char left_type  = diff_simplificate_operations(dtree, left, changes);
	char right_type = diff_simplificate_operations(dtree, right, changes);

	if (left_type == NUMBER || right_type == NUMBER)
	{
		long long value = 0;
		char var = 0;
		char type = NOTHING;
		
		if (dtree->tree[left].type == NUMBER)
		{
			if (dtree->tree[left].number == 0)
			{
				type = diff_left_operations_with_zero(dtree, index);
			}
			else if (dtree->tree[left].number == 1)
			{
				type = diff_left_operations_with_one(dtree, index);
			}
		}

		if (type != NOTHING)
		{
			*changes = 1;
			
			return type;
		}

		if (dtree->tree[right].type == NUMBER)
		{
			//printf("%lg\n", dtree->tree[right].number);
			if (dtree->tree[right].number == 0)
			{
				type = diff_right_operations_with_zero(dtree, index);
			}
			else if (dtree->tree[right].number == 1)
			{
				type = diff_right_operations_with_one(dtree, index);
			}
		}

		if (type != NOTHING)
		{
			*changes = 1;
		}
		
		return type;
	}
	
	return VARIABLE;
}

void diff_simplificate(Diff_tree* dtree)
{
	char changes = 0;
	do
	{
		changes = 0;
		diff_roll_up_consts(dtree, dtree->root_index, &changes);
		diff_print_tree_expression(stdout, dtree, dtree->root_index);
		printf("\n");
		diff_simplificate_operations(dtree, dtree->root_index, &changes);
		diff_print_tree_expression(stdout, dtree, dtree->root_index);
		printf("\n");
	} while (changes);
}

void diff_print_tree_node(FILE *out, Diff_tree* dtree, long long index)
{
	if (dtree->tree[index].type == NUMBER)
	{
		long long parent = tree_parent(dtree, index);
		if (dtree->tree[parent].operation == OP_LN && index == tree_left_son(dtree, parent))
			;
		else
			fprintf(out, "%lg", dtree->tree[index].number);
	}
	else if (dtree->tree[index].type == VARIABLE)
		fprintf(out, "%c", dtree->tree[index].variable);
	else
		fprintf(out, "%s", tree_operations_texts[(int)(dtree->tree[index].operation)]);
		//printf("%d", dtree->tree[index].operation);
}

void diff_print_tree_expression(FILE *out, Diff_tree* dtree, long long index)
{
	//printf("%lld\n", index);
	if (tree_if_lief(dtree, index))
	{
		diff_print_tree_node(out, dtree, index);
		return;
	}

	long long left = tree_left_son(dtree, index);
	long long right = tree_right_son(dtree, index);

	if (left != ABSENT)
	{
		if (dtree->tree[left].type == OPERATION)
		{
			tree_operations current_op = dtree->tree[index].operation;
			tree_operations left_op = dtree->tree[left].operation;
			if (tree_priorities[current_op] < tree_priorities[left_op] || ((current_op == left_op) && (current_op == OP_SUB)))
			{
				fprintf(out, "(");
				diff_print_tree_expression(out, dtree, left);
				fprintf(out, ")");
			}
			else 
				diff_print_tree_expression(out, dtree, left);
		}
		else
			diff_print_tree_expression(out, dtree, left);
	}

	diff_print_tree_node(out, dtree, index);

	if (right != ABSENT)
	{
		if (dtree->tree[right].type == OPERATION)
		{
			tree_operations current_op = dtree->tree[index].operation;
			tree_operations right_op = dtree->tree[right].operation;
			if (tree_priorities[current_op] < tree_priorities[right_op] || ((current_op == right_op) && (current_op == OP_SUB)))
			{
				fprintf(out, ")");
				diff_print_tree_expression(out, dtree, right);
				fprintf(out, ")");
			}
			else
				diff_print_tree_expression(out, dtree, right);
		}
		else
			diff_print_tree_expression(out, dtree, right);
	}
}