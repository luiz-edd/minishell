

#include "minishell.h"

// int is_key_exist(char *key)
// {
// 	int i;
// 	i = 0;

// 	while(__environ[i])
// 	{

// 	}
// }

static void	ft_set_env(char *new_str, char *key, char *content)
{
	char	*env_var;
	char	*aux;

	env_var = getenv(key);
	printf("getenv return: %s\n", env_var);
	// verifica se a key existe
	// se existir e o contet nao for null,
	// atulizar o valor da env_var com o novo valor new_str
	// se nao, adicionar arg na __env
	if (env_var && content != NULL)
	{
		aux = env_var;
		env_var = new_str;
		free(aux);
	}
	else
		(add_to_env(new_str));
	// else if(is_key_exist(key))
}

// export key=content
int	execute_export(t_token *cmd)
{
	int i;
	char **args;
	char *equal_sign;
	char *key;
	int status;

	i = 0;
	status = 0;
	args = get_cmd_and_args(cmd);
	if (!args[1])
		print_environ_sorted();
	while (args[++i])
	{
		if (!is_valid_identifier(args[i]) && status++)
			continue ;
		key = get_key(args[i]);
		equal_sign = ft_strchr(args[i], '=');
		if (equal_sign)
			ft_set_env(args[i], key, equal_sign + 1);
		else
			ft_set_env(args[i], key, NULL);
	}
	return (!!status);
}