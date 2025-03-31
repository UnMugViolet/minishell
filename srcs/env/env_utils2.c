/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:33:42 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/27 13:13:21 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Returns the adress of the `variable` string inside the `env` array.
	Returns `NULL` if not found.
	@param t_data*data
	@param char*variable
	@return char *
*/
char	*ft_get_env_var_adress(t_data *data, char *variable)
{
	int		i;
	size_t	size;

	i = -1;
	size = ft_strlen(variable);
	while (data->env[++i])
		if (ft_strncmp(data->env[i], variable, size) == 0
			&& data->env[i][size] == '=')
			return (data->env[i]);
	return (NULL);
}

void	ft_update_last_exit_value(t_data *data, int value)
{
	free(data->last_exit_value);
	data->last_exit_value = ft_itoa(value);
}
