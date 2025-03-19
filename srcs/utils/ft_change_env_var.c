/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguinio <yguinio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:33:42 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/19 17:07:14 by yguinio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Replace the value of the env variable `variable` by the string `new_val`
	@param t_data*data
	@param char*variable
	@param char*new_val
	@return void	
*/
void	ft_change_env_var(t_data *data, char *variable, char *new_val)
{
	int				i;
	size_t const	var_size = ft_strlen(variable);

	i = -1;
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], variable, var_size)
			&& data->env[i][var_size] == '=')
		{
			free(data->env[i]);
			data->env[i] = ft_strjoin_free(ft_strjoin(variable, "="), new_val);
			return ;
		}
	}
}
