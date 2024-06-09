#include "binary_trees.h"
#include <stdlib.h>
/**
 * bst_min_value_node - Find the noe with the minimum value in a BST
 *
 * @node: Pointer to the root node of the tree to search
 *
 * Return: Pointer to the node with the minimum value
 */
bst_t *bst_min_value_node(bst_t *node)
{
	bst_t *current = node;

	while (current && current->left != NULL)
		current = current->left;
	return (current);
}

/**
 * bst_remove - Removes a node from a Binary Search Tree
 *
 * @root: Pointer to the root node of the tree where you will remove a node
 * @value: Value to remove in the tree
 *
 * Return: Pointer to new root node of tree after removing the desired value
 */
bst_t *bst_remove(bst_t *root, int value)
{
	if (root == NULL)
		return (NULL);
	if (value < root->n)
		root->left = bst_remove(root->left, value);
	else if (value > root->n)
		root->right = bst_remove(root->right, value);
	else
	{
		if (root->left == NULL)
		{
			bst_t *temp = root->right;

			if (root->parent && root->parent->left == root)
				root->parent->left = temp;
			if (root->parent && root->parent->right == root)
				root->parent->right = temp;
			if (temp)
				temp->parent = root->parent;
			free(root);
			return (temp);
		}
		else if (root->right == NULL)
		{
			bst_t *temp = root->left;

			if (root->parent && root->parent->left == root)
				root->parent->left = temp;
			if (root->parent && root->parent->right == root)
				root->parent->right = temp;
			if (temp)
				temp->parent = root->parent;
			free(root);
			return (temp);
		}
		bst_t *temp = bst_min_value_node(root->right);

		root->n = temp->n;
		root->right = bst_remove(root->right, temp->n);
	}
	return (root);
}
