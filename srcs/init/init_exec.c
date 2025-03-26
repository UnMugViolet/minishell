/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:35:30 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/26 15:19:39 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*ft_exec_new(char **cmd, char *full_cmd, size_t type)
{
	t_exec	*new_element;

	new_element = (t_exec *)ft_calloc(1, sizeof(t_exec));
	if (!new_element)
		return (NULL);
	new_element->cmd = cmd;
	new_element->type = type;
	new_element->full_cmd = full_cmd;
	new_element->infile = ft_strdup("");
	new_element->outfile = ft_strdup("");
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

void	ft_free_exec(t_exec *exec)
{
    t_exec	*tmp;

    while (exec)
    {
        tmp = exec->next;
		ft_free_array_str(exec->cmd);
        if (exec->full_cmd)
            free(exec->full_cmd);
        if (exec->infile)
            free(exec->infile);
        if (exec->outfile)
            free(exec->outfile);
        free(exec);
        exec = tmp;
    }
}
