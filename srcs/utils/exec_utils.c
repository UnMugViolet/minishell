/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:24:45 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/21 09:30:34 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*ft_exec_new(char **cmd, char *path, size_t type)
{
	t_exec	*new_element;

	new_element = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!new_element)
		return (NULL);
	new_element->cmd = cmd;
	new_element->type = type;
	new_element->path = path;
	new_element->infile = 0;
	new_element->outfile = 0;
	new_element->next = NULL;
	new_element->prev = NULL;
	return (new_element);
}

void	ft_exec_add_back(t_exec **exec, t_exec *new)
{
	t_exec	*current;

	if (!exec || !new)
		return ;
	if (!*exec)
		*exec = new;
	else
	{
		current = *exec;
		while (current->next)
			current = current->next;
		current->next = new;
		new->prev = current;
	}
}

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
