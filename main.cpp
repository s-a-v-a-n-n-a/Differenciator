#include "diff_differentiator.h"

int main()
{
	Diff_tree* dtree = tree_read_from_file(DEFAULT_FILE_NAME);

	diff_print_tree_expression(dtree, dtree->root_index);
	printf("\n");

	Diff_tree* new_tree = tree_init(10);
	diff(dtree, new_tree, dtree->root_index, ABSENT);

	diff_print_tree_expression(new_tree, new_tree->root_index);
	printf("\n");

	diff_simplificate(new_tree);
	//printf("finished\n");

	diff_print_tree_expression(new_tree, new_tree->root_index);
	printf("\n");
	
	/*printf("\n");
	for (long long i = 0; i < new_tree->size; i++)
	{
		diff_print_tree_node(new_tree, i);
	}
	printf("\n");*/

	tree_delete(dtree);
	tree_delete(new_tree);
	return 0;
}