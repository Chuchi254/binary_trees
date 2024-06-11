#include "binary_trees.h"
#include <limits.h>
#include <stdlib.h>

/**
 * is_bst_helper - Helper function to check if a binary tree is a BST
 *
 * @tree: Pointer to the root node of tree to check
 * @min: Minimum value allowed for the current node
 * @max: Maximum value allowed for the current node
 *
 * Return: 1 if the tree is a valid BST, otherwise 0
 */
int is_bst_helper(const binary_tree_t *tree, int min, int max)
{
	if (tree == NULL)
		return (1);

	if (tree->n <= min || tree->n >= max)
		return (0);
	return ((is_bst_helper(tree->left, min, tree->n) &&
				is_bst_helper(tree->right, tree->n, max)));
}

/**
 * binary_tree_is_bst - Checks if a binary tree is a valid Binary Search Tree
 *
 * @tree: Pointer to the root node fo the tree to check
 *
 * Return: 1 if the tree is a valid BST, otherwise 0
 */
int binary_tree_is_bst(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return (is_bst_helper(tree, INT_MIN, INT_MAX));
}

/**
 * binary_tree_height - Measures the height of a binary tree
 *
 * @tree: Pointer to the root node of the tree to measure the height
 *
 * Return: height of the reee, or 0 if the tree is NULL
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
 * binary_tree_is_avl_helper - Helper function to check if a tree is an AVL
 *
 * @tree: Pointer to the root node of the tree to check
 * @height: Pointer to store the height of the tree
 *
 * Return: 1 if the tree is a valid AVL tree, otherwise 0
 */
int binary_tree_is_avl_helper(const binary_tree_t *tree, int *height)
{
	int left_height = 0, right_height = 0;

	if (tree == NULL)
	{
		*height = 0;
		return (1);
	}
	if (!binary_tree_is_avl_helper(tree->left, &left_height) ||
			!binary_tree_is_avl_helper(tree->right, &right_height))
	return (0);

	*height = (left_height > right_height ? left_height : right_height) + 1;

	if (abs(left_height - right_height) > 1)
		return (0);
	return (1);
}

/**
 * binary_tree_is_avl - Checks if a binary tree is a valid AVL tree
 *
 * @tree: Pointer to the root node of the tree to check
 *
 * Return: 1 if the tree is a valid AVL tree, otherwise 0
 */
int binary_tree_is_avl(const binary_tree_t *tree)
{
	int height = 0;

	if (tree == NULL)
		return (0);

	if (!binary_tree_is_bst(tree))
		return (0);
	return (binary_tree_is_avl_helper(tree, &height));
}
