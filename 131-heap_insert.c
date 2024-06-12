#include "binary_trees.h"
#include <stdlib.h>

/**
 * binary_tree_size - Measures the size of a binary tree
 *
 * @tree: Pointer to the root node of the tree to measure the size
 *
 * Return: Size of the tree, or 0 if tree is NULL
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
	if (tree == NULL)
		return (0);
	return ((1 + binary_tree_size(tree->left) + binary_tree_size(tree->right)));
}

/**
 * find_parent_for_insert - Finds the parent node for the next insertion
 *
 * @root: Pointer to the root node of th tree
 *
 * Return: Pointer to the parent node for the next insertion
 */
heap_t *find_parent_for_insert(heap_t *root)
{
	size_t size = binary_tree_size(root);
	size_t path = size + 1;
	heap_t *parent = root;
	heap_t *next;

	while (path > 1)
	{
		next = (path & 1) ? parent->left : parent->right;
		if (path > 3)
			parent = next;
		path >>= 1;
	}
	return (parent);
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
 * bubble_up - Restores the heap property by bubbling up
 *
 * @node: Pointer to the newly inserted node
 *
 * Return: Pointer to the node after bubbling up
 */
heap_t *bubble_up(heap_t *node)
{
	while (node->parent && node->n > node->parent->n)
	{
		swap_values(node, node->parent);
		node = node->parent;
	}
	return (node);
}

/**
 * heap_insert - Inserts a value in Binary Max Heap
 *
 * @root: Double pointer to the root node of the Heap to insert the value
 * @value: Value to store in the node to e inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
	heap_t *new_node;

	if (root == NULL)
		return (NULL);
	if (*root == NULL)
	{
		*root = (heap_t *)binary_tree_node(NULL, value);
		return (*root);
	}
	heap_t *parent;

	parent = find_parent_for_insert(*root);
	if (parent->left == NULL)
		parent->left = (heap_t *)binary_tree_node(parent, value);
	else
		parent->right = (heap_t *)binary_tree_node(parent, value);
	new_node = (parent->left &&
			parent->left->n == value) ? parent->left : parent->right;
	return (bubble_up(new_node));
}
