

#include "libft.h"

char	*ft_strndup(char *s, int n)
{
	char *ptr;
	int i;

	i = 0;
	while (s[i])
		i++;
	if (n < i)
		i = n;
	ptr = ft_dalloc(i + 1, sizeof(ptr));
	if (!ptr)
		return (NULL);
	i = 0;
	while (s && *s && i < n)
		ptr[i++] = *s++;
	ptr[i] = '\0';
	return (ptr);
}