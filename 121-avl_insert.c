#include "binary_trees.h"
#include <stdlib.h>

/**
 * avl_insert_helper - Helper function to insert a value in an AVL Tree
 *
 * @tree: Double pointer to root node of the AVL tree for inserting value
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
avl_t *avl_insert_helper(avl_t **tree, int value)
{
	avl_t *node = NULL;

	if (tree == NULL)
		return (NULL);

	if (*tree == NULL)
	{
		*tree = (avl_t *)binary_tree_node(NULL, value);
		return (*tree);
	}

	if (value < (*tree)->n)
	{
		node = avl_insert(&(*tree)->left, value);
		if (node == NULL)
			return (NULL);
		(*tree)->left->parent = *tree;
	}
	else if (value > (*tree)->n)
	{
		node = avl_insert_helper(&(*tree)->right, value);
		if (node == NULL)
			return (NULL);
		(*tree)->right->parent = *tree;
	}
	else
	{
		return (NULL);
	}
	return (node);
}

/**
 * avl_insert - Inserts a value in an AVL Tree
 *
 * @tree: Double pointer to the root node of AVL tree for inserting value
 *
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *node, *current;
	int balance;

	node = avl_insert_helper(tree, value);
	if (node == NULL)
		return (NULL);
	current = node->parent;
	while (current != NULL)
	{
		balance = binary_tree_balance((const binary_tree_t *)current);
		if (balance > 1 && value < current->left->n)
			return ((avl_t *)binary_tree_rotate_right((binary_tree_t *)current));

		if (balance < -1 && value > current->right->n)
			return ((avl_t *)binary_tree_rotate_left(
						(binary_tree_t *)current));

		if (balance > 1 && value > current->left->n)
		{
			current->left = (avl_t *)binary_tree_rotate_left(
					(binary_tree_t *)current->left);
			return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)current));
		}

		if (balance < -1 && value < current->right->n)
		{
			current->right = (avl_t *)binary_tree_rotate_right(
					(binary_tree_t *)current->right);
			return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)current));
		}
		current = current->parent;
	}
	return (node);
}
