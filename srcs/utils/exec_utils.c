/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:24:45 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/26 15:23:48 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_exec(t_exec *exec)
{
	t_exec	*tmp;
	int		i;

	tmp = exec;
	i = 0;
	if (!tmp)
		ft_printf("EXEC IS EMPTY\n");
	else
	{
		ft_printf("EXEC ARRAY:\n");
		while (tmp)
		{
			ft_printf("Chain nbr: %i\n", ++i);
			ft_print_array_str_fd(tmp->cmd, 1);
			ft_printf("Full Command: %s\n", tmp->full_cmd ? tmp->full_cmd : "NULL");
			ft_printf("Infile: %s\n", (tmp->infile
					&& ft_strlen(tmp->infile) > 0) ? tmp->infile : "NULL");
			ft_printf("Outfile: %s\n\n", (tmp->outfile
					&& ft_strlen(tmp->outfile) > 0) ? tmp->outfile : "NULL");
			tmp = tmp->next;
		}
	}
}
