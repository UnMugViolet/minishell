/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:24:44 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/24 12:44:32 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_exec_conditionaly(t_data *data, char *cmd, size_t type)
{
	if (!data->exec)
		data->exec = ft_exec_new(ft_split(cmd, ' '), NULL, type);
	else
		ft_exec_add_back(&data->exec, ft_exec_new(ft_split(cmd, ' '), NULL, type));
	free(cmd);
}

void	ft_get_heredocs(t_data *data)
{
	t_lex	*tmp;
	char	*cmd;

	cmd = NULL;
	tmp = data->lex;
	while (tmp)
	{
		if (tmp && tmp->type == DOUBLE_LEFT_BRACKET)
		{
			cmd = ft_strjoin(tmp->content, " ");
			if (tmp->next && tmp->next->content)
			{
				cmd = ft_strjoin_free(cmd, tmp->next->content);
				ft_lex_del_content(tmp->next);
			}
			ft_lex_del_content(tmp);
			ft_create_exec_conditionaly(data, cmd, DOUBLE_LEFT_BRACKET);
		}
		tmp = tmp->next;
	}
}

void	ft_get_commands(t_data *data)
{
	t_lex	*tmp;
	char	*cmd;

	cmd = NULL;
	tmp = data->lex;
	while (tmp && (tmp->type == WORD || tmp->type == 0))
	{
		cmd = ft_strjoin_free(cmd, " ");
		cmd = ft_strjoin_free(cmd, tmp->content);
		ft_lex_del_content(tmp);
		tmp = tmp->next;
	}
	ft_create_exec_conditionaly(data, cmd, WORD);
}
