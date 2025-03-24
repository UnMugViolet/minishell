/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fureimu <fureimu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:24:45 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/24 16:52:22 by fureimu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t	

void	ft_print_exec(t_exec *exec)
{
	t_exec	*tmp;
	int		i;

	tmp = exec;
	i = 0;
	if (!tmp)
		printf("EXEC IS EMPTY\n");
	else if (tmp)
		printf("EXEC ARRAY:\n");
	while (tmp)
	{
		printf("Chain nbr: %i\n", ++i);
		ft_print_array_str_fd(tmp->cmd, 1);
		printf("\n");
		tmp = tmp->next;
	}
}
