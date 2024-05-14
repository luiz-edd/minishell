

#include "minishell.h"

//mudar de lugar a declaracao dessa funcao
char	*ft_strdup_calloc(const char *s)
{
	size_t	len;
	size_t	i;
	char	*p;

	len = ft_strlen(s);
	p = (char *)ft_calloc(len + 1, 1);
	if (p == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

// char	**get_environ(void)
// {
// 	static char	**env;

// 	return (env);
// }

void	init_environ(void)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (__environ[i])
		i++;
	env_copy = ft_calloc(i + 1, sizeof(char *));
	i = -1;
	while (__environ[++i])
		env_copy[i] = ft_strdup_calloc(__environ[i]);
	env_copy[i] = NULL;
	__environ = env_copy;
}

void	free_env(void)
{
	int i;

	i = -1;
	while (__environ[++i])
		free(__environ[i]);
	free(__environ);
}