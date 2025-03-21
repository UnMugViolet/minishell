/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:12:15 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/21 09:46:32 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_prompt(t_data *data)
{
	size_t	i;
	t_lex	*curr_cmd;

	curr_cmd = data->lex;
	ft_get_first_command(data, &i);
	printf("curr_cmd->content: %s, I size: %zu, is an env var %i\n",
		curr_cmd->content, i, ft_is_env_var(curr_cmd->content));
	curr_cmd = data->lex->next;
}
