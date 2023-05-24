#include "shell.h"

/**
 * _memcpy - copy n bytes of memory from src to dest
 * @dest: pointer to destination
 * @src: pointer to source
 * @n: number of bytes to be copied
 *
 * Return: pointer to destination
 */
void *_memcpy(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;
	size_t i = 0;

	if (src == NULL || n == 0)
		return (dest);

	if (dest == NULL)
		return (NULL);

	for (i = 0 ; i < n ; i++)
		d[i] = s[i];

	return (dest);
}

/**
 * _realloc - reallocate memeory to a new size
 * @ptr: pointer to memory to be allocated
 * @size: new size
 *
 * Return: pointer to new memory, or NULL on error
 */
void *_realloc(void *ptr, size_t size, size_t cpy_size)
{
	void *new_ptr;

	if (ptr == NULL && size == 0)
		return (NULL);
	else if (ptr == NULL && size != 0)
	{
		new_ptr = malloc(size);
		return (new_ptr);
	}
	else if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(size);
	printf("size = %lu\n", size);
	printf("address = %p\n", new_ptr);
	if (new_ptr == NULL)
		return (NULL);

	if (cpy_size > size)
		cpy_size = size;

	_memcpy(new_ptr, ptr, cpy_size);
	free(ptr);

	return (new_ptr);
}
