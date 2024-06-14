#include "binary_trees.h"
#include <stdlib.h>

/**
 * heap_to_sorted_array - Converts a Binary Max Heap to a sorted
 * array of intergers
 *
 * @heap: Pointer to the root node of the heap to convert
 * @size: Address to store the size of the array
 *
 * Return: Pointer to the sorted array, or NULL on failure
 */
int *heapt_to_sorted_array(heap_t *heap, size_t *size)
{
	int *array;
	size_t heap_size, i;

	if (heap == NULL || size == NULL)
		return (NULL);

	heap_size = binary_tree_size(heap);
	*size = heap_size;
	array = malloc(heap_size * sizeof(int));

	if (array == NULL)
		return (NULL);

	for (i = 0; i < heap_size; i++)
		array[i] = heap_extract(&heap);
	return (array);
}
