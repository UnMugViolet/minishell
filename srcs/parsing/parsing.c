/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:08:53 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/04/02 10:42:09 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_exec(t_data *data)
{
	ft_get_pipes(data);
	ft_get_heredocs(data);
	ft_get_infiles(data);
	ft_get_outfiles(data);
	ft_get_commands(data);
}

/*
	Check the inputs from the user, exit if the value entered is incorrect
	@param t_data*data
	@return void
*/
void	ft_parse_prompt(t_data *data)
{
	ft_create_exec(data);
	ft_replace_env_variable(data);
}
