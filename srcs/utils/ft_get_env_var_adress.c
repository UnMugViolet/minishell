/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_env_var_adress.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguinio <yguinio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 09:28:59 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/20 09:32:40 by yguinio          ###   ########.fr       */
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
	int				i;
	size_t const	size = ft_strlen(variable);

	i = -1;
	while (data->env[++i])
		if (ft_strncmp(data->env[i], variable, size) == 0
			&& data->env[i][size] == '=')
			return (data->env[i]);
	return (NULL);
}
