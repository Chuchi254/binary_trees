#include <stdlib.h>
#include "binary_trees.h"

/**
 * binary_tree_is_complete - Checks if abinary tree is complete
 *
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if the treee is complete, otherwise 0
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	binary_tree_t **queue;
	int front = 0, rear = 0, found_null = 0;

	if (tree == NULL)
		return (0);

	queue = malloc(sizeof(binary_tree_t *) * 1024);

	if (queue == NULL)
		return (0);

	queue[rear++] = (binary_tree_t *)tree;

	while (front < rear)
	{
		binary_tree_t *current = queue[front++];

		if (current == NULL)
		{
			found_null = 1;
		}
		else
		{
			if (found_null)
			{
				free(queue);
				return (0);
			}
			queue[rear++] = current->left;
			queue[rear++] = current->right;
		}
	}
	free(queue);
	return (1);
}
