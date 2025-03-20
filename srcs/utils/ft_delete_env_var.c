/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguinio <yguinio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:02:18 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/20 09:34:38 by yguinio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Deletes the variable `variable` from the `env` array
	in the `t_data` struct.
	@param t_data*data
	@param char*variable
	@return void
*/
void	ft_delete_env_var(t_data *data, char *variable)
{
	size_t const	variable_len = ft_strlen(variable);
	int				i;
	int				j;
	char			**new_env;

	i = 0;
	if (!ft_get_env_var_adress(data, variable))
		return ;
	while (data->env[i])
		i++;
	new_env = (char **)ft_calloc(sizeof(char *), i);
	i = -1;
	j = 0;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], variable, variable_len)
			&& data->env[i][variable_len] == '=')
			continue ;
		new_env[j] = ft_strdup(data->env[i]);
		j++;
	}
	new_env[j] = NULL;
	data->env = new_env;
}
