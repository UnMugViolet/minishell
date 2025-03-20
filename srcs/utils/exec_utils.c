/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:24:45 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/20 16:59:08 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_exec_tree(t_exec *exec)
{
	t_exec	*tmp;

	while (exec)
	{
		tmp = exec->next;
		ft_free_array_str(exec->cmd);
		free(exec);
		exec = tmp;
	}
}

t_exec	*ft_exec_new(char **cmd, char *path, size_t type)
{
	t_exec	*new_element;

	new_element = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!new_element)
		return (NULL);
	new_element->cmd = cmd;
	new_element->type = type;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_exec_add_back(t_exec **exec, t_exec *new)
{
	if (!exec || !new)
		return ;
	if (!*exec)
		*exec = new;
	else
	{
		while ((*exec)->next)
			exec = (*exec)->next;
		(*exec)->next = new;
		new->prev = *exec;
	}
}

void	ft_get_first_command(t_data *data, size_t *i)
{
	*i = -1;
	if (data->lex->type == WORD)
		return ;
	else if (data->lex->type == DOUBLE_LEFT_BRACKET)
		*i = 1;
	else
		ft_printf("Symbol found, TODO implement\n");
}
