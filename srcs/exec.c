/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:12:15 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/17 12:44:14 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_prompt(t_data *data)
{
	int		i;
	t_lex	*curr_cmd;

	curr_cmd = data->lex;
	ft_get_first_command(data, &i);
	while (++i < data->lex_size)
	{
		
	}
	curr_cmd = data->lex->next;
}
