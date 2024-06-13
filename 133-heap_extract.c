#include "binary_trees.h"
#include <stdlib.h>

/**
 * binary_tree_node - Creates a binary tree node
 *
 * @parent: Pointer to the parent node
 * @value: Valueto put in the new node
 *
 * Return: Pointer to the new node, or NULL on failure
 */
binary_tree_t *binary_tree_node(binary_tree_t *parent, int value)
{
	binary_tree_t *new_node;

	new_node = malloc(sizeof(binary_tree_t));
	if (new_node == NULL)
		return (NULL);

	new_node->n = value;
	new_node->parent = parent;
	new_node->left = NULL;
	new_node->right = NULL;

	return (new_node);
}
/**
 * swap_values - Swaps the values of two nodes
 *
 * @a: Pointer to the first node
 * @b: Pointer to the second node
 */
void swap_values(heap_t *a, heap_t *b)
{
	int temp = a->n;

	a->n = b->n;
	b->n = temp;
}

/**
 * get_last_node - Retrieves the last node in a level-order traversal
 *
 * @root: Pointer to the root node of the tree
 *
 * Return: Pointer to the last node
 */
heap_t *get_last_node(heap_t *root)
{
	size_t size = binary_tree_size(root);
	size_t path = size;
	heap_t *node = root;

	while (path > 1)
	{
		if (path & 1)
			node = node->right;
		else
			node = node->left;
		path >>= 1;
	}
	return (node);
}

/**
 * bubble_down - Restores the heap property by bubbling down
 *
 * @node: Pointer to the node to bubble down
 */
void bubble_down(heap_t *node)
{
	heap_t *largest = node;

	while (node)
	{
		if (node->left && node->left->n > largest->n)
			largest = node->left;

		if (node->right && node->right->n > largest->n)
			largest = node->right;

		if (largest != node)
		{
			swap_values(largest, node);
			node = largest;
		}
		else
			break;
	}
}

/**
 * heap_extract - Extracts the root node of a Max Binary Heap
 *
 * @root: Double pointer to the root node of the heap
 *
 * Return: The value stored in the root node, or 0 if the function fails
 */
int heap_extract(heap_t **root)
{
	int value;
	heap_t *last_node;

	if (root == NULL || *root == NULL)
		return (0);

	value = (*root)->n;

	if ((*root)->left == NULL && (*root)->right == NULL)
	{
		free(*root);
		*root = NULL;
		return (value);
	}
	last_node = get_last_node(*root);

	if (last_node->parent)
	{
		if (last_node->parent->right == last_node)
			last_node->parent->right = NULL;
		else
			last_node->parent->left = NULL;
	}

	(*root)->n = last_node->n;
	free(last_node);

	bubble_down(*root);
	return (value);
}
