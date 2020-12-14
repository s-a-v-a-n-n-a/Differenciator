#define DO_DIFFERENTIATION    diff(dtree, dtree, dtree->tree[current_index].left_son, current_index);

#define COPY_LEFT   tree_copy_branch(old_tree, dtree, old_tree->tree[branch].left_son, current_index);
#define COPY_RIGHT  tree_copy_branch(old_tree, dtree, old_tree->tree[branch].right_son, current_index);

#define DIFFERENTIATE_VALUE(value)\
	diff_create_new_lief(dtree, NUMBER, value, current_index);\

#define DIFFERENTIATE_PLUS\
	diff_create_new_lief(dtree, OPERATION, OP_PLUS, current_index);\

#define DIFFERENTIATE_MINUS\
	diff_create_new_lief(dtree, OPERATION, OP_SUB, current_index);\

#define DIFFERNTIATE_MUL\
	diff_create_new_lief(dtree, OPERATION, OP_MUL, current_index);\

#define DIFFERENTIATE_DIV\
	diff_create_new_lief(dtree, OPERATION, OP_DIV, current_index);\

#define DIFFERENTIATE_LOG\
	diff_create_new_lief(dtree, OPERATION, OP_LN, current_index);\

#define DIFFERENTIATE_POW\
	diff_create_new_lief(dtree, OPERATION, OP_POW, current_index);\

#define DIFFERENTIATE_SIN\
	diff_create_new_lief(dtree, OPERATION, OP_SIN, current_index);\

#define DIFFERENTIATE_COS\
	diff_create_new_lief(dtree, OPERATION, OP_COS, current_index);\

#define DIFFERENTIATE_SQRT\
	diff_create_new_lief(dtree, OPERATION, OP_SQRT, current_index);\

#define DIFFERENTIATE_DIFF\
	diff_create_new_lief(dtree, OPERATION, OP_DIFF, current_index);\

#define DIFFERENTIATE_LEFT\
	current_index = DIFFERENTIATE_DIFF;\
	COPY_LEFT;\
	DIFFERENTIATE_VALUE(ABSENT); \
	diff_print_formula_in_tex(dtree, current_index, 0, PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT, FORMULA);\
	diff(dtree, dtree, current_index, current_index);\
	current_index = tree_parent(dtree, current_index);\

#define DIFFERENTIATE_RIGHT\
	current_index = DIFFERENTIATE_DIFF;\
	COPY_RIGHT;\
	DIFFERENTIATE_VALUE(ABSENT);\
	diff_print_formula_in_tex(dtree, current_index, 0, PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT, FORMULA);\
	diff(dtree, dtree, current_index, current_index);\
	current_index = tree_parent(dtree, current_index);\

DEFINE_OPS(OP_PLUS, 0, "+", 5,
{
	current_index = DIFFERENTIATE_PLUS;
	DIFFERENTIATE_LEFT;
	DIFFERENTIATE_RIGHT;
},

{
	value = left_value + right_value;
})

DEFINE_OPS(OP_SUB, 1, "-", 4,
{
	current_index = DIFFERENTIATE_MINUS;
	DIFFERENTIATE_LEFT;
	DIFFERENTIATE_RIGHT;
},

{
	value = left_value - right_value;
})

DEFINE_OPS(OP_MUL, 2, " \\cdot ", 3,
{
	current_index = DIFFERENTIATE_PLUS;

	current_index = DIFFERNTIATE_MUL;
	DIFFERENTIATE_LEFT;
	COPY_RIGHT;

	current_index = tree_parent(dtree, current_index);

	current_index = DIFFERNTIATE_MUL;
	DIFFERENTIATE_RIGHT;
	COPY_LEFT;
},

{
	value = left_value * right_value;
})

DEFINE_OPS(OP_DIV, 3, "\\frac", 3,
{
	current_index = DIFFERENTIATE_DIV;

	current_index = DIFFERENTIATE_MINUS;

	current_index = DIFFERNTIATE_MUL;
	DIFFERENTIATE_LEFT;
	COPY_RIGHT;

	current_index = tree_go_up(dtree, current_index, ONE_STEP);

	current_index = DIFFERNTIATE_MUL;
	DIFFERENTIATE_RIGHT;
	COPY_LEFT;

	current_index = tree_go_up(dtree, current_index, TWO_STEPS);

	current_index = DIFFERNTIATE_MUL;
	COPY_RIGHT;
	COPY_RIGHT;
},

{
	value = left_value / right_value;
})

DEFINE_OPS(OP_POW, 4, "^", 2,
{
	current_index = DIFFERNTIATE_MUL;

	current_index = DIFFERENTIATE_POW;
	DIFFERENTIATE_VALUE(exp(1));

	current_index = tree_go_up(dtree, current_index, ONE_STEP);

	current_index = DIFFERNTIATE_MUL;
	COPY_RIGHT;
	current_index = DIFFERENTIATE_LOG;
	current_index = DIFFERENTIATE_VALUE(ABSENT);

	current_index = tree_go_up(dtree, current_index, ONE_STEP);
	COPY_LEFT;

	current_index = tree_go_up(dtree, current_index, THREE_STEPS);

	current_index = DIFFERENTIATE_PLUS;
	current_index = DIFFERNTIATE_MUL;
	
	DIFFERENTIATE_RIGHT;

	current_index = DIFFERENTIATE_LOG;
	current_index = DIFFERENTIATE_VALUE(ABSENT);
	
	current_index = tree_go_up(dtree, current_index, ONE_STEP);
	COPY_LEFT;

	current_index = tree_go_up(dtree, current_index, TWO_STEPS);

	current_index = DIFFERNTIATE_MUL;
	current_index = DIFFERENTIATE_DIV;

	DIFFERENTIATE_LEFT;

	COPY_LEFT;

	current_index = tree_go_up(dtree, current_index, ONE_STEP);
	COPY_RIGHT;
},

{
	value = pow(left_value, right_value);
})


DEFINE_OPS(OP_SIN, 5, "sin", 2,
{
	current_index = DIFFERNTIATE_MUL;

	DIFFERENTIATE_RIGHT;
	//current_index = tree_go_up(dtree, current_index, ONE_STEP);

	current_index = DIFFERENTIATE_COS;
	current_index = DIFFERENTIATE_VALUE(ABSENT);
	
	current_index = tree_go_up(dtree, current_index, ONE_STEP);
	COPY_RIGHT;

	tree_dump(dtree, TREE_OK, DESTRUCTION);
},

{
	value = sin(right_value);
})

DEFINE_OPS(OP_COS, 6, "cos", 2,
{
	current_index = DIFFERNTIATE_MUL;

	DIFFERENTIATE_RIGHT;
	//current_index = tree_go_up(dtree, current_index, TWO_STEPS);

	current_index = DIFFERNTIATE_MUL;
	current_index = DIFFERENTIATE_VALUE(ABSENT);
	
	current_index = tree_go_up(dtree, current_index, ONE_STEP);
	current_index = DIFFERENTIATE_SIN;
	
	current_index = DIFFERENTIATE_VALUE(ABSENT);
	current_index = tree_go_up(dtree, current_index, ONE_STEP);
	COPY_RIGHT;
},

{
	value = cos(right_value);
})


DEFINE_OPS(OP_LN, 7, "log", 2,
{
	current_index = DIFFERENTIATE_DIV;
	current_index = DIFFERENTIATE_VALUE(1);
	COPY_RIGHT;
},

{
	value = log(right_value);
})

DEFINE_OPS(OP_SQRT, 8, " \\sqrt ", 2,
{
	current_index = DIFFERNTIATE_MUL;
	current_index = DIFFERENTIATE_VALUE(0.5);
	
	current_index = tree_go_up(dtree, current_index, ONE_STEP);
	DIFFERENTIATE_RIGHT;
},

{
	value = sqrt(right_value);
})

DEFINE_OPS(OP_DIFF, 9, "'", 1,
{
	tree_clean_branch(dtree, tree_right_son(dtree, current_index));
	DO_DIFFERENTIATION;
	tree_remove_knot(dtree, current_index, tree_right_son(dtree, current_index));
	current_index = tree_right_son(dtree, current_index);

	if (!tree_if_lief(dtree, current_index))
		diff_print_formula_in_tex(dtree, current_index, 0, PROHIBITED_FOR_RANDOM_PHRASES_AMOUNT, FORMULA);
},

{})