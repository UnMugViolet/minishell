/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 09:41:17 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/31 10:03:01 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_get_pipes(t_data *data)
{
	t_lex	*tmp;
	char	*cmd;

	cmd = NULL;
	tmp = data->lex;
	while (tmp)
	{
		if (tmp && tmp->type == PIPE)
		{
			ft_get_commands(data);
			cmd = ft_strdup(tmp->content);
			ft_lex_del_content(tmp);
			ft_create_exec_conditionaly(data, cmd, PIPE);
		}
		tmp = tmp->next;
	}
}
