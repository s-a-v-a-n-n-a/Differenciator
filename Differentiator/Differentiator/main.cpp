#include "diff_differentiator.h"

void work_with_expression();

int main()
{
	srand(time(0));
	work_with_expression();
	
	return 0;
}

void work_with_expression()
{
	Diff_tree* dtree = tree_read_from_file(DEFAULT_FILE_NAME);

	diff_simplificate(dtree);

	diff_print_formula_in_tex(dtree, dtree->root_index, NOT_END, FIRST_DEPR, FORMULA);

	Diff_tree* new_tree = tree_init(10);
	diff(dtree, new_tree, dtree->root_index, ABSENT);

	diff_print_formula_in_tex(new_tree, new_tree->root_index, NOT_END, SIMPLIFIER, FORMULA);
	diff_simplificate(new_tree);
	tree_dump(new_tree, TREE_OK, DESTRUCTION);

	//diff_print_tree_expression(stdout, new_tree, new_tree->root_index);
	//printf("\n");

	/*printf("\n");
	for (long long i = 0; i < new_tree->size; i++)
	{
		diff_print_tree_node(new_tree, i);
	}
	printf("\n");*/
	diff_print_formula_in_tex(new_tree, new_tree->root_index, NOT_END, FINAL_ANSWER, FORMULA);
	diff_print_formula_in_tex(new_tree, new_tree->root_index, END, GRAPHICS, GRAPH);

	tree_delete(dtree);
	tree_delete(new_tree);
}