#include "binary_trees.h"
#include <stdlib.h>
/**
 * bst_insert_recursive - Helper function to recursively insert value in a BST
 *
 * @tree: Double pointer to the root node of the BST to insert the value
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure or if value exists
 */
bst_t *bst_insert_recursive(bst_t **tree, int value)
{
	bst_t *new_node = NULL;

	if (*tree == NULL)
	{
		new_node = binary_tree_node(NULL, value);
		if (new_node == NULL)
			return (NULL);
		*tree = new_node;
		return (new_node);
	}
	if (value < (*tree)->n)
	{
		if ((*tree)->left != NULL)
			return (bst_insert_recursive(&(*tree)->left, value));
		new_node = binary_tree_node(*tree, value);
		if (new_node == NULL)
			return (NULL);
		(*tree)->left = new_node;
		return (new_node);
	}
	else if (value > (*tree)->n)
	{
		if ((*tree)->right != NULL)
			return (bst_insert_recursive(&(*tree)->right, value));
		new_node = binary_tree_node(*tree, value);
		if (new_node == NULL)
			return (NULL);
		(*tree)->right = new_node;
		return (new_node);
	}
	return (NULL);
}

/**
 * bst_insert - Inserts a value in a Binary Search Tree
 *
 * @tree: Doule pointer to the root node of the BST to insert the value
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure or if value exists
 */
bst_t *bst_insert(bst_t **tree, int value)
{
	if (tree == NULL)
		return (NULL);
	return (bst_insert_recursive(tree, value));
}
