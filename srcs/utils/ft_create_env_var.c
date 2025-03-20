/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_env_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:15:02 by yguinio           #+#    #+#             */
/*   Updated: 2025/03/20 11:01:17 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_all(char **new_env, char *var_check)
{
	ft_free_array_str(new_env);
	free(var_check);
}

static bool	ft_check_env_var_format(char *str)
{
	int	i;

	i = 0;
	while (ft_isalnum(str[i]))
		i++;
	if (str[i] == '=')
		return (true);
	return (false);
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
	if (!ft_check_env_var_format(str))
		return ;
	var_check = ft_substr(str, 0, ft_strchr(str, '=') - str);
	if (ft_get_env_var_adress(data, var_check))
	{
		ft_change_env_var(data, var_check, str + ft_strlen(var_check) + 1);
		free(var_check);
		return ;
	}
	while (data->env[i])
		i++;
	new_env = (char **)ft_calloc(sizeof(char *), i + 2);
	if (!new_env)
		return ;
	i = -1;
	while (data->env[++i])
		new_env[i] = ft_strdup(data->env[i]);
	new_env[i++] = ft_strdup(str);
	ft_free_all(data->env, var_check);
	data->env = new_env;
}
