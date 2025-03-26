/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:08:53 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/26 11:40:18 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_exec_tree(t_data *data)
{
	ft_get_heredocs(data);
	ft_get_infiles(data);
	ft_get_outfile(data);
	ft_get_commands(data);
	// ft_get_pipes(data);
	// ft_get_infiles(data);
}

/*
	Check the inputs from the user, exit if the value entered is incorrect
	@param t_data*data
	@return void
*/
void	ft_parse_prompt(t_data *data)
{
	ft_create_exec_tree(data);
	ft_replace_env_variable(data);
	ft_exec_builtins(data, data->exec->cmd);
}
