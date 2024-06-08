#include <stdlib.h>
#include "binary_trees.h"

/**
 * binary_tree_height - Measures the height of a binary tree
 *
 * @tree: Pointer to the root node of the tree to measure the height
 *
 * Return: Height of the tree, or 0 if tree is NULL
 */
size_t binary_tree_height(const binary_tree_t *tree)
{
	size_t left_height, right_height;

	if (tree == NULL)
		return (0);

	left_height = binary_tree_height(tree->left);
	right_height = binary_tree_height(tree->right);

	return ((left_height > right_height ? left_height : right_height) + 1);
}

/**
 * binary_tree_levelorder_helper - Helper function to traverse a binary tree
 * using level-order traversal
 *
 * @tree: Pointer to the root node of the tree to traverse
 * @func: Pointer to a function to call for each node
 * @level: Current level in the binary tree
 */
void binary_tree_levelorder_helper(
		const binary_tree_t *tree, void (*func)(int), size_t level)
{
	if (tree == NULL)
		return;

	if (level == 1)
	{
		func(tree->n);
	}
	else if (level > 1)
	{
		binary_tree_levelorder_helper(tree->left, func, level - 1);
		binary_tree_levelorder_helper(tree->right, func, level - 1);
	}
}

/**
 * binary_tree_levelorder - Goes through a binary tree
 * using level-order traversal
 *
 * @tree: Pointer to the root node of the tree to traverse
 * @func: Pointer to a function to call for each node
 */
void binary_tree_levelorder(const binary_tree_t *tree, void (*func)(int))
{
	size_t height, level;

	if (tree == NULL || func == NULL)
		return;

	height = binary_tree_height(tree);
	for (level = 1; level <= height; level++)
	{
		binary_tree_levelorder_helper(tree, func, level);
	}
}
