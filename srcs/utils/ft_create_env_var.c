/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguinio <yguinio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:15:02 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/19 18:06:27 by yguinio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env_var_adress(t_data *data, char *variable)
{
	int				i;
	size_t const	size = ft_strlen(variable);
	
	i = -1;
	while (data->env[++i])
	if (ft_strncmp(data->env[i], variable, size) == 0
			&& data->env[i][size] == '=')
			return (data->env[i]);
	return (NULL);
}

/*
	Add the new variable and its value contained in `str` to the `env` array
	in the `t_data` struct.
	@param t_data*data
	@param char*str
	@return void
*/
void	ft_create_env_var(t_data *data, char *str)
{
	int		i;
	char	**new_env;
	char	*var_check;

	i = 0;
	var_check = ft_substr(str, 0, ft_strchr(str, '=') - str);
	if (ft_get_env_var_adress(data, var_check))
	{
		ft_change_env_var(data, var_check, str + ft_strlen(var_check) + 1);
		return ;
	}
	while (data->env[i])
		i++;
	new_env = (char **)ft_calloc(sizeof(char *), i + 2);
	i = -1;
	while (data->env[++i])
		new_env[i] = ft_strdup(data->env[i]);
	new_env[i++] = ft_strdup(str);
	new_env[i] = NULL;
	free(data->env);
	data->env = new_env;
}
