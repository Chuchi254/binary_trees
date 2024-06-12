#include "binary_trees.h"
#include <stdlib.h>

/**
 * balance_avl_tree_after_removal - Balances the AVL tree after removal
 *
 * @tree: Double pointer to the root node of the AVL tree
 *
 * Return: Pointer to the new root node of the AVL tree
 */
avl_t *balance_avl_tree_after_removal(avl_t **tree)
{
	int balance;

	balance = binary_tree_balance((const binary_tree_t *)(*tree));

	if (balance > 1 && binary_tree_balance((*tree)->left) >= 0)
		return ((avl_t *)binary_tree_rotate_right((binary_tree_t *)*tree));

	if (balance > 1 && binary_tree_balance((*tree)->left) < 0)
	{
		(*tree)->left = (avl_t *)binary_tree_rotate_left(
				(binary_tree_t *)(*tree)->left);
		return ((avl_t *)binary_tree_rotate_right((binary_tree_t *)*tree));
	}

	if (balance < -1 && binary_tree_balance((*tree)->right) <= 0)
		return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)*tree));

	if (balance < -1 && binary_tree_balance((*tree)->right) > 0)
	{
		(*tree)->right = (avl_t *)binary_tree_rotate_right(
				(binary_tree_t *)(*tree)->right);
		return ((avl_t *)binary_tree_rotate_left((binary_tree_t *)*tree));
	}
	return (*tree);
}

/**
 * find_min_node - Finds hte node with the minimum value in a tree
 *
 * @node: Pointer to the root node of the tree
 *
 * Return: Pointer to the ndoe with the minimum value
 */
avl_t *find_min_node(avl_t *node)
{
	avl_t *current = node;

	while (current && current->left != NULL)
		current = current->left;

	return (current);
}

/**
 * avl_remove_helper - Helper function to remove a node from an AVL tree
 *
 * @root: Pointer to the root node of the tree for removing a node
 * @value: Value to remove in the tree
 *
 * Return: Pointer to the new root node of the tree after removing
 */
avl_t *avl_remove_helper(avl_t *root, int value)
{
	avl_t *temp;

	if (root == NULL)
		return (NULL);

	if (value < root->n)
		root->left = avl_remove_helper(root->left, value);
	else if (value > root->n)
		root->right = avl_remove_helper(root->right, value);
	else
	{
		if (root->left == NULL || root->right == NULL)
		{
			temp = root->left ? root->left : root->right;
			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
			{
				*root = *temp;
			}
			free(temp);
		}
		else
		{
			temp = find_min_node(root->right);
			root->n = temp->n;
			root->right = avl_remove_helper(root->right, temp->n);
		}
	}
	if (root == NULL)
		return (root);
	return (balance_avl_tree_after_removal(&root));
}

/**
 * avl_remove - Removes a node from an AVL tree
 *
 * @root: Pointer o the root node of the tree for removing a node
 * @value: Value to remove in the tree
 *
 * Return: Pointer to the new root node of the tree after removing
 * and rebalancing
 */
avl_t *avl_remove(avl_t *root, int value)
{
	return (avl_remove_helper(root, value));
}
