

#include "minishell.h"

static void	format_and_print(const char *env_var)
{
	char	*name;
	char	*equal;
	char	*value;
	char	*copy;

	copy = ft_strdup(env_var);
	equal = ft_strchr(copy, '=');
	if (!equal)
		printf("declare -x %s\n", copy);
	else
	{
		*equal = '\0';
		name = copy;
		value = equal + 1;
		printf("declare -x %s=\"%s\"\n", name, value);
	}
	// free(copy);
}

static int	print_small(char **env, size_t env_size, unsigned char *printed)
{
	int	small_pos;

	small_pos = -1;
	while (env_size-- > 0)
	{
		if (printed[env_size])
			continue ;
		if (small_pos == -1)
			small_pos = env_size;
		else
		{
			if (ft_strcmp(env[small_pos], env[env_size]) > 0)
				small_pos = env_size;
		}
	}
	if (small_pos != -1)
	{
		format_and_print(env[small_pos]);
		printed[small_pos]++;
		return (1);
	}
	return (0);
}

void	print_environ_sorted(void)
{
	size_t size;
	unsigned char *printed;

	size = 0;
	while (__environ[size])
		size++;
	printed = ft_calloc(size + 1, sizeof(unsigned char));
	while (print_small(__environ, size, printed))
		;
	free(printed);
}