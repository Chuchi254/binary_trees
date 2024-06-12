#include "binary_trees.h"
#include <stdlib.h>

/**
 * balance_avl_tree - Balances the AVL tree after insertion
 *
 * @tree: Double pointer to the root node of the AVL tree
 * @value: Value that was inserted
 *
 * Return: Pointer to the new root node of the AVL tree
 */
avl_t *balance_avl_tree(avl_t **tree, int value)
{
	int balance;

	balance = binary_tree_balance((const binary_tree_t *)(*tree));

	if (balance > 1 && value < (*tree)->left->n)
		return ((avl_t *)binary_tree_rotate_right((binary_tree_t *)*tree));

	if (balance < -1 && value > (*tree)->right->n)
		return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)*tree));

	if (balance > 1 && value > (*tree)->left->n)
	{
		(*tree)->left = (avl_t *)binary_tree_rotate_left(
				(binary_tree_t *)(*tree)->left);
		return ((avl_t *)binary_tree_rotate_right((binary_tree_t *)*tree));
	}

	if (balance < -1 && value < (*tree)->right->n)
	{
		(*tree)->right = (avl_t *)binary_tree_rotate_right(
				(binary_tree_t *)(*tree)->right);
		return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)*tree));
	}
	return (*tree);
}

/**
 * avl_insert_helper - Helprr function to insert a value in an AVL Tre
 *
 * @tree: Double pointer to the root node of the AVL
 * tree for inserting the value
 * @value: Value to store in the node to be inserted
 * @new_node: Pointer to store the newly created node
 *
 * Return: Pointer to the new root node of the AVL tree
 */
avl_t *avl_insert_helper(avl_t **tree, int value, avl_t **new_node)
{
	if (*tree == NULL)
	{
		*new_node = (avl_t *)binary_tree_node(NULL, value);
		return (*new_node);
	}

	if (value < (*tree)->n)
	{
		(*tree)->left = avl_insert_helper(&(*tree)->left, value, new_node);
		if ((*tree)->left)
			(*tree)->left->parent = *tree;
	}

	else if (value > (*tree)->n)
	{
		(*tree)->right = avl_insert_helper(&(*tree)->right, value, new_node);
		if ((*tree)->right)
			(*tree)->right->parent = *tree;
	}
	else
	{
		return (*tree);
	}
	return (balance_avl_tree(tree, value));
}

/**
 * avl_insert - inserts a value in an AVL Tree
 *
 * @tree: Double pointer to the root node of the AVL
 * tree for inserting the value
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
avl_t *avl_insert(avl_t **tree, int value)
{
	avl_t *new_node = NULL;

	if (tree == NULL)
		return (NULL);

	*tree = avl_insert_helper(tree, value, &new_node);
	return (new_node);
}
