/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:24:34 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/20 12:43:35 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Increment the value of the `SHLVL` variable in the `env` array
	@param t_data*data
	@return void
*/
static void	ft_inc_shell_lvl(t_data *data)
{
	int		i;
	char	*new_value;

	i = -1;
	while (data->env[++i])
		if (!ft_strncmp(data->env[i], "SHLVL=", 6))
			break ;
	if (!data->env[i])
		return ;
	new_value = ft_itoa(ft_atoi(data->env[i] + 6) + 1);
	if (!new_value)
		new_value = ft_strdup("1");
	free(data->env[i]);
	data->env[i] = ft_strjoin("SHLVL=", new_value);
	free(new_value);
}

/*
	Sets the default values of the `env` array in the `data` struct
	@param t_data*data
	@return void
*/
static void	ft_default_env(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	data->env = (char **)ft_calloc(sizeof(char *), 4);
	data->env[0] = ft_strjoin("PWD=", cwd);
	data->env[1] = ft_strdup(DEF_SHLVL);
	data->env[2] = ft_strdup(DEF_LAST_ARG);
	free(cwd);
}

/*
	Fetches the `$PATH` value from the `env` array.
	If no `$PATH` is found, sets the value to `DEF_PATH`.
	@param t_data*data
	@return char *
*/
static char	**ft_get_path_from_env(t_data *data)
{
	int		i;
	char	**paths;

	i = 0;
	if (*data->env)
	{
		while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5))
			i++;
		if (data->env[i] && !ft_strncmp(data->env[i], "PATH=", 5))
			paths = ft_split(data->env[i] + 5, ':');
	}
	if (!data->env[i])
		paths = ft_split(DEF_PATH, ':');
	i = -1;
	while (paths[++i])
		paths[i] = ft_strjoin_free(paths[i], "/");
	return (paths);
}

/*
	Initialize the `data` struct.
	@param t_data*data
	@param char**env
	@return void
*/
void	ft_init_data_struct(t_data *data, char **env)
{
	data->env = ft_str_array_dup(env);
	if (!data->env)
		ft_default_env(data);
	ft_inc_shell_lvl(data);
	data->paths = ft_get_path_from_env(data);
	data->prompt = NULL;
	data->lex = NULL;
	data->metachar = ft_split(METACHAR, ' ');
	data->last_exit_value = ft_strdup("0");
}
