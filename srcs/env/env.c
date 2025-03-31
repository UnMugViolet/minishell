/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:29:05 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/26 10:30:08 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Returns the name of the first `$variable` in the string `str`
	`NULL` if no `$variable` is found
	@param char*str
	@return char *
*/
char	*ft_get_env_var_name(char *str)
{
	char	*res;
	int		size;

	size = 0;
	str = ft_strchr(str, '$');
	if (!str)
		return (NULL);
	str++;
	if (*str == '?')
		return (ft_strdup("?"));
	if (*str == '_')
		return (ft_strdup("_"));
	while (*str && ft_isalnum(*str))
	{
		size++;
		str++;
	}
	res = (char *)ft_calloc(sizeof(char), size + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, str - size, size + 1);
	return (res);
}

/*
	Returns the value of the `variable` if found in the `env` array.
	@param char** env
	@param char* variable
	@return char *
*/
char	*ft_get_associated_env_value(t_data *data, char *variable)
{
	int		i;
	size_t	size;

	i = 0;
	if (!data->env || !variable)
		return (ft_strdup(""));
	if (!(*variable))
		return (ft_strdup("$"));
	size = ft_strlen(variable);
	if (!ft_strncmp(variable, "?", 2))
		return (ft_strdup(data->last_exit_value));
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], variable, size) == 0
			&& data->env[i][size] == '=')
			return (ft_strdup(data->env[i] + size + 1));
		i++;
	}
	return (ft_strdup(""));
}

/*
	Browses the `t_lex` list and replaces the `$` type element by their value.
	Empty string if no env variable matches
	@param t_data* data
	@return void
*/
void	ft_replace_env_variable(t_data *data)
{
	char	**cmd;
	char	*temp;
	int		i;

	i = 0;
	cmd = data->exec->cmd;
	while (cmd[i])
	{
		if (cmd[i][0] == SGL_QT)
		{
			temp = cmd[i];
			cmd[i] = ft_strtrim(cmd[i], "\'");
			free(temp);
			i++;
			continue ;
		}
		temp = ft_str_substitute(cmd[i], data);
		cmd[i] = ft_strtrim(temp, "\"");
		free(temp);
		i++;
	}
}
