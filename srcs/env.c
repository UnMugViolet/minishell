/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguinio <yguinio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 16:29:05 by fureimu           #+#    #+#             */
/*   Updated: 2025/03/17 17:29:11 by yguinio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_var_name(char *str)
{
	char	*res;
	int		size;

	size = 0;
	str = ft_strchr(str, '$');
	if (!str)
		return (NULL);
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
*/
char	*ft_get_associated_env_value(char **env, char *variable)
{
	int		i;
	size_t	size;
	char	*res;

	i = 0;
	if (!env || !variable)
		return (ft_strdup(""));
	size = ft_strlen(variable) - 1;
	while (env[i])
	{
		if (ft_strncmp(env[i], variable + 1, size) == 0 && env[i][size] == '=')
		{
			res = ft_strdup(env[i] + size + 1);
			return (res);
		}
		i++;
	}
	res = ft_strdup("");
	return (res);
}

/*
	Browses the `t_lex` list and replaces the `$` type element by their value.
	Empty string if no env variable matches
	@param t_data* data
*/
void	ft_replace_env_variable(t_data *data)
{
	char	*temp;
	t_lex	*start;

	start = data->lex;
	if (!ft_strncmp(data->prompt, "exit", 5))
		ft_exit_clean(data);
	while (start)
	{
		if (start->type == WORD)
		{
			if ((start->content)[0] == SGL_QT)
			{
				temp = start->content;
				start->content = ft_strtrim(start->content, "\'");
				free(temp);
				start = start->next;
				continue ;
			}
			start->content = ft_str_substitute(start->content, data->env);
		start = start->next;
		}
	}
}
