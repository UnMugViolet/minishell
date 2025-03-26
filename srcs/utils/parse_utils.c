/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:24:44 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/26 15:24:05 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_create_exec_conditionaly(t_data *data, char *cmd, size_t type)
{
	char	**cmd_array;

	cmd_array = ft_split_strset(cmd, data->metachar);
	if (!cmd_array)
	{
		ft_exit_error(data, "Error: malloc exec failed, \
			cannot fetch commands.");
		return ;
	}
	if (!data->exec)
		data->exec = ft_exec_new(cmd_array, ft_get_path_for_cmd(data, cmd),
				type);
	else
		ft_exec_add_back(&data->exec, ft_exec_new(cmd_array,
				ft_get_path_for_cmd(data, cmd), type));
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

void	ft_get_infiles(t_data *data)
{
	t_lex	*tmp;
	char	*cmd;

	cmd = NULL;
	tmp = data->lex;
	while (tmp)
	{
		if (tmp && tmp->type == LEFT_BRACKET)
		{
			cmd = ft_strjoin(tmp->content, " ");
			if (tmp->next && tmp->next->content)
			{
				cmd = ft_strjoin_free(cmd, tmp->next->content);
				ft_lex_del_content(tmp->next);
			}
			ft_lex_del_content(tmp);
			ft_create_exec_conditionaly(data, cmd, LEFT_BRACKET);
		}
		tmp = tmp->next;
	}
}

void	ft_get_outfile(t_data *data)
{
	t_lex	*tmp;
	char	*cmd;

	cmd = NULL;
	tmp = data->lex;
	while (tmp)
	{
		if (tmp && (tmp->type == RIGHT_BRACKET
				|| tmp->type == DOUBLE_RIGHT_BRACKET))
		{
			cmd = ft_strjoin(tmp->content, " ");
			if (tmp->next && tmp->next->content)
			{
				cmd = ft_strjoin_free(cmd, tmp->next->content);
				ft_lex_del_content(tmp->next);
			}
			ft_lex_del_content(tmp);
			ft_create_exec_conditionaly(data, cmd, LEFT_BRACKET);
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
		cmd = ft_strjoin_free(cmd, tmp->content);
		if (tmp->next && (tmp->type == WORD || tmp->type == 0))
			cmd = ft_strjoin_free(cmd, " ");
		ft_lex_del_content(tmp);
		tmp = tmp->next;
	}
	ft_create_exec_conditionaly(data, cmd, WORD);
}
