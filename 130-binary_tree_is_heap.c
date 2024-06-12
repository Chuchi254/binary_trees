#include "binary_trees.h"
#include <stdlib.h>

/**
 * binary_tree_is_complete - Checks if a binary tree is complete
 *
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if the tree is complete, 0 otherwise
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	const binary_tree_t **queue;
	size_t head = 0, tail = 0, size = 1024;
	int found_non_full = 0;

	if (tree == NULL)
		return (0);
	queue = malloc(sizeof(*queue) * size);
	if (queue == NULL)
		return (0);
	queue[tail++] = tree;
	while (head < tail)
	{
		const binary_tree_t *node = queue[head++];

		if (node == NULL)
			found_non_full = 1;
		else
		{
			if (found_non_full)
			{
				free(queue);
				return (0);
			}
			if (tail >= size)
			{
				size *= 2;
				queue = realloc(queue, sizeof(*queue) * size);
				if (queue == NULL)
					return (0);
			}
			queue[tail++] = node->left;
			queue[tail++] = node->right;
		}
	}
	free(queue);
	return (1);
}

/**
 * binary_tree_is_heap_helper - Helper function to check if a tree is
 * a max heap
 *
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if the tree is a max heap, 0 otherwise
 */
int binary_tree_is_heap_helper(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (1);
	if (tree->left != NULL && tree->left->n > tree->n)
		return (0);
	if (tree->right != NULL && tree->right->n > tree->n)
		return (0);
	return (binary_tree_is_heap_helper(tree->left) &&
			binary_tree_is_heap_helper(tree->right));
}

/**
 * binary_tree_is_heap - Checks if a binary tree is a valid Max Binary Heap
 *
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if the tree is a valid Max Binary Heap, 0 otherwise
 */
int binary_tree_is_heap(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (binary_tree_is_complete(tree) &&
			binary_tree_is_heap_helper(tree));
}
